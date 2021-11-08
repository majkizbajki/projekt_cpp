#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Ally.h"

class Shop
{
public:
    bool isShopOpen;
    bool unlockedCharacter;
    bool enoughMoney;
    std::vector<Ally>* allyVector;

	Shop(sf::Font* menuFont, std::vector<Ally>* allyVector);
	void openShop(sf::RectangleShape* button, sf::RenderWindow* window, bool* isMenuWindowOpen);
	void closeShop(bool* isMenuWindowOpen);
    void drawShop(sf::RenderWindow* window);
    void pickCharacter();
    void blockCharacter();
    ~Shop();

private:
    const sf::VideoMode desktopSize = sf::VideoMode::getDesktopMode();

    // Texture
    sf::Texture leftArrow;
    sf::Texture blockedTexture;

    // Sprite
    sf::Sprite leftArrowButton;
    std::vector<sf::Sprite> characterSprites;
    std::vector<sf::Sprite> blockedSprites;

    // Text
    sf::Text shopText;
    sf::Text lockedCharacterText;
    sf::Text noMoneyText;
    sf::Text buyButtonText;

    // Button
    sf::RectangleShape pickCharacterGlow;
    sf::RectangleShape buyButton;
};

