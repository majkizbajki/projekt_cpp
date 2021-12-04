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
#include "Collision.h"

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

    Satyr1* satyr1 = new Satyr1();
    Game* game = new Game(&menu->menuFont, &shop->pickedCharacter, backslider1, backslider2, backslider3);
    game->enemyVector.push_back(*satyr1);

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
                    rules->openRules(&menu->rulesButton, &window, &menu->isMenuWindowOpen);
                    shop->openShop(&menu->shopButton, &window, &menu->isMenuWindowOpen);
                    delete game;
                    game = new Game(&menu->menuFont, &shop->pickedCharacter, backslider1, backslider2, backslider3);
                    game->enemyVector.push_back(*satyr1);
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
                                game->closeGame(&menu->isMenuWindowOpen, &menu->musicTheme);
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
                            game->backslider1->attackAnimation = true;
                        }
                        else if (game->pickedCharacter == 1)
                        {
                            game->backslider2->attackAnimation = true;
                        }
                        else if (game->pickedCharacter == 2)
                        {
                            game->backslider3->attackAnimation = true;
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
            if (game->enemyVector.size() > 0 && game->isGamePaused == false && game->isGameEnded == false && game->isRoundEnded == false)
            {
                for (int i = 0; i < game->enemyVector.size(); i++)
                {   
                    if (game->enemyVector[i].life > 0)
                    {
                        if (Collision::PixelPerfectTest(game->enemyVector[i].enemySprite, game->backslider1->playerSprite) && game->enemyVector[i].pauseTimeAttack >= 1.0f)
                        {
                            game->enemyVector[i].attackAnimation = true;
                            if (game->pickedCharacter == 0)
                            {
                                game->enemyVector[i].attack(game->backslider1);
                            }
                            else if (game->pickedCharacter == 1)
                            {
                                game->enemyVector[i].attack(game->backslider2);
                            }
                            else if (game->pickedCharacter == 2)
                            {
                                game->enemyVector[i].attack(game->backslider3);
                            }
                        }
                    }
                    else
                    {
                        game->enemyVector[i].deadAnimation = true;
                        game->enemyVector[i].dead();
                    }
                }
            }
            menu->musicTheme.stop();
            if (game->pickedCharacter == 0)
            {
                if (game->backslider1->life > 0)
                {
                    game->drawGame(&window);
                }
                else if (game->backslider1->life <= 0 && game->isGameEnded == false && game->isGamePaused == false && game->isRoundEnded == false)
                {
                    game->backslider1->deadAnimation = true;
                    game->backslider1->dead();
                    if (game->backslider1->endGame)
                    {
                        game->isGameEnded = true;
                    }
                    game->drawGame(&window);
                }
                else if (game->backslider1->life <= 0 && game->isGameEnded == true && game->isGamePaused == false && game->isRoundEnded == false)
                {
                    delete backslider1;
                    backslider1 = new Backslider1();
                    game->isGameOpen = false;
                    game->isGamePaused = false;
                    menu->isMenuWindowOpen = true;
                }
            }
            else if (game->pickedCharacter == 1)
            {
                if (game->backslider2->life > 0)
                {
                    game->drawGame(&window);
                }
                else if (game->backslider2->life <= 0 && game->isGameEnded == false && game->isGamePaused == false && game->isRoundEnded == false)
                {
                    game->backslider2->deadAnimation = true;
                    game->backslider2->dead();
                    if (game->backslider2->endGame)
                    {
                        game->isGameEnded = true;
                    }
                    game->drawGame(&window);
                }
                else if (game->backslider2->life <= 0 && game->isGameEnded == true && game->isGamePaused == false && game->isRoundEnded == false)
                {
                    delete backslider2;
                    backslider2 = new Backslider2();
                    game->isGameOpen = false;
                    game->isGamePaused = false;
                    menu->isMenuWindowOpen = true;
                }
            }
            else if (game->pickedCharacter == 2)
            {
                if (game->backslider3->life > 0)
                {
                    game->drawGame(&window);
                }
                else if (game->backslider3->life <= 0 && game->isGameEnded == false && game->isGamePaused == false && game->isRoundEnded == false)
                {
                    game->backslider3->deadAnimation = true;
                    game->backslider3->dead();
                    if (game->backslider3->endGame)
                    {
                        game->isGameEnded = true;
                    }
                    game->drawGame(&window);
                }
                else if (game->backslider3->life <= 0 && game->isGameEnded == true && game->isGamePaused == false && game->isRoundEnded == false)
                {
                    delete backslider3;
                    backslider3 = new Backslider3();
                    game->isGameOpen = false;
                    game->isGamePaused = false;
                    menu->isMenuWindowOpen = true;
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

    return 0;
}