#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include <vector>
#include "Menu.h"
#include "Rules.h"
#include "Shop.h"
#include "Ally.h"
#include "Backslider1.h"
#include "Backslider2.h"
#include "Backslider3.h"
#include "Player.h"
#include "Game.h"
#include "Enemy.h"
#include "Satyr1.h"
#include "Satyr2.h"
#include "Satyr3.h"
#include "Collision.h"
#include "Round.h"

int main()
{
    const sf::VideoMode desktopSize = sf::VideoMode::getDesktopMode();

    sf::RenderWindow window(sf::VideoMode(desktopSize.width, 0.96*desktopSize.height), "Legendary Scuffle Game", sf::Style::Fullscreen);
    window.setFramerateLimit(60);

    Menu* menu = new Menu();
    Rules* rules = new Rules(&menu->menuFont);

    Backslider1* backslider1 = new Backslider1();
    Backslider2* backslider2 = new Backslider2();
    Backslider3* backslider3 = new Backslider3();

    std::vector<Ally> allyVector;
    allyVector.push_back(*backslider1);
    allyVector.push_back(*backslider2);
    allyVector.push_back(*backslider3);

    Player* player = new Player();
    Shop* shop = new Shop(&menu->menuFont,&allyVector,player);

    Round* gameRound = new Round();

    Game* game = new Game(&menu->menuFont, &shop->pickedCharacter, &allyVector, &gameRound->enemyVector, &gameRound->mapSprites);

    while (window.isOpen())
    {
        menu->animationInterval();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            else if (event.type == sf::Event::MouseButtonReleased)
            {
                if (menu->closeGame() && menu->isMenuWindowOpen)
                {
                    window.close();
                }
                if (menu->isMenuWindowOpen)
                {
                    menu->playPauseMusic();
                    menu->musicTheme.setVolume(100);
                    rules->openRules(&menu->rulesButton, &window, &menu->isMenuWindowOpen);
                    shop->openShop(&menu->shopButton, &window, &menu->isMenuWindowOpen);
                    
                    delete game;

                    for (int i = 0; i < allyVector.size(); i++)
                    {
                        allyVector[i].setStatistics(i);
                    }
                    // Round reset
                    delete gameRound;
                    gameRound = new Round();
                    gameRound->generateRound();

                    for (int i = 0; i < allyVector.size(); i++)
                    {
                        allyVector[i].playerSprite.setPosition(sf::Vector2f(0.1 * desktopSize.width, 0.45 * desktopSize.height));
                    }
                    
                    game = new Game(&menu->menuFont, &shop->pickedCharacter, &allyVector,&gameRound->enemyVector,&gameRound->mapSprites);
                    game->openGame(&menu->startGameButton, &window, &menu->isMenuWindowOpen);
                }
                else
                {
                    if (rules->isRulesOpen)
                    {
                        rules->closeRules(&menu->isMenuWindowOpen);
                    }
                    if (shop->isShopOpen)
                    {
                        shop->closeShop(&menu->isMenuWindowOpen);
                        shop->drawShop(&window);
                    }
                    if (game)
                    {
                        if (game->isGameOpen)
                        {
                            if (game->isGamePaused)
                            {
                                game->closeGame(&menu->isMenuWindowOpen,&menu->musicTheme);
                                game->continueGame();
                            }
                        }
                    }
                }
            }
            else if (event.type == sf::Event::KeyReleased)
            {
                if (game)
                {
                    if (event.key.code == sf::Keyboard::Escape && game->isGameOpen && game->isGamePaused == false && game->isGameEnded == false && game->isRoundEnded == false)
                    {
                        game->isGamePaused = true;
                    }
                    if (event.key.code == sf::Keyboard::Space && game->isGameOpen && game->isGamePaused == false && game->isGameEnded == false && game->isRoundEnded == false)
                    {
                        if (game->pickedCharacter == 0)
                        {
                            game->allyVector->at(0).attackAnimation = true;
                        }
                        else if (game->pickedCharacter == 1)
                        {
                            game->allyVector->at(1).attackAnimation = true;
                        }
                        else if (game->pickedCharacter == 2)
                        {
                            game->allyVector->at(2).attackAnimation = true;
                        }
                    }
                }
            }
        }

        if (menu->isMenuWindowOpen)
        {
            menu->drawMenu(&window);
        }

        if (game->isGameOpen)
        {
            menu->musicTheme.setVolume(0);
            
            if (game->enemyVector->size() > 0)
            {
                bool isRoundEnded = true;
                if (game->isGamePaused == false && game->isGameEnded == false && game->isRoundEnded == false)
                {
                    for (int i = 0; i < game->enemyVector->size(); i++)
                    {
                        if (game->enemyVector->at(i).endRound == false)
                        {
                            if (game->enemyVector->at(i).life > 0)
                            {
                                if (Collision::PixelPerfectTest(game->enemyVector->at(i).enemySprite, game->allyVector->at(0).playerSprite) && game->enemyVector->at(i).pauseTimeAttack >= 1.0f)
                                {
                                    game->enemyVector->at(i).attackAnimation = true;
                                    if (game->pickedCharacter == 0)
                                    {
                                        game->enemyVector->at(i).attack(&game->allyVector->at(0));
                                    }
                                    else if (game->pickedCharacter == 1)
                                    {
                                        game->enemyVector->at(i).attack(&game->allyVector->at(1));
                                    }
                                    else if (game->pickedCharacter == 2)
                                    {
                                        game->enemyVector->at(i).attack(&game->allyVector->at(2));
                                    }
                                }
                            }
                            else
                            {
                                game->enemyVector->at(i).deadAnimation = true;
                                game->enemyVector->at(i).dead();
                            }
                        }
                    }
                }

                for (int i = 0; i < game->enemyVector->size(); i++)
                {
                    if (game->enemyVector->at(i).endRound == false)
                    {
                        isRoundEnded = false;
                        break;
                    }
                }

                if (isRoundEnded)
                {
                    game->enemyVector->clear();
                }
            }
            else
            {
                delete game;

                // Round reset
                gameRound->round += 1;
                gameRound->generateRound();

                for (int i = 0; i < allyVector.size(); i++)
                {
                    allyVector[i].playerSprite.setPosition(sf::Vector2f(0.1 * desktopSize.width, 0.45 * desktopSize.height));
                }

                game = new Game(&menu->menuFont, &shop->pickedCharacter, &allyVector, &gameRound->enemyVector, &gameRound->mapSprites);
                game->isGameOpen = true;
            }

            if (game->pickedCharacter == 0)
            {
                if (game->allyVector->at(0).life > 0)
                {
                    game->drawGame(&window);
                }
                else if (game->allyVector->at(0).life <= 0 && game->isGameEnded == false && game->isGamePaused == false && game->isRoundEnded == false)
                {
                    game->allyVector->at(0).deadAnimation = true;
                    game->allyVector->at(0).dead();
                    if (game->allyVector->at(0).endGame)
                    {
                        game->isGameEnded = true;
                    }
                    game->drawGame(&window);
                }
                else if (game->allyVector->at(0).life <= 0 && game->isGameEnded == true && game->isGamePaused == false && game->isRoundEnded == false)
                {
                    delete backslider1;
                    backslider1 = new Backslider1();
                    game->isGameOpen = false;
                    game->isGamePaused = false;
                    menu->isMenuWindowOpen = true;
                    menu->musicTheme.setVolume(100);
                }
            }
            else if (game->pickedCharacter == 1)
            {
                if (game->allyVector->at(1).life > 0)
                {
                    game->drawGame(&window);
                }
                else if (game->allyVector->at(1).life <= 0 && game->isGameEnded == false && game->isGamePaused == false && game->isRoundEnded == false)
                {
                    game->allyVector->at(1).deadAnimation = true;
                    game->allyVector->at(1).dead();
                    if (game->allyVector->at(1).endGame)
                    {
                        game->isGameEnded = true;
                    }
                    game->drawGame(&window);
                }
                else if (game->allyVector->at(1).life <= 0 && game->isGameEnded == true && game->isGamePaused == false && game->isRoundEnded == false)
                {
                    delete backslider2;
                    backslider2 = new Backslider2();
                    game->isGameOpen = false;
                    game->isGamePaused = false;
                    menu->isMenuWindowOpen = true;
                    menu->musicTheme.setVolume(100);
                }
            }
            else if (game->pickedCharacter == 2)
            {
                if (game->allyVector->at(2).life > 0)
                {
                    game->drawGame(&window);
                }
                else if (game->allyVector->at(2).life <= 0 && game->isGameEnded == false && game->isGamePaused == false && game->isRoundEnded == false)
                {
                    game->allyVector->at(2).deadAnimation = true;
                    game->allyVector->at(2).dead();
                    if (game->allyVector->at(2).endGame)
                    {
                        game->isGameEnded = true;
                    }
                    game->drawGame(&window);
                }
                else if (game->allyVector->at(2).life <= 0 && game->isGameEnded == true && game->isGamePaused == false && game->isRoundEnded == false)
                {
                    delete backslider3;
                    backslider3 = new Backslider3();
                    game->isGameOpen = false;
                    game->isGamePaused = false;
                    menu->isMenuWindowOpen = true;
                    menu->musicTheme.setVolume(100);
                }
            }
        }
    }

    delete menu;
    delete rules;
    delete shop;
    delete backslider1;
    delete backslider2;
    delete backslider3;
    delete game;
    delete gameRound;
    delete player;

    return 0;
}