#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include <vector>
#include "Menu.h"
#include "Rules.h"

int main()
{
    const sf::VideoMode desktopSize = sf::VideoMode::getDesktopMode();

    sf::RenderWindow window(sf::VideoMode(desktopSize.width, 0.96*desktopSize.height), "SFML works!", sf::Style::Fullscreen);
    window.setFramerateLimit(60);

    Menu menu;
    Rules rules(&menu.menuFont);

    while (window.isOpen())
    {
        menu.animationInterval();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                window.close();
            }
            else if (event.type == sf::Event::MouseButtonReleased)
            {
                if (menu.closeGame())
                {
                    window.close();
                }
                if (menu.isMenuWindowOpen)
                {
                    menu.playPauseMusic();
                    rules.openRules(&menu.rulesButton, &window, &menu.isMenuWindowOpen);
                }
                else
                {
                    rules.closeRules(&menu.isMenuWindowOpen);
                }
            }
        }

        if (menu.isMenuWindowOpen)
        {
            menu.drawMenu(&window);
        }
    }

    return 0;
}