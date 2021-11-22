﻿#include <SFML/Graphics.hpp>
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

    Game* game = new Game(&menu->menuFont,&shop->pickedCharacter,backslider1, backslider2, backslider3);

    while (window.isOpen())
    {
        menu->animationInterval();
        backslider1->animationInterval();

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
            else if (event.type == sf::Event::KeyReleased)
            {
                if (event.key.code == sf::Keyboard::Escape && game->isGameOpen && game->isGamePaused == false)
                {
                    game->isGamePaused = true;
                }
                if (event.key.code == sf::Keyboard::Space && game->isGameOpen && game->isGamePaused == false)
                {
                    backslider1->attackAnimation = true;
                }
            }
        }

        if (menu->isMenuWindowOpen)
        {
            menu->drawMenu(&window);
        }

        if (game->isGameOpen)
        {
            menu->musicTheme.stop();
            game->drawGame(&window);
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