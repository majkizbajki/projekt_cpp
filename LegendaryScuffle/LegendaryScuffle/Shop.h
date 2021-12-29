#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "Ally.h"
#include "Player.h"
#include <fstream>

class Shop
{
public:
    bool isShopOpen;
    bool unlockedCharacter;
    bool enoughMoney;
    short pickedCharacter;
    std::vector<Ally>* allyVector;
    Player* player;
    std::vector<bool> possibleUpgrade;

	Shop(sf::Font* menuFont, std::vector<Ally>* allyVector, Player* player);
	void openShop(sf::RectangleShape* button, sf::RenderWindow* window, bool* isMenuWindowOpen);
	void closeShop(bool* isMenuWindowOpen);
    void drawShop(sf::RenderWindow* window);
    void pickCharacter();
    void blockCharacter();
    void unlockCharacter();
    void upgradeCharacter();
    void upgradeCharacterText();
    ~Shop();

private:
    const sf::VideoMode desktopSize = sf::VideoMode::getDesktopMode();
    sf::Window window;

    std::fstream file;

    // Texture
    sf::Texture leftArrow;
    sf::Texture blockedTexture;
    sf::Texture upgradeButtonTexture;
    sf::Texture lifeTexture;
    sf::Texture powerTexture;
    sf::Texture armorTexture;
    sf::Texture magicResistTexture;
    sf::Texture superPowerTexture;
    sf::Texture lifeUpgradeTexture;
    sf::Texture powerUpgradeTexture;
    sf::Texture armorUpgradeTexture;
    sf::Texture magicResistUpgradeTexture;
    sf::Texture superPowerUpgradeTexture;
    sf::Texture moneyTextTexture;

    // Sprite
    sf::Sprite leftArrowButton;
    std::vector<sf::Sprite> characterSprites;
    std::vector<sf::Sprite> blockedSprites;
    sf::Sprite upgradeButton;
    std::vector<sf::Sprite> upgradeButtonVector;
    sf::Sprite lifeSprite;
    sf::Sprite powerSprite;
    sf::Sprite armorSprite;
    sf::Sprite magicResistSprite;
    sf::Sprite superPowerSprite;
    sf::Sprite lifeUpgradeSprite;
    sf::Sprite powerUpgradeSprite;
    sf::Sprite armorUpgradeSprite;
    sf::Sprite magicResistUpgradeSprite;
    sf::Sprite superPowerUpgradeSprite;
    sf::Sprite moneyTextSprite;

    // Text
    sf::Text shopText;
    sf::Text lockedCharacterText;
    sf::Text noMoneyText;
    sf::Text buyButtonText;
    sf::Text lifeText;
    sf::Text powerText;
    sf::Text superPowerText;
    sf::Text magicResistText;
    sf::Text armorText;
    sf::Text lifeUpgradeText;
    sf::Text powerUpgradeText;
    sf::Text superPowerUpgradeText;
    sf::Text magicResistUpgradeText;
    sf::Text armorUpgradeText;
    sf::Text moneyText;

    sf::Font menuFont;

    // Button
    sf::RectangleShape pickCharacterGlow;
    sf::RectangleShape buyButton;
};

