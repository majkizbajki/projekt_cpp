#pragma once

#include <SFML/Graphics.hpp>

class Rules
{
public:
	Rules(sf::Font* menuFont);
    void openRules(sf::RectangleShape* button, sf::RenderWindow* window, bool* isMenuWindowOpen);
    void closeRules(bool* isMenuWindowOpen);
private:
    const sf::VideoMode desktopSize = sf::VideoMode::getDesktopMode();

    // Texture
    sf::Texture leftArrow;
    
    //Sprite
    sf::Sprite leftArrowButton;

    // Text
    sf::Text rulesText;
    sf::Text rulesDescriptionText;
    sf::Text controlsText;
    sf::Text wasdText;
    sf::Text spaceText;
    sf::Text superPowerText;

    std::vector <sf::Text> rulesControlsAssets;
};

