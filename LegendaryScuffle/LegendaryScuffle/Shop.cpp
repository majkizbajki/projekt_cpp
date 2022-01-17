#include "Shop.h"
#include "Player.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <cmath>

Shop::Shop(sf::Font* menuFont, std::vector<Ally>* allyVector,Player* player)
{
    this->isShopOpen = false;
    this->unlockedCharacter = false;
    this->enoughMoney = false;
    this->pickedCharacter = 0;
    this->allyVector = allyVector;
    this->menuFont = *menuFont;
    this->player = player;
    for (int i = 0; i < 5; i++)
    {
        this->possibleUpgrade.push_back(false);
    }

	// Back to menu button
	this->leftArrow.loadFromFile("assets/left-arrow.png");
	this->leftArrow.setSmooth(true);

	this->leftArrowButton.setTexture(this->leftArrow);
	this->leftArrowButton.setPosition(sf::Vector2f(0.05 * this->desktopSize.width, 0.05 * this->desktopSize.height));

    // Shop title text
    this->shopText.setString("SHOP");
    this->shopText.setFont(*menuFont);
    this->shopText.setCharacterSize(60);
    this->shopText.setFillColor(sf::Color(254, 250, 224));
    this->shopText.setPosition(sf::Vector2f(0.47 * this->desktopSize.width, 0.1 * this->desktopSize.height));
    
    // Characters
    for (int i = 0; i < this->allyVector->size(); i++)
    {
        sf::Sprite sprite;
        sprite.setTexture(*this->allyVector->at(i).getSprite().getTexture());
        sprite.setScale(0.5, 0.5);
        if (i % 3 == 0)
        {
            sprite.setPosition(sf::Vector2f(0.1 * this->desktopSize.width, 0.21 * this->desktopSize.height));
        }
        else if (i % 3 == 1)
        {
            sprite.setPosition(sf::Vector2f(0.4 * this->desktopSize.width, 0.21 * this->desktopSize.height));
        }
        else if (i % 3 == 2)
        {
            sprite.setPosition(sf::Vector2f(0.7 * this->desktopSize.width, 0.21 * this->desktopSize.height));
        }

        this->characterSprites.push_back(sprite);
    }

    // Pick character background
    this->pickCharacterGlow.setSize(sf::Vector2f(450.0, 450.0));
    this->pickCharacterGlow.setFillColor(sf::Color(0, 0, 0, 100));
    this->pickCharacterGlow.setPosition(sf::Vector2f(0.1 * desktopSize.width, 0.2 * desktopSize.height));

    // Pick character when open shop
    this->pickCharacterGlow.setPosition(sf::Vector2f(0.1 * this->desktopSize.width, 0.2 * this->desktopSize.height));
    this->unlockedCharacter = this->allyVector->at(0).isUnlocked;
    this->enoughMoney = true;

    // Blocked image
    this->blockedTexture.loadFromFile("assets/shop/block.png");
    this->blockedTexture.setSmooth(true);

    // Locked character text
    this->lockedCharacterText.setString("This hero is locked. You have to buy it first.");
    this->lockedCharacterText.setFont(*menuFont);
    this->lockedCharacterText.setCharacterSize(40);
    this->lockedCharacterText.setFillColor(sf::Color(254, 250, 224));
    this->lockedCharacterText.setPosition(sf::Vector2f(0.28 * this->desktopSize.width, 0.7 * this->desktopSize.height));

    // Not enough money text
    this->noMoneyText.setString("Sorry, you don't have enough money to buy this hero.");
    this->noMoneyText.setFont(*menuFont);
    this->noMoneyText.setCharacterSize(40);
    this->noMoneyText.setFillColor(sf::Color(254, 250, 224));
    this->noMoneyText.setPosition(sf::Vector2f(0.2 * this->desktopSize.width, 0.8 * this->desktopSize.height));

    // Buy hero button
    this->buyButtonText.setString("BUY");
    this->buyButtonText.setFont(*menuFont);
    this->buyButtonText.setCharacterSize(40);
    this->buyButtonText.setFillColor(sf::Color(40, 54, 24));
    this->buyButtonText.setPosition(sf::Vector2f(0.47 * this->desktopSize.width, 0.87 * this->desktopSize.height));
    this->buyButton.setSize(sf::Vector2f(400, 90));
    this->buyButton.setFillColor(sf::Color(221, 161, 94));
    this->buyButton.setPosition(sf::Vector2f(0.38 * this->desktopSize.width, 0.85 * this->desktopSize.height));

    // Upgrade button
    this->upgradeButtonTexture.loadFromFile("assets/shop/upgrade.png");
    this->upgradeButtonTexture.setSmooth(true);
    this->upgradeButton.setTexture(this->upgradeButtonTexture);
    this->upgradeButton.setPosition(sf::Vector2f(0.43 * this->desktopSize.width, 0.69 * this->desktopSize.height));
    this->upgradeButtonVector.push_back(this->upgradeButton);
    this->upgradeButton.setPosition(sf::Vector2f(0.43 * this->desktopSize.width, 0.79 * this->desktopSize.height));
    this->upgradeButtonVector.push_back(this->upgradeButton);
    this->upgradeButton.setPosition(sf::Vector2f(0.43 * this->desktopSize.width, 0.89 * this->desktopSize.height));
    this->upgradeButtonVector.push_back(this->upgradeButton);
    this->upgradeButton.setPosition(sf::Vector2f(0.8 * this->desktopSize.width, 0.69 * this->desktopSize.height));
    this->upgradeButtonVector.push_back(this->upgradeButton);
    this->upgradeButton.setPosition(sf::Vector2f(0.8 * this->desktopSize.width, 0.79 * this->desktopSize.height));
    this->upgradeButtonVector.push_back(this->upgradeButton);

    // Upgrade Sprites and text
    this->lifeTexture.loadFromFile("assets/shop/heart.png");
    this->lifeTexture.setSmooth(true);
    this->powerTexture.loadFromFile("assets/shop/power.png");
    this->powerTexture.setSmooth(true);
    this->armorTexture.loadFromFile("assets/shop/armor.png");
    this->armorTexture.setSmooth(true);
    this->magicResistTexture.loadFromFile("assets/shop/magic.png");
    this->magicResistTexture.setSmooth(true);
    this->superPowerTexture.loadFromFile("assets/shop/superhero.png");
    this->superPowerTexture.setSmooth(true);

    this->lifeUpgradeTexture.loadFromFile("assets/shop/heart_upgrade.png");
    this->lifeUpgradeTexture.setSmooth(true);
    this->powerUpgradeTexture.loadFromFile("assets/shop/power_upgrade.png");
    this->powerUpgradeTexture.setSmooth(true);
    this->armorUpgradeTexture.loadFromFile("assets/shop/armor_upgrade.png");
    this->armorUpgradeTexture.setSmooth(true);
    this->magicResistUpgradeTexture.loadFromFile("assets/shop/magic_upgrade.png");
    this->magicResistUpgradeTexture.setSmooth(true);
    this->superPowerUpgradeTexture.loadFromFile("assets/shop/superhero_upgrade.png");
    this->superPowerUpgradeTexture.setSmooth(true);

    this->lifeSprite.setTexture(this->lifeTexture);
    this->lifeSprite.setPosition(sf::Vector2f(0.85 * this->desktopSize.width, 0.01 * this->desktopSize.height));
    this->powerSprite.setTexture(this->powerTexture);
    this->powerSprite.setPosition(sf::Vector2f(0.85 * this->desktopSize.width, 0.05 * this->desktopSize.height));
    this->armorSprite.setTexture(this->armorTexture);
    this->armorSprite.setPosition(sf::Vector2f(0.85 * this->desktopSize.width, 0.09 * this->desktopSize.height));
    this->magicResistSprite.setTexture(this->magicResistTexture);
    this->magicResistSprite.setPosition(sf::Vector2f(0.85 * this->desktopSize.width, 0.13 * this->desktopSize.height));
    this->superPowerSprite.setTexture(this->superPowerTexture);
    this->superPowerSprite.setPosition(sf::Vector2f(0.85 * this->desktopSize.width, 0.17 * this->desktopSize.height));

    this->lifeUpgradeSprite.setTexture(this->lifeUpgradeTexture);
    this->lifeUpgradeSprite.setPosition(sf::Vector2f(0.1 * this->desktopSize.width, 0.7 * this->desktopSize.height));
    this->powerUpgradeSprite.setTexture(this->powerUpgradeTexture);
    this->powerUpgradeSprite.setPosition(sf::Vector2f(0.5 * this->desktopSize.width, 0.7 * this->desktopSize.height));
    this->armorUpgradeSprite.setTexture(this->armorUpgradeTexture);
    this->armorUpgradeSprite.setPosition(sf::Vector2f(0.1 * this->desktopSize.width, 0.8 * this->desktopSize.height));
    this->magicResistUpgradeSprite.setTexture(this->magicResistUpgradeTexture);
    this->magicResistUpgradeSprite.setPosition(sf::Vector2f(0.5 * this->desktopSize.width, 0.8 * this->desktopSize.height));
    this->superPowerUpgradeSprite.setTexture(this->superPowerUpgradeTexture);
    this->superPowerUpgradeSprite.setPosition(sf::Vector2f(0.1 * this->desktopSize.width, 0.9 * this->desktopSize.height));

    this->lifeText.setFont(this->menuFont);
    this->lifeText.setCharacterSize(24);
    this->lifeText.setFillColor(sf::Color(254, 250, 224));
    this->lifeText.setPosition(sf::Vector2f(0.88 * this->desktopSize.width,0.01 * this->desktopSize.height));
    this->powerText.setFont(this->menuFont);
    this->powerText.setCharacterSize(24);
    this->powerText.setFillColor(sf::Color(254, 250, 224));
    this->powerText.setPosition(sf::Vector2f(0.88 * this->desktopSize.width, 0.05 * this->desktopSize.height));
    this->armorText.setFont(this->menuFont);
    this->armorText.setCharacterSize(24);
    this->armorText.setFillColor(sf::Color(254, 250, 224));
    this->armorText.setPosition(sf::Vector2f(0.88 * this->desktopSize.width, 0.09 * this->desktopSize.height));
    this->magicResistText.setFont(this->menuFont);
    this->magicResistText.setCharacterSize(24);
    this->magicResistText.setFillColor(sf::Color(254, 250, 224));
    this->magicResistText.setPosition(sf::Vector2f(0.88 * this->desktopSize.width, 0.13 * this->desktopSize.height));
    this->superPowerText.setFont(this->menuFont);
    this->superPowerText.setCharacterSize(24);
    this->superPowerText.setFillColor(sf::Color(254, 250, 224));
    this->superPowerText.setPosition(sf::Vector2f(0.88 * this->desktopSize.width, 0.17 * this->desktopSize.height));

    this->lifeText.setString(std::to_string(int(this->allyVector->at(this->pickedCharacter).life)));
    this->powerText.setString(std::to_string(int(this->allyVector->at(this->pickedCharacter).power)));
    this->armorText.setString(std::to_string(int(this->allyVector->at(this->pickedCharacter).armor)));
    this->magicResistText.setString(std::to_string(int(this->allyVector->at(this->pickedCharacter).magicResist)));
    this->superPowerText.setString(std::to_string(this->allyVector->at(this->pickedCharacter).superPower).substr(0, 3));

    this->pickCharacter();

    // Upgrade text
    if (this->pickedCharacter == 0)
    {
        // LIFE LEVEL
        std::string lifeLevel = std::to_string(this->allyVector->at(this->pickedCharacter).lifeLevel);
        std::string lifeNextLevel = "( + ";
        if (this->allyVector->at(this->pickedCharacter).lifeLevel == 1)
        {
            lifeNextLevel += "150 )";
        }
        else if (this->allyVector->at(this->pickedCharacter).lifeLevel > 1 && this->allyVector->at(this->pickedCharacter).lifeLevel < 7)
        {
            lifeNextLevel += "250 )";
        }
        else if (this->allyVector->at(this->pickedCharacter).lifeLevel == 7)
        {
            lifeNextLevel += "1000 )";
        }
        else
        {
            lifeNextLevel += "2500 )";
        }
        if (this->allyVector->at(this->pickedCharacter).lifeLevel != 10)
        {
            this->lifeUpgradeText.setString("LIFE  LEVEL:  " + lifeLevel + "\n" + "NEXT  LEVEL:  " + lifeNextLevel);
            this->lifeUpgradeText.setPosition(sf::Vector2f(0.15 * this->desktopSize.width, 0.7 * this->desktopSize.height));
        }
        else
        {
            this->lifeUpgradeText.setString("LIFE  LEVEL:  MAX");
            this->lifeUpgradeText.setPosition(sf::Vector2f(0.15 * this->desktopSize.width, 0.725 * this->desktopSize.height));
        }
        this->lifeUpgradeText.setFont(this->menuFont);
        this->lifeUpgradeText.setCharacterSize(25);
        this->lifeUpgradeText.setFillColor(sf::Color(254, 250, 224));

        // POWER LEVEL
        std::string powerLevel = std::to_string(this->allyVector->at(this->pickedCharacter).powerLevel);
        std::string powerNextLevel = "( + 10 )";
        if (this->allyVector->at(this->pickedCharacter).powerLevel != 10)
        {
            this->powerUpgradeText.setString("POWER  LEVEL:  " + powerLevel + "\n" + "NEXT  LEVEL:  " + powerNextLevel);
            this->powerUpgradeText.setPosition(sf::Vector2f(0.55 * this->desktopSize.width, 0.7 * this->desktopSize.height));
        }
        else
        {
            this->powerUpgradeText.setString("POWER  LEVEL:  MAX");
            this->powerUpgradeText.setPosition(sf::Vector2f(0.55 * this->desktopSize.width, 0.725 * this->desktopSize.height));
        }
        this->powerUpgradeText.setFont(this->menuFont);
        this->powerUpgradeText.setCharacterSize(25);
        this->powerUpgradeText.setFillColor(sf::Color(254, 250, 224));

        // ARMOR LEVEL
        std::string armorLevel = std::to_string(this->allyVector->at(this->pickedCharacter).armorLevel);
        std::string armorNextLevel = "( + ";
        if (this->allyVector->at(this->pickedCharacter).armorLevel < 8)
        {
            armorNextLevel += "5 )";
        }
        else
        {
            armorNextLevel += "25 )";
        }
        if (this->allyVector->at(this->pickedCharacter).armorLevel != 10)
        {
            this->armorUpgradeText.setString("ARMOR  LEVEL:  " + armorLevel + "\n" + "NEXT  LEVEL:  " + armorNextLevel);
            this->armorUpgradeText.setPosition(sf::Vector2f(0.15 * this->desktopSize.width, 0.8 * this->desktopSize.height));
        }
        else
        {
            this->armorUpgradeText.setString("ARMOR  LEVEL:  MAX");
            this->armorUpgradeText.setPosition(sf::Vector2f(0.15 * this->desktopSize.width, 0.825 * this->desktopSize.height));
        }
        this->armorUpgradeText.setFont(this->menuFont);
        this->armorUpgradeText.setCharacterSize(25);
        this->armorUpgradeText.setFillColor(sf::Color(254, 250, 224));

        // MAGIC RESIST LEVEL
        std::string magicResistLevel = std::to_string(this->allyVector->at(this->pickedCharacter).magicResistLevel);
        std::string magicResistNextLevel = "( + ";
        if (this->allyVector->at(this->pickedCharacter).magicResistLevel < 8)
        {
            magicResistNextLevel += "5 )";
        }
        else
        {
            magicResistNextLevel += "25 )";
        }
        if (this->allyVector->at(this->pickedCharacter).magicResistLevel != 10)
        {
            this->magicResistUpgradeText.setString("MAGIC  RESIST  LEVEL:  " + magicResistLevel + "\n" + "NEXT  LEVEL:  " + magicResistNextLevel);
            this->magicResistUpgradeText.setPosition(sf::Vector2f(0.55 * this->desktopSize.width, 0.8 * this->desktopSize.height));
        }
        else
        {
            this->magicResistUpgradeText.setString("MAGIC  RESIST  LEVEL:  MAX");
            this->magicResistUpgradeText.setPosition(sf::Vector2f(0.55 * this->desktopSize.width, 0.825 * this->desktopSize.height));
        }
        this->magicResistUpgradeText.setFont(this->menuFont);
        this->magicResistUpgradeText.setCharacterSize(25);
        this->magicResistUpgradeText.setFillColor(sf::Color(254, 250, 224));

        // SUPER POWER LEVEL
        std::string superPowerLevel = std::to_string(this->allyVector->at(this->pickedCharacter).superPowerLevel);
        std::string superPowerNextLevel = "( + 0.5 )";
        if (this->allyVector->at(this->pickedCharacter).superPowerLevel != 10)
        {
            this->superPowerUpgradeText.setString("SUPER  POWER  LEVEL:  " + superPowerLevel + "\n" + "NEXT  LEVEL:  " + superPowerNextLevel);
            this->superPowerUpgradeText.setPosition(sf::Vector2f(0.15 * this->desktopSize.width, 0.9 * this->desktopSize.height));
        }
        else
        {
            this->superPowerUpgradeText.setString("SUPER  POWER  LEVEL:  MAX");
            this->superPowerUpgradeText.setPosition(sf::Vector2f(0.15 * this->desktopSize.width, 0.925 * this->desktopSize.height));
        }
        this->superPowerUpgradeText.setFont(this->menuFont);
        this->superPowerUpgradeText.setCharacterSize(25);
        this->superPowerUpgradeText.setFillColor(sf::Color(254, 250, 224));
    }
    else if (this->pickedCharacter == 1)
    {
        // LIFE LEVEL
        std::string lifeLevel = std::to_string(this->allyVector->at(this->pickedCharacter).lifeLevel);
        std::string lifeNextLevel = "( + ";
        if (this->allyVector->at(this->pickedCharacter).lifeLevel == 1)
        {
            lifeNextLevel += "1500 )";
        }
        else if (this->allyVector->at(this->pickedCharacter).lifeLevel > 1 && this->allyVector->at(this->pickedCharacter).lifeLevel < 5)
        {
            lifeNextLevel += "2500 )";
        }
        else
        {
            lifeNextLevel += "2000 )";
        }
        if (this->allyVector->at(this->pickedCharacter).lifeLevel != 10)
        {
            this->lifeUpgradeText.setString("LIFE  LEVEL:  " + lifeLevel + "\n" + "NEXT  LEVEL:  " + lifeNextLevel);
            this->lifeUpgradeText.setPosition(sf::Vector2f(0.15 * this->desktopSize.width, 0.7 * this->desktopSize.height));
        }
        else
        {
            this->lifeUpgradeText.setString("LIFE  LEVEL:  MAX");
            this->lifeUpgradeText.setPosition(sf::Vector2f(0.15 * this->desktopSize.width, 0.725 * this->desktopSize.height));
        }
        this->lifeUpgradeText.setFont(this->menuFont);
        this->lifeUpgradeText.setCharacterSize(25);
        this->lifeUpgradeText.setFillColor(sf::Color(254, 250, 224));

        // POWER LEVEL
        std::string powerLevel = std::to_string(this->allyVector->at(this->pickedCharacter).powerLevel);
        std::string powerNextLevel = "( + ";
        if (this->allyVector->at(this->pickedCharacter).powerLevel < 7)
        {
            powerNextLevel += "25 )";
        }
        else
        {
            powerNextLevel += "50 )";
        }
        if (this->allyVector->at(this->pickedCharacter).powerLevel != 10)
        {
            this->powerUpgradeText.setString("POWER  LEVEL:  " + powerLevel + "\n" + "NEXT  LEVEL:  " + powerNextLevel);
            this->powerUpgradeText.setPosition(sf::Vector2f(0.55 * this->desktopSize.width, 0.7 * this->desktopSize.height));
        }
        else
        {
            this->powerUpgradeText.setString("POWER  LEVEL:  MAX");
            this->powerUpgradeText.setPosition(sf::Vector2f(0.55 * this->desktopSize.width, 0.725 * this->desktopSize.height));
        }
        this->powerUpgradeText.setFont(this->menuFont);
        this->powerUpgradeText.setCharacterSize(25);
        this->powerUpgradeText.setFillColor(sf::Color(254, 250, 224));

        // ARMOR LEVEL
        std::string armorLevel = std::to_string(this->allyVector->at(this->pickedCharacter).armorLevel);
        std::string armorNextLevel = "( + ";
        if (this->allyVector->at(this->pickedCharacter).armorLevel < 6)
        {
            armorNextLevel += "10 )";
        }
        else if (this->allyVector->at(this->pickedCharacter).armorLevel > 5 && this->allyVector->at(this->pickedCharacter).armorLevel < 9)
        {
            armorNextLevel += "25 )";
        }
        else
        {
            armorNextLevel += "50 )";
        }
        if (this->allyVector->at(this->pickedCharacter).armorLevel != 10)
        {
            this->armorUpgradeText.setString("ARMOR  LEVEL:  " + armorLevel + "\n" + "NEXT  LEVEL:  " + armorNextLevel);
            this->armorUpgradeText.setPosition(sf::Vector2f(0.15 * this->desktopSize.width, 0.8 * this->desktopSize.height));
        }
        else
        {
            this->armorUpgradeText.setString("ARMOR  LEVEL:  MAX");
            this->armorUpgradeText.setPosition(sf::Vector2f(0.15 * this->desktopSize.width, 0.825 * this->desktopSize.height));
        }
        this->armorUpgradeText.setFont(this->menuFont);
        this->armorUpgradeText.setCharacterSize(25);
        this->armorUpgradeText.setFillColor(sf::Color(254, 250, 224));

        // MAGIC RESIST LEVEL
        std::string magicResistLevel = std::to_string(this->allyVector->at(this->pickedCharacter).magicResistLevel);
        std::string magicResistNextLevel = "( + ";
        if (this->allyVector->at(this->pickedCharacter).magicResistLevel < 6)
        {
            magicResistNextLevel += "10 )";
        }
        else if (this->allyVector->at(this->pickedCharacter).magicResistLevel > 5 && this->allyVector->at(this->pickedCharacter).magicResistLevel < 9)
        {
            magicResistNextLevel += "25 )";
        }
        else
        {
            magicResistNextLevel += "50 )";
        }
        if (this->allyVector->at(this->pickedCharacter).magicResistLevel != 10)
        {
            this->magicResistUpgradeText.setString("MAGIC  RESIST  LEVEL:  " + magicResistLevel + "\n" + "NEXT  LEVEL:  " + magicResistNextLevel);
            this->magicResistUpgradeText.setPosition(sf::Vector2f(0.55 * this->desktopSize.width, 0.8 * this->desktopSize.height));
        }
        else
        {
            this->magicResistUpgradeText.setString("MAGIC  RESIST  LEVEL:  MAX");
            this->magicResistUpgradeText.setPosition(sf::Vector2f(0.55 * this->desktopSize.width, 0.825 * this->desktopSize.height));
        }
        this->magicResistUpgradeText.setFont(this->menuFont);
        this->magicResistUpgradeText.setCharacterSize(25);
        this->magicResistUpgradeText.setFillColor(sf::Color(254, 250, 224));

        // SUPER POWER LEVEL
        std::string superPowerLevel = std::to_string(this->allyVector->at(this->pickedCharacter).superPowerLevel);
        std::string superPowerNextLevel = "( + 0.5 )";
        if (this->allyVector->at(this->pickedCharacter).superPowerLevel != 10)
        {
            this->superPowerUpgradeText.setString("SUPER  POWER  LEVEL:  " + superPowerLevel + "\n" + "NEXT  LEVEL:  " + superPowerNextLevel);
            this->superPowerUpgradeText.setPosition(sf::Vector2f(0.15 * this->desktopSize.width, 0.9 * this->desktopSize.height));
        }
        else
        {
            this->superPowerUpgradeText.setString("SUPER  POWER  LEVEL:  MAX");
            this->superPowerUpgradeText.setPosition(sf::Vector2f(0.15 * this->desktopSize.width, 0.925 * this->desktopSize.height));
        }
        this->superPowerUpgradeText.setFont(this->menuFont);
        this->superPowerUpgradeText.setCharacterSize(25);
        this->superPowerUpgradeText.setFillColor(sf::Color(254, 250, 224));
    }
    else if (this->pickedCharacter == 2)
    {
        // LIFE LEVEL
        std::string lifeLevel = std::to_string(this->allyVector->at(this->pickedCharacter).lifeLevel);
        std::string lifeNextLevel = "( + ";
        if (this->allyVector->at(this->pickedCharacter).lifeLevel < 5)
        {
            lifeNextLevel += "5000 )";
        }
        else
        {
            lifeNextLevel += "2500 )";
        }
        if (this->allyVector->at(this->pickedCharacter).lifeLevel != 10)
        {
            this->lifeUpgradeText.setString("LIFE  LEVEL:  " + lifeLevel + "\n" + "NEXT  LEVEL:  " + lifeNextLevel);
            this->lifeUpgradeText.setPosition(sf::Vector2f(0.15 * this->desktopSize.width, 0.7 * this->desktopSize.height));
        }
        else
        {
            this->lifeUpgradeText.setString("LIFE  LEVEL:  MAX");
            this->lifeUpgradeText.setPosition(sf::Vector2f(0.15 * this->desktopSize.width, 0.725 * this->desktopSize.height));
        }
        this->lifeUpgradeText.setFont(this->menuFont);
        this->lifeUpgradeText.setCharacterSize(25);
        this->lifeUpgradeText.setFillColor(sf::Color(254, 250, 224));

        // POWER LEVEL
        std::string powerLevel = std::to_string(this->allyVector->at(this->pickedCharacter).powerLevel);
        std::string powerNextLevel = "( + 100 )";
        if (this->allyVector->at(this->pickedCharacter).powerLevel != 10)
        {
            this->powerUpgradeText.setString("POWER  LEVEL:  " + powerLevel + "\n" + "NEXT  LEVEL:  " + powerNextLevel);
            this->powerUpgradeText.setPosition(sf::Vector2f(0.55 * this->desktopSize.width, 0.7 * this->desktopSize.height));
        }
        else
        {
            this->powerUpgradeText.setString("POWER  LEVEL:  MAX");
            this->powerUpgradeText.setPosition(sf::Vector2f(0.55 * this->desktopSize.width, 0.725 * this->desktopSize.height));
        }
        this->powerUpgradeText.setFont(this->menuFont);
        this->powerUpgradeText.setCharacterSize(40);
        this->powerUpgradeText.setFillColor(sf::Color(254, 250, 224));

        // ARMOR LEVEL
        std::string armorLevel = std::to_string(this->allyVector->at(this->pickedCharacter).armorLevel);
        std::string armorNextLevel = "( + 50 )";
        if (this->allyVector->at(this->pickedCharacter).armorLevel != 10)
        {
            this->armorUpgradeText.setString("ARMOR  LEVEL:  " + armorLevel + "\n" + "NEXT  LEVEL:  " + armorNextLevel);
            this->armorUpgradeText.setPosition(sf::Vector2f(0.15 * this->desktopSize.width, 0.8 * this->desktopSize.height));
        }
        else
        {
            this->armorUpgradeText.setString("ARMOR  LEVEL:  MAX");
            this->armorUpgradeText.setPosition(sf::Vector2f(0.15 * this->desktopSize.width, 0.825 * this->desktopSize.height));
        }
        this->armorUpgradeText.setFont(this->menuFont);
        this->armorUpgradeText.setCharacterSize(25);
        this->armorUpgradeText.setFillColor(sf::Color(254, 250, 224));

        // MAGIC RESIST LEVEL
        std::string magicResistLevel = std::to_string(this->allyVector->at(this->pickedCharacter).magicResistLevel);
        std::string magicResistNextLevel = "( + 50 )";
        if (this->allyVector->at(this->pickedCharacter).magicResistLevel != 10)
        {
            this->magicResistUpgradeText.setString("MAGIC  RESIST  LEVEL:  " + magicResistLevel + "\n" + "NEXT  LEVEL:  " + magicResistNextLevel);
            this->magicResistUpgradeText.setPosition(sf::Vector2f(0.55 * this->desktopSize.width, 0.8 * this->desktopSize.height));
        }
        else
        {
            this->magicResistUpgradeText.setString("MAGIC  RESIST  LEVEL:  MAX");
            this->magicResistUpgradeText.setPosition(sf::Vector2f(0.55 * this->desktopSize.width, 0.825 * this->desktopSize.height));
        }
        this->magicResistUpgradeText.setFont(this->menuFont);
        this->magicResistUpgradeText.setCharacterSize(25);
        this->magicResistUpgradeText.setFillColor(sf::Color(254, 250, 224));

        // SUPER POWER LEVEL
        std::string superPowerLevel = std::to_string(this->allyVector->at(this->pickedCharacter).superPowerLevel);
        std::string superPowerNextLevel = "( + 0.5 )";
        if (this->allyVector->at(this->pickedCharacter).superPowerLevel != 10)
        {
            this->superPowerUpgradeText.setString("SUPER  POWER  LEVEL:  " + superPowerLevel + "\n" + "NEXT  LEVEL:  " + superPowerNextLevel);
            this->superPowerUpgradeText.setPosition(sf::Vector2f(0.15 * this->desktopSize.width, 0.9 * this->desktopSize.height));
        }
        else
        {
            this->superPowerUpgradeText.setString("SUPER  POWER  LEVEL:  MAX");
            this->superPowerUpgradeText.setPosition(sf::Vector2f(0.15 * this->desktopSize.width, 0.925 * this->desktopSize.height));
        }
        this->superPowerUpgradeText.setFont(this->menuFont);
        this->superPowerUpgradeText.setCharacterSize(25);
        this->superPowerUpgradeText.setFillColor(sf::Color(254, 250, 224));
    }

    // Money text
    std::string moneyString = std::to_string(this->player->money);
    this->moneyText.setString(moneyString);
    this->moneyText.setFont(this->menuFont);
    this->moneyText.setCharacterSize(40);
    this->moneyText.setFillColor(sf::Color(254, 250, 224));
    this->moneyText.setPosition(sf::Vector2f(0.5 * this->desktopSize.width, 0.03 * this->desktopSize.height));

    // Money sprite    
    moneyTextTexture.loadFromFile("assets/shop/coins.png");
    moneyTextTexture.setSmooth(true);
    moneyTextSprite.setTexture(this->moneyTextTexture);
    moneyTextSprite.setPosition(sf::Vector2f(0.35 * this->desktopSize.width, 0.04 * this->desktopSize.height));
    for (int i = 0; i < 5; i++)
    {
        this->moneyUpgradeSprite.push_back(moneyTextSprite);
    }
    this->moneyUpgradeSprite[0].setPosition(sf::Vector2f(0.34 * this->desktopSize.width, 0.7 * this->desktopSize.height));
    this->moneyUpgradeSprite[1].setPosition(sf::Vector2f(0.34 * this->desktopSize.width, 0.8 * this->desktopSize.height));
    this->moneyUpgradeSprite[2].setPosition(sf::Vector2f(0.34 * this->desktopSize.width, 0.9 * this->desktopSize.height));
    this->moneyUpgradeSprite[3].setPosition(sf::Vector2f(0.88 * this->desktopSize.width, 0.7 * this->desktopSize.height));
    this->moneyUpgradeSprite[4].setPosition(sf::Vector2f(0.88 * this->desktopSize.width, 0.8 * this->desktopSize.height));

    this->moneyTextTexture.loadFromFile("assets/shop/coins.png");
    this->moneyTextTexture.setSmooth(true);
    this->moneyTextSprite.setTexture(this->moneyTextTexture);
    this->moneyTextSprite.setPosition(sf::Vector2f(0.47 * this->desktopSize.width, 0.04 * this->desktopSize.height));
}

void Shop::openShop(sf::RectangleShape* button, sf::RenderWindow* window, bool* isMenuWindowOpen)
{
    float buttonX = button->getPosition().x;
    float buttonY = button->getPosition().y;
    float buttonWidth = button->getGlobalBounds().width;
    float buttonHeight = button->getGlobalBounds().height;

    float mousePositionX = sf::Mouse::getPosition().x;
    float mousePositionY = sf::Mouse::getPosition().y;

    std::string moneyString = std::to_string(this->player->money);
    this->moneyText.setString(moneyString);

    if (mousePositionX >= buttonX && mousePositionX <= (buttonX + buttonWidth) && mousePositionY >= buttonY && mousePositionY <= (buttonY + buttonHeight))
    {
        this->isShopOpen = true;
        *isMenuWindowOpen = false;
        for (int i = 0; i < this->allyVector->size(); i++)
        {
            this->allyVector->at(i).setStatistics(i);
        }
        this->drawShop(window);
    }
}

void Shop::closeShop(bool* isMenuWindowOpen)
{
    float buttonX = this->leftArrowButton.getPosition().x;
    float buttonY = this->leftArrowButton.getPosition().y;
    float buttonWidth = this->leftArrowButton.getGlobalBounds().width;
    float buttonHeight = this->leftArrowButton.getGlobalBounds().height;

    float mousePositionX = sf::Mouse::getPosition().x;
    float mousePositionY = sf::Mouse::getPosition().y;

    if (mousePositionX >= buttonX && mousePositionX <= (buttonX + buttonWidth) && mousePositionY >= buttonY && mousePositionY <= (buttonY + buttonHeight))
    {
        this->file.open("saves/player.txt", std::ios::in | std::ios::out);
        if (this->file.good() == true)
        {
            this->file << "money=" << std::to_string(player->money) << "\n";
        }
        this->file.close();

        this->file.open("saves/backslider1.txt", std::ios::in | std::ios::out);
        if (this->file.good() == true)
        {
            this->file << "isUnlocked=" << std::to_string(allyVector->at(0).isUnlocked) << "\n";
            this->file << "armorLevel=" << std::to_string(allyVector->at(0).armorLevel) << "\n";
            this->file << "lifeLevel=" << std::to_string(allyVector->at(0).lifeLevel) << "\n";
            this->file << "magicResistLevel=" << std::to_string(allyVector->at(0).magicResistLevel) << "\n";
            this->file << "powerLevel=" << std::to_string(allyVector->at(0).powerLevel) << "\n";
            this->file << "superPowerLevel=" << std::to_string(allyVector->at(0).superPowerLevel) << "\n";
        }
        this->file.close();

        this->file.open("saves/backslider2.txt", std::ios::in | std::ios::out);
        if (this->file.good() == true)
        {
            this->file << "isUnlocked=" << std::to_string(allyVector->at(1).isUnlocked) << "\n";
            this->file << "armorLevel=" << std::to_string(allyVector->at(1).armorLevel) << "\n";
            this->file << "lifeLevel=" << std::to_string(allyVector->at(1).lifeLevel) << "\n";
            this->file << "magicResistLevel=" << std::to_string(allyVector->at(1).magicResistLevel) << "\n";
            this->file << "powerLevel=" << std::to_string(allyVector->at(1).powerLevel) << "\n";
            this->file << "superPowerLevel=" << std::to_string(allyVector->at(1).superPowerLevel) << "\n";
        }
        this->file.close();

        this->file.open("saves/backslider3.txt", std::ios::in | std::ios::out);
        if (this->file.good() == true)
        {
            this->file << "isUnlocked=" << std::to_string(allyVector->at(2).isUnlocked) << "\n";
            this->file << "armorLevel=" << std::to_string(allyVector->at(2).armorLevel) << "\n";
            this->file << "lifeLevel=" << std::to_string(allyVector->at(2).lifeLevel) << "\n";
            this->file << "magicResistLevel=" << std::to_string(allyVector->at(2).magicResistLevel) << "\n";
            this->file << "powerLevel=" << std::to_string(allyVector->at(2).powerLevel) << "\n";
            this->file << "superPowerLevel=" << std::to_string(allyVector->at(2).superPowerLevel) << "\n";
        }
        this->file.close();

        this->isShopOpen = false;
        *isMenuWindowOpen = true;
    }
}

void Shop::drawShop(sf::RenderWindow* window)
{
    window->clear(sf::Color(96, 108, 56));
    
    window->draw(this->leftArrowButton);
    
    window->draw(this->shopText);
    
    pickCharacter();
    window->draw(this->pickCharacterGlow);

    for (int i = 0; i < this->characterSprites.size(); i++)
    {
        window->draw(this->characterSprites[i]);
    }

    if (this->unlockedCharacter)
    {
        this->blockCharacter();
        this->upgradeCharacter();
        
        for (int i = 0; i < this->blockedSprites.size(); i++)
        {
            window->draw(this->blockedSprites[i]);
        }

        window->draw(this->lifeSprite);
        window->draw(this->lifeText);
        window->draw(this->powerSprite);
        window->draw(this->powerText);
        window->draw(this->armorSprite);
        window->draw(this->armorText);
        window->draw(this->magicResistSprite);
        window->draw(this->magicResistText);
        window->draw(this->superPowerSprite);
        window->draw(this->superPowerText);

        window->draw(this->lifeUpgradeSprite);
        window->draw(this->lifeUpgradeText);
        window->draw(this->powerUpgradeSprite);
        window->draw(this->powerUpgradeText);
        window->draw(this->armorUpgradeSprite);
        window->draw(this->armorUpgradeText);
        window->draw(this->magicResistUpgradeSprite);
        window->draw(this->magicResistUpgradeText);
        window->draw(this->superPowerUpgradeSprite);
        window->draw(this->superPowerUpgradeText);

        window->draw(this->lifeUpgradeCostText);
        window->draw(this->armorUpgradeCostText);
        window->draw(this->magicResistUpgradeCostText);
        window->draw(this->powerUpgradeCostText);
        window->draw(this->superPowerUpgradeCostText);

        for (int i = 0; i < this->possibleUpgrade.size(); i++) {
            if (possibleUpgrade[i] == true)
            {
                window->draw(this->upgradeButtonVector.at(i));
            }
        }
        for (int i = 0; i < this->moneyUpgradeSprite.size(); i++)
        {
            window->draw(this->moneyUpgradeSprite[i]);
        }
    }
    else
    {
        if (this->enoughMoney)
        {
            this->unlockCharacter();
            this->blockCharacter();
            if (!(this->allyVector->at(this->pickedCharacter).isUnlocked))
            {
                window->draw(this->buyButton);
                window->draw(this->buyButtonText);
                window->draw(this->lockedCharacterText);
                for (int i = 0; i < this->blockedSprites.size(); i++)
                {
                    window->draw(this->blockedSprites[i]);
                }
            }
            else
            {
                this->blockCharacter();
                this->upgradeCharacter();

                for (int i = 0; i < this->blockedSprites.size(); i++)
                {
                    window->draw(this->blockedSprites[i]);
                }

                window->draw(this->lifeSprite);
                window->draw(this->lifeText);
                window->draw(this->powerSprite);
                window->draw(this->powerText);
                window->draw(this->armorSprite);
                window->draw(this->armorText);
                window->draw(this->magicResistSprite);
                window->draw(this->magicResistText);
                window->draw(this->superPowerSprite);
                window->draw(this->superPowerText);

                window->draw(this->lifeUpgradeSprite);
                window->draw(this->lifeUpgradeText);
                window->draw(this->powerUpgradeSprite);
                window->draw(this->powerUpgradeText);
                window->draw(this->armorUpgradeSprite);
                window->draw(this->armorUpgradeText);
                window->draw(this->magicResistUpgradeSprite);
                window->draw(this->magicResistUpgradeText);
                window->draw(this->superPowerUpgradeSprite);
                window->draw(this->superPowerUpgradeText);

                window->draw(this->lifeUpgradeCostText);
                window->draw(this->armorUpgradeCostText);
                window->draw(this->magicResistUpgradeCostText);
                window->draw(this->powerUpgradeCostText);
                window->draw(this->superPowerUpgradeCostText);

                for (int i = 0; i < this->possibleUpgrade.size(); i++) {
                    if (possibleUpgrade[i] == true)
                    {
                        window->draw(this->upgradeButtonVector.at(i));
                    }
                }
            }
        }
        else
        {
            this->blockCharacter();
            for (int i = 0; i < this->blockedSprites.size(); i++)
            {
                window->draw(this->blockedSprites[i]);
            }
            window->draw(this->lockedCharacterText);
            window->draw(this->noMoneyText);
        }
    }

    window->draw(this->moneyText);
    window->draw(this->moneyTextSprite);

    window->display();
}

void Shop::pickCharacter()
{
    if (this->characterSprites[0].getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y)))
    {
        this->pickedCharacter = 0;
        this->pickCharacterGlow.setPosition(sf::Vector2f(0.1 * this->desktopSize.width, 0.21 * this->desktopSize.height));

        this->unlockedCharacter = this->allyVector->at(0).isUnlocked;
        this->enoughMoney = true;

        this->lifeText.setString(std::to_string(int(this->allyVector->at(this->pickedCharacter).life)));
        this->powerText.setString(std::to_string(int(this->allyVector->at(this->pickedCharacter).power)));
        this->armorText.setString(std::to_string(int(this->allyVector->at(this->pickedCharacter).armor)));
        this->magicResistText.setString(std::to_string(int(this->allyVector->at(this->pickedCharacter).magicResist)));
        this->superPowerText.setString(std::to_string(this->allyVector->at(this->pickedCharacter).superPower).substr(0, 3));

        // LIFE LEVEL
        std::string lifeLevel = std::to_string(this->allyVector->at(this->pickedCharacter).lifeLevel);
        std::string lifeNextLevel = "( + ";
        if (this->allyVector->at(this->pickedCharacter).lifeLevel == 1)
        {
            lifeNextLevel += "150 )";
            this->lifeUpgradeCostText.setString(std::to_string(int(this->allyVector->at(this->pickedCharacter).life) + 150));
            this->lifeUpgradeCostText.setCharacterSize(25);
            this->lifeUpgradeCostText.setFont(this->menuFont);
            this->lifeUpgradeCostText.setPosition(sf::Vector2f(0.36 * this->desktopSize.width, 0.7 * this->desktopSize.height));
            this->lifeUpgradeCostText.setFillColor(sf::Color(254, 250, 224));
            if (this->allyVector->at(this->pickedCharacter).life + 150 <= this->player->money)
            {
                this->possibleUpgrade[0] = true;
            }
            else
            {
                this->possibleUpgrade[0] = false;
            }
        }
        else if (this->allyVector->at(this->pickedCharacter).lifeLevel > 1 && this->allyVector->at(this->pickedCharacter).lifeLevel < 7)
        {
            lifeNextLevel += "250 )";
            this->lifeUpgradeCostText.setString(std::to_string(int(this->allyVector->at(this->pickedCharacter).life) + 250));
            this->lifeUpgradeCostText.setCharacterSize(25);
            this->lifeUpgradeCostText.setFont(this->menuFont);
            this->lifeUpgradeCostText.setPosition(sf::Vector2f(0.36 * this->desktopSize.width, 0.7 * this->desktopSize.height));
            this->lifeUpgradeCostText.setFillColor(sf::Color(254, 250, 224));
            if (this->allyVector->at(this->pickedCharacter).life + 250 <= this->player->money)
            {
                this->possibleUpgrade[0] = true;
            }
            else
            {
                this->possibleUpgrade[0] = false;
            }
        }
        else if (this->allyVector->at(this->pickedCharacter).lifeLevel == 7)
        {
            lifeNextLevel += "1000 )";
            this->lifeUpgradeCostText.setString(std::to_string(int(this->allyVector->at(this->pickedCharacter).life) + 1000));
            this->lifeUpgradeCostText.setCharacterSize(25);
            this->lifeUpgradeCostText.setFont(this->menuFont);
            this->lifeUpgradeCostText.setPosition(sf::Vector2f(0.36 * this->desktopSize.width, 0.7 * this->desktopSize.height));
            this->lifeUpgradeCostText.setFillColor(sf::Color(254, 250, 224));
            if (this->allyVector->at(this->pickedCharacter).life + 1000 <= this->player->money)
            {
                this->possibleUpgrade[0] = true;
            }
            else
            {
                this->possibleUpgrade[0] = false;
            }
        }
        else
        {
            lifeNextLevel += "2500 )";
            this->lifeUpgradeCostText.setString(std::to_string(this->allyVector->at(this->pickedCharacter).life + 2500));
            this->lifeUpgradeCostText.setCharacterSize(25);
            this->lifeUpgradeCostText.setFont(this->menuFont);
            this->lifeUpgradeCostText.setPosition(sf::Vector2f(0.36 * this->desktopSize.width, 0.7 * this->desktopSize.height));
            this->lifeUpgradeCostText.setFillColor(sf::Color(254, 250, 224));
            if (this->allyVector->at(this->pickedCharacter).life + 2500 <= this->player->money)
            {
                this->possibleUpgrade[0] = true;
            }
            else
            {
                this->possibleUpgrade[0] = false;
            }
        }
        if (this->allyVector->at(this->pickedCharacter).lifeLevel != 10)
        {
            this->lifeUpgradeText.setString("LIFE  LEVEL:  " + lifeLevel + "\n" + "NEXT  LEVEL:  " + lifeNextLevel);
        }
        else
        {
            this->lifeUpgradeText.setString("LIFE  LEVEL:  MAX");
            this->possibleUpgrade[0] = false;
            this->lifeUpgradeText.setPosition(sf::Vector2f(0.15 * this->desktopSize.width, 0.705 * this->desktopSize.height));
        }
        // POWER LEVEL
        std::string powerLevel = std::to_string(this->allyVector->at(this->pickedCharacter).powerLevel);
        std::string powerNextLevel = "( + 10 )";
        this->powerUpgradeCostText.setString(std::to_string(int(this->allyVector->at(this->pickedCharacter).power * pow(this->allyVector->at(this->pickedCharacter).powerLevel, 2))));
        this->powerUpgradeCostText.setCharacterSize(25);
        this->powerUpgradeCostText.setFont(this->menuFont);
        this->powerUpgradeCostText.setPosition(sf::Vector2f(0.9 * this->desktopSize.width, 0.7 * this->desktopSize.height));
        this->powerUpgradeCostText.setFillColor(sf::Color(254, 250, 224));
        if (this->allyVector->at(this->pickedCharacter).power * pow(this->allyVector->at(this->pickedCharacter).powerLevel,2) <= this->player->money)
        {
            this->possibleUpgrade[3] = true;
        }
        else
        {
            this->possibleUpgrade[3] = false;
        }
        if (this->allyVector->at(this->pickedCharacter).powerLevel != 10)
        {
            this->powerUpgradeText.setString("POWER  LEVEL:  " + powerLevel + "\n" + "NEXT  LEVEL:  " + powerNextLevel);
        }
        else
        {
            this->powerUpgradeText.setString("POWER  LEVEL:  MAX");
            this->possibleUpgrade[3] = false;
            this->powerUpgradeText.setPosition(sf::Vector2f(0.55 * this->desktopSize.width, 0.705 * this->desktopSize.height));
        }
        // ARMOR LEVEL
        std::string armorLevel = std::to_string(this->allyVector->at(this->pickedCharacter).armorLevel);
        std::string armorNextLevel = "( + ";
        this->armorUpgradeCostText.setString(std::to_string(int(this->allyVector->at(this->pickedCharacter).armor* pow(this->allyVector->at(this->pickedCharacter).armorLevel, 2))));
        this->armorUpgradeCostText.setCharacterSize(25);
        this->armorUpgradeCostText.setFont(this->menuFont);
        this->armorUpgradeCostText.setPosition(sf::Vector2f(0.36 * this->desktopSize.width, 0.8 * this->desktopSize.height));
        this->armorUpgradeCostText.setFillColor(sf::Color(254, 250, 224));
        if (this->allyVector->at(this->pickedCharacter).armor * pow(this->allyVector->at(this->pickedCharacter).armorLevel, 2) <= this->player->money)
        {
            this->possibleUpgrade[1] = true;
        }
        else
        {
            this->possibleUpgrade[1] = false;
        }
        if (this->allyVector->at(this->pickedCharacter).armorLevel < 8)
        {
            armorNextLevel += "5 )";
        }
        else
        {
            armorNextLevel += "25 )";
        }
        if (this->allyVector->at(this->pickedCharacter).armorLevel != 10)
        {
            this->armorUpgradeText.setString("ARMOR  LEVEL:  " + armorLevel + "\n" + "NEXT  LEVEL:  " + armorNextLevel);
        }
        else
        {
            this->armorUpgradeText.setString("ARMOR  LEVEL:  MAX");
            this->possibleUpgrade[1] = false;
            this->armorUpgradeText.setPosition(sf::Vector2f(0.15 * this->desktopSize.width, 0.805 * this->desktopSize.height));
        }
        // MAGIC RESIST LEVEL
        std::string magicResistLevel = std::to_string(this->allyVector->at(this->pickedCharacter).magicResistLevel);
        std::string magicResistNextLevel = "( + ";
        this->magicResistUpgradeCostText.setString(std::to_string(int(this->allyVector->at(this->pickedCharacter).magicResist* pow(this->allyVector->at(this->pickedCharacter).magicResistLevel, 2))));
        this->magicResistUpgradeCostText.setCharacterSize(25);
        this->magicResistUpgradeCostText.setFont(this->menuFont);
        this->magicResistUpgradeCostText.setPosition(sf::Vector2f(0.9 * this->desktopSize.width, 0.8 * this->desktopSize.height));
        this->magicResistUpgradeCostText.setFillColor(sf::Color(254, 250, 224));
        if (this->allyVector->at(this->pickedCharacter).magicResist * pow(this->allyVector->at(this->pickedCharacter).magicResistLevel, 2) <= this->player->money)
        {
            this->possibleUpgrade[4] = true;
        }
        else
        {
            this->possibleUpgrade[4] = false;
        }
        if (this->allyVector->at(this->pickedCharacter).magicResistLevel < 8)
        {
            magicResistNextLevel += "5 )";
        }
        else
        {
            magicResistNextLevel += "25 )";
        }
        if (this->allyVector->at(this->pickedCharacter).magicResistLevel != 10)
        {
            this->magicResistUpgradeText.setString("MAGIC  RESIST  LEVEL:  " + magicResistLevel + "\n" + "NEXT  LEVEL:  " + magicResistNextLevel);
        }
        else
        {
            this->magicResistUpgradeText.setString("MAGIC  RESIST  LEVEL:  MAX");
            this->possibleUpgrade[4] = false;
            this->magicResistUpgradeText.setPosition(sf::Vector2f(0.55 * this->desktopSize.width, 0.805 * this->desktopSize.height));
        }
        // SUPER POWER LEVEL
        std::string superPowerLevel = std::to_string(this->allyVector->at(this->pickedCharacter).superPowerLevel);
        std::string superPowerNextLevel = "( + 0.5 )";
        this->superPowerUpgradeCostText.setString(std::to_string((this->allyVector->at(this->pickedCharacter).superPowerLevel) * 500));
        this->superPowerUpgradeCostText.setCharacterSize(25);
        this->superPowerUpgradeCostText.setFont(this->menuFont);
        this->superPowerUpgradeCostText.setPosition(sf::Vector2f(0.36 * this->desktopSize.width, 0.9 * this->desktopSize.height));
        this->superPowerUpgradeCostText.setFillColor(sf::Color(254, 250, 224));
        if ((this->allyVector->at(this->pickedCharacter).superPowerLevel) * 500 <= this->player->money)
        {
            this->possibleUpgrade[2] = true;
        }
        else
        {
            this->possibleUpgrade[2] = false;
        }
        if (this->allyVector->at(this->pickedCharacter).superPowerLevel != 10)
        {
            this->superPowerUpgradeText.setString("SUPER  POWER  LEVEL:  " + superPowerLevel + "\n" + "NEXT  LEVEL:  " + superPowerNextLevel);
        }
        else
        {
            this->superPowerUpgradeText.setString("SUPER  POWER  LEVEL:  MAX");
            this->possibleUpgrade[2] = false;
            this->superPowerUpgradeText.setPosition(sf::Vector2f(0.15 * this->desktopSize.width, 0.905 * this->desktopSize.height));
        }
    }
    else if (this->characterSprites[1].getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y)))
    {
        this->pickedCharacter = 1;
        this->pickCharacterGlow.setPosition(sf::Vector2f(0.4 * this->desktopSize.width, 0.21 * this->desktopSize.height));

        this->unlockedCharacter = this->allyVector->at(1).isUnlocked;
        if (this->player->money >= 10000)
        {
            this->enoughMoney = true;
        }
        else
        {
            this->enoughMoney = false;
        }

        // LIFE LEVEL
        std::string lifeLevel = std::to_string(this->allyVector->at(this->pickedCharacter).lifeLevel);
        std::string lifeNextLevel = "( + ";
        if (this->allyVector->at(this->pickedCharacter).lifeLevel == 1)
        {
            lifeNextLevel += "1500 )";
            this->lifeUpgradeCostText.setString(std::to_string(int(this->allyVector->at(this->pickedCharacter).life + 1500)));
            this->lifeUpgradeCostText.setCharacterSize(25);
            this->lifeUpgradeCostText.setFont(this->menuFont);
            this->lifeUpgradeCostText.setPosition(sf::Vector2f(0.36 * this->desktopSize.width, 0.7 * this->desktopSize.height));
            this->lifeUpgradeCostText.setFillColor(sf::Color(254, 250, 224));
            if (this->allyVector->at(this->pickedCharacter).life + 1500 <= this->player->money)
            {
                this->possibleUpgrade[0] = true;
            }
            else
            {
                this->possibleUpgrade[0] = false;
            }
        }
        else if (this->allyVector->at(this->pickedCharacter).lifeLevel > 1 && this->allyVector->at(this->pickedCharacter).lifeLevel < 5)
        {
            lifeNextLevel += "2500 )";
            this->lifeUpgradeCostText.setString(std::to_string(int(this->allyVector->at(this->pickedCharacter).life + 2500)));
            this->lifeUpgradeCostText.setCharacterSize(25);
            this->lifeUpgradeCostText.setFont(this->menuFont);
            this->lifeUpgradeCostText.setPosition(sf::Vector2f(0.36 * this->desktopSize.width, 0.7 * this->desktopSize.height));
            this->lifeUpgradeCostText.setFillColor(sf::Color(254, 250, 224));
            if (this->allyVector->at(this->pickedCharacter).life + 2500 <= this->player->money)
            {
                this->possibleUpgrade[0] = true;
            }
            else
            {
                this->possibleUpgrade[0] = false;
            }
        }
        else
        {
            lifeNextLevel += "2000 )";
            this->lifeUpgradeCostText.setString(std::to_string(int(this->allyVector->at(this->pickedCharacter).life + 2000)));
            this->lifeUpgradeCostText.setCharacterSize(25);
            this->lifeUpgradeCostText.setFont(this->menuFont);
            this->lifeUpgradeCostText.setPosition(sf::Vector2f(0.36 * this->desktopSize.width, 0.7 * this->desktopSize.height));
            this->lifeUpgradeCostText.setFillColor(sf::Color(254, 250, 224));
            if (this->allyVector->at(this->pickedCharacter).life + 2000 <= this->player->money)
            {
                this->possibleUpgrade[0] = true;
            }
            else
            {
                this->possibleUpgrade[0] = false;
            }
        }
        if (this->allyVector->at(this->pickedCharacter).lifeLevel != 10)
        {
            this->lifeUpgradeText.setString("LIFE  LEVEL:  " + lifeLevel + "\n" + "NEXT  LEVEL:  " + lifeNextLevel);
        }
        else
        {
            this->lifeUpgradeText.setString("LIFE  LEVEL:  MAX");
            this->possibleUpgrade[0] = false;
            this->lifeUpgradeText.setPosition(sf::Vector2f(0.15 * this->desktopSize.width, 0.705 * this->desktopSize.height));
        }
        // POWER LEVEL
        std::string powerLevel = std::to_string(this->allyVector->at(this->pickedCharacter).powerLevel);
        std::string powerNextLevel = "( + ";
        this->powerUpgradeCostText.setString(std::to_string(int(this->allyVector->at(this->pickedCharacter).power* pow(this->allyVector->at(this->pickedCharacter).powerLevel, 2))));
        this->powerUpgradeCostText.setCharacterSize(25);
        this->powerUpgradeCostText.setFont(this->menuFont);
        this->powerUpgradeCostText.setPosition(sf::Vector2f(0.9 * this->desktopSize.width, 0.7 * this->desktopSize.height));
        this->powerUpgradeCostText.setFillColor(sf::Color(254, 250, 224));
        if (this->allyVector->at(this->pickedCharacter).power * pow(this->allyVector->at(this->pickedCharacter).powerLevel, 2) <= this->player->money)
        {
            this->possibleUpgrade[3] = true;
        }
        else
        {
            this->possibleUpgrade[3] = false;
        }
        if (this->allyVector->at(this->pickedCharacter).powerLevel < 7)
        {
            powerNextLevel += "25 )";
        }
        else
        {
            powerNextLevel += "50 )";
        }
        if (this->allyVector->at(this->pickedCharacter).powerLevel != 10)
        {
            this->powerUpgradeText.setString("POWER  LEVEL:  " + powerLevel + "\n" + "NEXT  LEVEL:  " + powerNextLevel);
        }
        else
        {
            this->powerUpgradeText.setString("POWER  LEVEL:  MAX");
            this->possibleUpgrade[3] = false;
            this->powerUpgradeText.setPosition(sf::Vector2f(0.55 * this->desktopSize.width, 0.705 * this->desktopSize.height));
        }
        // ARMOR LEVEL
        std::string armorLevel = std::to_string(this->allyVector->at(this->pickedCharacter).armorLevel);
        std::string armorNextLevel = "( + ";
        this->armorUpgradeCostText.setString(std::to_string(int(this->allyVector->at(this->pickedCharacter).armor * pow(this->allyVector->at(this->pickedCharacter).armorLevel, 2))));
        this->armorUpgradeCostText.setCharacterSize(25);
        this->armorUpgradeCostText.setFont(this->menuFont);
        this->armorUpgradeCostText.setPosition(sf::Vector2f(0.36 * this->desktopSize.width, 0.8 * this->desktopSize.height));
        this->armorUpgradeCostText.setFillColor(sf::Color(254, 250, 224));
        if (this->allyVector->at(this->pickedCharacter).armor * pow(this->allyVector->at(this->pickedCharacter).armorLevel, 2) <= this->player->money)
        {
            this->possibleUpgrade[1] = true;
        }
        else
        {
            this->possibleUpgrade[1] = false;
        }
        if (this->allyVector->at(this->pickedCharacter).armorLevel < 6)
        {
            armorNextLevel += "10 )";
        }
        else if (this->allyVector->at(this->pickedCharacter).armorLevel > 5 && this->allyVector->at(this->pickedCharacter).armorLevel < 9)
        {
            armorNextLevel += "25 )";
        }
        else
        {
            armorNextLevel += "50 )";
        }
        if (this->allyVector->at(this->pickedCharacter).armorLevel != 10)
        {
            this->armorUpgradeText.setString("ARMOR  LEVEL:  " + armorLevel + "\n" + "NEXT  LEVEL:  " + armorNextLevel);
        }
        else
        {
            this->armorUpgradeText.setString("ARMOR  LEVEL:  MAX");
            this->possibleUpgrade[1] = false;
            this->armorUpgradeText.setPosition(sf::Vector2f(0.15 * this->desktopSize.width, 0.805 * this->desktopSize.height));
        }
        // MAGIC RESIST LEVEL
        std::string magicResistLevel = std::to_string(this->allyVector->at(this->pickedCharacter).magicResistLevel);
        std::string magicResistNextLevel = "( + ";
        this->magicResistUpgradeCostText.setString(std::to_string(int(this->allyVector->at(this->pickedCharacter).magicResist* pow(this->allyVector->at(this->pickedCharacter).magicResistLevel, 2))));
        this->magicResistUpgradeCostText.setCharacterSize(25);
        this->magicResistUpgradeCostText.setFont(this->menuFont);
        this->magicResistUpgradeCostText.setPosition(sf::Vector2f(0.9 * this->desktopSize.width, 0.8 * this->desktopSize.height));
        this->magicResistUpgradeCostText.setFillColor(sf::Color(254, 250, 224));
        if (this->allyVector->at(this->pickedCharacter).magicResist * pow(this->allyVector->at(this->pickedCharacter).magicResistLevel, 2) <= this->player->money)
        {
            this->possibleUpgrade[4] = true;
        }
        else
        {
            this->possibleUpgrade[4] = false;
        }
        if (this->allyVector->at(this->pickedCharacter).magicResistLevel < 6)
        {
            magicResistNextLevel += "10 )";
        }
        else if (this->allyVector->at(this->pickedCharacter).magicResistLevel > 5 && this->allyVector->at(this->pickedCharacter).magicResistLevel < 9)
        {
            magicResistNextLevel += "25 )";
        }
        else
        {
            magicResistNextLevel += "50 )";
        }
        if (this->allyVector->at(this->pickedCharacter).magicResistLevel != 10)
        {
            this->magicResistUpgradeText.setString("MAGIC  RESIST  LEVEL:  " + magicResistLevel + "\n" + "NEXT  LEVEL:  " + magicResistNextLevel);
        }
        else
        {
            this->magicResistUpgradeText.setString("MAGIC  RESIST  LEVEL:  MAX");
            this->possibleUpgrade[4] = false;
            this->magicResistUpgradeText.setPosition(sf::Vector2f(0.55 * this->desktopSize.width, 0.805 * this->desktopSize.height));
        }
        // SUPER POWER LEVEL
        std::string superPowerLevel = std::to_string(this->allyVector->at(this->pickedCharacter).superPowerLevel);
        std::string superPowerNextLevel = "( + 0.5 )";
        this->superPowerUpgradeCostText.setString(std::to_string(int((this->allyVector->at(this->pickedCharacter).superPowerLevel) * 1000)));
        this->superPowerUpgradeCostText.setCharacterSize(25);
        this->superPowerUpgradeCostText.setFont(this->menuFont);
        this->superPowerUpgradeCostText.setPosition(sf::Vector2f(0.36 * this->desktopSize.width, 0.9 * this->desktopSize.height));
        this->superPowerUpgradeCostText.setFillColor(sf::Color(254, 250, 224));
        if (this->allyVector->at(this->pickedCharacter).superPowerLevel * 1000 <= this->player->money)
        {
            this->possibleUpgrade[2] = true;
        }
        else
        {
            this->possibleUpgrade[2] = false;
        }
        if (this->allyVector->at(this->pickedCharacter).superPowerLevel != 10)
        {
            this->superPowerUpgradeText.setString("SUPER  POWER  LEVEL:  " + superPowerLevel + "\n" + "NEXT  LEVEL:  " + superPowerNextLevel);
        }
        else
        {
            this->superPowerUpgradeText.setString("SUPER  POWER  LEVEL:  MAX");
            this->possibleUpgrade[2] = false;
            this->superPowerUpgradeText.setPosition(sf::Vector2f(0.15 * this->desktopSize.width, 0.905 * this->desktopSize.height));
        }
    }
    else if (this->characterSprites[2].getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y)))
    {
        this->pickedCharacter = 2;
        this->pickCharacterGlow.setPosition(sf::Vector2f(0.7 * this->desktopSize.width, 0.21 * this->desktopSize.height));
    
        this->unlockedCharacter = this->allyVector->at(2).isUnlocked;
        if (this->player->money > 25000)
        {
            this->enoughMoney = true;
        }
        else
        {
            this->enoughMoney = false;
        }

        // LIFE LEVEL
        std::string lifeLevel = std::to_string(this->allyVector->at(this->pickedCharacter).lifeLevel);
        std::string lifeNextLevel = "( + ";
        if (this->allyVector->at(this->pickedCharacter).lifeLevel < 5)
        {
            lifeNextLevel += "5000 )";
            this->lifeUpgradeCostText.setString(std::to_string(int(this->allyVector->at(this->pickedCharacter).life + 5000)));
            this->lifeUpgradeCostText.setCharacterSize(25);
            this->lifeUpgradeCostText.setFont(this->menuFont);
            this->lifeUpgradeCostText.setPosition(sf::Vector2f(0.36 * this->desktopSize.width, 0.7 * this->desktopSize.height));
            this->lifeUpgradeCostText.setFillColor(sf::Color(254, 250, 224));
            if (this->allyVector->at(this->pickedCharacter).life + 5000 <= this->player->money)
            {
                this->possibleUpgrade[0] = true;
            }
            else
            {
                this->possibleUpgrade[0] = false;
            }
        }
        else
        {
            lifeNextLevel += "2500 )";
            this->lifeUpgradeCostText.setString(std::to_string(int(this->allyVector->at(this->pickedCharacter).life + 2500)));
            this->lifeUpgradeCostText.setCharacterSize(25);
            this->lifeUpgradeCostText.setFont(this->menuFont);
            this->lifeUpgradeCostText.setPosition(sf::Vector2f(0.36 * this->desktopSize.width, 0.7 * this->desktopSize.height));
            this->lifeUpgradeCostText.setFillColor(sf::Color(254, 250, 224));
            if (this->allyVector->at(this->pickedCharacter).life + 2500 <= this->player->money)
            {
                this->possibleUpgrade[0] = true;
            }
            else
            {
                this->possibleUpgrade[0] = false;
            }
        }
        if (this->allyVector->at(this->pickedCharacter).lifeLevel != 10)
        {
            this->lifeUpgradeText.setString("LIFE  LEVEL:  " + lifeLevel + "\n" + "NEXT  LEVEL:  " + lifeNextLevel);
        }
        else
        {
            this->lifeUpgradeText.setString("LIFE  LEVEL:  MAX");
            this->possibleUpgrade[0] = false;
            this->lifeUpgradeText.setPosition(sf::Vector2f(0.15 * this->desktopSize.width, 0.705 * this->desktopSize.height));
        }
        // POWER LEVEL
        std::string powerLevel = std::to_string(this->allyVector->at(this->pickedCharacter).powerLevel);
        std::string powerNextLevel = "( + 100 )";
        this->powerUpgradeCostText.setString(std::to_string(int(this->allyVector->at(this->pickedCharacter).power* pow(this->allyVector->at(this->pickedCharacter).powerLevel, 2))));
        this->powerUpgradeCostText.setCharacterSize(25);
        this->powerUpgradeCostText.setFont(this->menuFont);
        this->powerUpgradeCostText.setPosition(sf::Vector2f(0.9 * this->desktopSize.width, 0.7 * this->desktopSize.height));
        this->powerUpgradeCostText.setFillColor(sf::Color(254, 250, 224));
        if (this->allyVector->at(this->pickedCharacter).power * pow(this->allyVector->at(this->pickedCharacter).powerLevel, 2) <= this->player->money)
        {
            this->possibleUpgrade[3] = true;
        }
        else
        {
            this->possibleUpgrade[3] = false;
        }
        if (this->allyVector->at(this->pickedCharacter).powerLevel != 10)
        {
            this->powerUpgradeText.setString("POWER  LEVEL:  " + powerLevel + "\n" + "NEXT  LEVEL:  " + powerNextLevel);
        }
        else
        {
            this->powerUpgradeText.setString("POWER  LEVEL:  MAX");
            this->possibleUpgrade[3] = false;
            this->powerUpgradeText.setPosition(sf::Vector2f(0.55 * this->desktopSize.width, 0.705 * this->desktopSize.height));
        }
        // ARMOR LEVEL
        std::string armorLevel = std::to_string(this->allyVector->at(this->pickedCharacter).armorLevel);
        std::string armorNextLevel = "( + 50 )";
        this->armorUpgradeCostText.setString(std::to_string(int(this->allyVector->at(this->pickedCharacter).armor* pow(this->allyVector->at(this->pickedCharacter).armorLevel, 2))));
        this->armorUpgradeCostText.setCharacterSize(25);
        this->armorUpgradeCostText.setFont(this->menuFont);
        this->armorUpgradeCostText.setPosition(sf::Vector2f(0.36 * this->desktopSize.width, 0.8 * this->desktopSize.height));
        this->armorUpgradeCostText.setFillColor(sf::Color(254, 250, 224));
        if (this->allyVector->at(this->pickedCharacter).armor * pow(this->allyVector->at(this->pickedCharacter).armorLevel, 2) <= this->player->money)
        {
            this->possibleUpgrade[1] = true;
        }
        else
        {
            this->possibleUpgrade[1] = false;
        }
        if (this->allyVector->at(this->pickedCharacter).armorLevel != 10)
        {
            this->armorUpgradeText.setString("ARMOR  LEVEL:  " + armorLevel + "\n" + "NEXT  LEVEL:  " + armorNextLevel);
        }
        else
        {
            this->armorUpgradeText.setString("ARMOR  LEVEL:  MAX");
            this->possibleUpgrade[1] = false;
            this->armorUpgradeText.setPosition(sf::Vector2f(0.15 * this->desktopSize.width, 0.805 * this->desktopSize.height));
        }
        // MAGIC RESIST LEVEL
        std::string magicResistLevel = std::to_string(this->allyVector->at(this->pickedCharacter).magicResistLevel);
        std::string magicResistNextLevel = "( + 50 )";
        this->magicResistUpgradeCostText.setString(std::to_string(int(this->allyVector->at(this->pickedCharacter).magicResist * pow(this->allyVector->at(this->pickedCharacter).magicResistLevel, 2))));
        this->magicResistUpgradeCostText.setCharacterSize(25);
        this->magicResistUpgradeCostText.setFont(this->menuFont);
        this->magicResistUpgradeCostText.setPosition(sf::Vector2f(0.9 * this->desktopSize.width, 0.8 * this->desktopSize.height));
        this->magicResistUpgradeCostText.setFillColor(sf::Color(254, 250, 224));
        if (this->allyVector->at(this->pickedCharacter).magicResist * pow(this->allyVector->at(this->pickedCharacter).magicResistLevel, 2) <= this->player->money)
        {
            this->possibleUpgrade[4] = true;
        }
        else
        {
            this->possibleUpgrade[4] = false;
        }
        if (this->allyVector->at(this->pickedCharacter).magicResistLevel != 10)
        {
            this->magicResistUpgradeText.setString("MAGIC  RESIST  LEVEL:  " + magicResistLevel + "\n" + "NEXT  LEVEL:  " + magicResistNextLevel);
        }
        else
        {
            this->magicResistUpgradeText.setString("MAGIC  RESIST  LEVEL:  MAX");
            this->possibleUpgrade[4] = false;
            this->magicResistUpgradeText.setPosition(sf::Vector2f(0.55 * this->desktopSize.width, 0.805 * this->desktopSize.height));
        }
        // SUPER POWER LEVEL
        std::string superPowerLevel = std::to_string(this->allyVector->at(this->pickedCharacter).superPowerLevel);
        this->superPowerUpgradeCostText.setString(std::to_string(int((this->allyVector->at(this->pickedCharacter).superPowerLevel) * 2000)));
        this->superPowerUpgradeCostText.setCharacterSize(25);
        this->superPowerUpgradeCostText.setFont(this->menuFont);
        this->superPowerUpgradeCostText.setPosition(sf::Vector2f(0.36 * this->desktopSize.width, 0.9 * this->desktopSize.height));
        this->superPowerUpgradeCostText.setFillColor(sf::Color(254, 250, 224));
        if (this->allyVector->at(this->pickedCharacter).superPowerLevel * 2000 <= this->player->money)
        {
            this->possibleUpgrade[2] = true;
        }
        else
        {
            this->possibleUpgrade[2] = false;
        }
        std::string superPowerNextLevel = "( + 0.5 )";
        if (this->allyVector->at(this->pickedCharacter).superPowerLevel != 10)
        {
            this->superPowerUpgradeText.setString("SUPER  POWER  LEVEL:  " + superPowerLevel + "\n" + "NEXT  LEVEL:  " + superPowerNextLevel);
        }
        else
        {
            this->superPowerUpgradeText.setString("SUPER  POWER  LEVEL:  MAX");
            this->possibleUpgrade[2] = false;
            this->superPowerUpgradeText.setPosition(sf::Vector2f(0.15 * this->desktopSize.width, 0.905 * this->desktopSize.height));
        }

    }
}

void Shop::blockCharacter()
{
    this->blockedSprites.clear();
    for (int i = 0; i < this->allyVector->size(); i++)
    {
        if (!(this->allyVector->at(i).isUnlocked))
        {
            sf::Sprite blockedItemSprite;
            blockedItemSprite.setTexture(this->blockedTexture);
            if (i % 3 == 0)
            {
                blockedItemSprite.setPosition(sf::Vector2f(0.15 * this->desktopSize.width, 0.3 * this->desktopSize.height));
            }
            else if (i % 3 == 1)
            {
                blockedItemSprite.setPosition(sf::Vector2f(0.45 * this->desktopSize.width, 0.3 * this->desktopSize.height));
            }
            else if (i % 3 == 2)
            {
                blockedItemSprite.setPosition(sf::Vector2f(0.75 * this->desktopSize.width, 0.3 * this->desktopSize.height));
            }

            this->blockedSprites.push_back(blockedItemSprite);
        }
    }
}

void Shop::unlockCharacter()
{
    if (this->buyButton.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y)))
    {
        if (this->pickedCharacter == 1)
        {
            this->player->money -= 10000;
        }
        if (this->pickedCharacter == 2)
        {
            this->player->money -= 25000;
        }
        this->allyVector->at(this->pickedCharacter).isUnlocked = true;
        std::string moneyString = std::to_string(this->player->money);
        this->moneyText.setString(moneyString);
        this->upgradeCharacterText();
    }
}

void Shop::upgradeCharacter()
{   
    if (this->pickedCharacter == 0)
    {
        // LIFE LEVEL
        if (this->upgradeButtonVector.at(0).getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y)) && this->possibleUpgrade[0] == true)
        {
            if (this->allyVector->at(this->pickedCharacter).lifeLevel == 1)
            {
                this->player->money -= this->allyVector->at(this->pickedCharacter).life;
                this->allyVector->at(this->pickedCharacter).lifeLevel += 1;
                this->allyVector->at(this->pickedCharacter).life += 150;
            }
            else if (this->allyVector->at(this->pickedCharacter).lifeLevel > 1 && this->allyVector->at(this->pickedCharacter).lifeLevel < 7)
            {
                this->player->money -= this->allyVector->at(this->pickedCharacter).life;
                this->allyVector->at(this->pickedCharacter).lifeLevel += 1;
                this->allyVector->at(this->pickedCharacter).life += 250;
            }
            else if (this->allyVector->at(this->pickedCharacter).lifeLevel == 7)
            {
                this->player->money -= this->allyVector->at(this->pickedCharacter).life;
                this->allyVector->at(this->pickedCharacter).lifeLevel += 1;
                this->allyVector->at(this->pickedCharacter).life += 1000;
            }
            else
            {
                this->player->money -= this->allyVector->at(this->pickedCharacter).life;
                this->allyVector->at(this->pickedCharacter).lifeLevel += 1;
                this->allyVector->at(this->pickedCharacter).life += 2500;
            }
            std::string moneyString = std::to_string(this->player->money);
            this->moneyText.setString(moneyString);
            std::string lifeLevel = std::to_string(this->allyVector->at(this->pickedCharacter).lifeLevel);
            std::string lifeNextLevel = "( + ";
            if (this->allyVector->at(this->pickedCharacter).lifeLevel == 1)
            {
                lifeNextLevel += "150 )";
                if (this->allyVector->at(this->pickedCharacter).life + 150 <= this->player->money)
                {
                    this->possibleUpgrade[0] = true;
                }
                else
                {
                    this->possibleUpgrade[0] = false;
                }
            }
            else if (this->allyVector->at(this->pickedCharacter).lifeLevel > 1 && this->allyVector->at(this->pickedCharacter).lifeLevel < 7)
            {
                lifeNextLevel += "250 )";
                if (this->allyVector->at(this->pickedCharacter).life + 250 <= this->player->money)
                {
                    this->possibleUpgrade[0] = true;
                }
                else
                {
                    this->possibleUpgrade[0] = false;
                }
            }
            else if (this->allyVector->at(this->pickedCharacter).lifeLevel == 7)
            {
                lifeNextLevel += "1000 )";
                if (this->allyVector->at(this->pickedCharacter).life + 1000 <= this->player->money)
                {
                    this->possibleUpgrade[0] = true;
                }
                else
                {
                    this->possibleUpgrade[0] = false;
                }
            }
            else
            {
                lifeNextLevel += "2500 )";
                if (this->allyVector->at(this->pickedCharacter).life + 2500 <= this->player->money)
                {
                    this->possibleUpgrade[0] = true;
                }
                else
                {
                    this->possibleUpgrade[0] = false;
                }
            }
            if (this->allyVector->at(this->pickedCharacter).lifeLevel != 10)
            {
                this->lifeUpgradeText.setString("LIFE  LEVEL:  " + lifeLevel + "\n" + "NEXT  LEVEL:  " + lifeNextLevel);
            }
            else
            {
                this->lifeUpgradeText.setString("LIFE  LEVEL:  MAX");
                this->lifeUpgradeText.setPosition(sf::Vector2f(0.15 * this->desktopSize.width, 0.705 * this->desktopSize.height));
            }
        }
        // POWER LEVEL
        if (this->upgradeButtonVector.at(3).getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y)) && this->possibleUpgrade[3] == true)
        {
            this->player->money -= pow(this->allyVector->at(this->pickedCharacter).powerLevel, 2) * this->allyVector->at(this->pickedCharacter).power;
            this->allyVector->at(this->pickedCharacter).powerLevel += 1;
            this->allyVector->at(this->pickedCharacter).power += 10;
            if (this->allyVector->at(this->pickedCharacter).power * pow(this->allyVector->at(this->pickedCharacter).powerLevel, 2) <= this->player->money)
            {
                this->possibleUpgrade[3] = true;
            }
            else
            {
                this->possibleUpgrade[3] = false;
            }
            std::string moneyString = std::to_string(this->player->money);
            this->moneyText.setString(moneyString);
            std::string powerLevel = std::to_string(this->allyVector->at(this->pickedCharacter).powerLevel);
            std::string powerNextLevel = "( + 10 )";
            if (this->allyVector->at(this->pickedCharacter).powerLevel != 10)
            {
                this->powerUpgradeText.setString("POWER  LEVEL:  " + powerLevel + "\n" + "NEXT  LEVEL:  " + powerNextLevel);
            }
            else
            {
                this->powerUpgradeText.setString("POWER  LEVEL:  MAX");
                this->possibleUpgrade[3] = false;
                this->powerUpgradeText.setPosition(sf::Vector2f(0.55 * this->desktopSize.width, 0.705 * this->desktopSize.height));
            }
        }
        // ARMOR LEVEL
        if (this->upgradeButtonVector.at(1).getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y)) && this->possibleUpgrade[1] == true)
        {
            if (this->allyVector->at(this->pickedCharacter).armorLevel < 8)
            {
                this->player->money -= pow(this->allyVector->at(this->pickedCharacter).armorLevel, 2) * this->allyVector->at(this->pickedCharacter).armor;
                this->allyVector->at(this->pickedCharacter).armorLevel += 1;
                this->allyVector->at(this->pickedCharacter).armor += 5;
            }
            else
            {
                this->player->money -= pow(this->allyVector->at(this->pickedCharacter).armorLevel, 2) * this->allyVector->at(this->pickedCharacter).armor;
                this->allyVector->at(this->pickedCharacter).armorLevel += 1;
                this->allyVector->at(this->pickedCharacter).armor += 25;
            }
            if (this->allyVector->at(this->pickedCharacter).armor * pow(this->allyVector->at(this->pickedCharacter).armorLevel, 2) <= this->player->money)
            {
                this->possibleUpgrade[1] = true;
            }
            else
            {
                this->possibleUpgrade[1] = false;
            }
            std::string moneyString = std::to_string(this->player->money);
            this->moneyText.setString(moneyString);
            std::string armorLevel = std::to_string(this->allyVector->at(this->pickedCharacter).armorLevel);
            std::string armorNextLevel = "( + ";
            if (this->allyVector->at(this->pickedCharacter).armorLevel < 8)
            {
                armorNextLevel += "5 )";
            }
            else
            {
                armorNextLevel += "25 )";
            }
            if (this->allyVector->at(this->pickedCharacter).armorLevel != 10)
            {
                this->armorUpgradeText.setString("ARMOR  LEVEL:  " + armorLevel + "\n" + "NEXT  LEVEL:  " + armorNextLevel);
            }
            else
            {
                this->armorUpgradeText.setString("ARMOR  LEVEL:  MAX");
                this->possibleUpgrade[1] = false;
                this->armorUpgradeText.setPosition(sf::Vector2f(0.15 * this->desktopSize.width, 0.805 * this->desktopSize.height));
            }
        }
        // MAGIC RESIST LEVEL
        if (this->upgradeButtonVector.at(4).getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y)) && this->possibleUpgrade[4] == true)
        {
            if (this->allyVector->at(this->pickedCharacter).magicResistLevel < 8)
            {
                this->player->money -= pow(this->allyVector->at(this->pickedCharacter).magicResistLevel, 2) * this->allyVector->at(this->pickedCharacter).magicResist;
                this->allyVector->at(this->pickedCharacter).magicResistLevel += 1;
                this->allyVector->at(this->pickedCharacter).magicResist += 5;
            }
            else
            {
                this->player->money -= pow(this->allyVector->at(this->pickedCharacter).magicResistLevel, 2) * this->allyVector->at(this->pickedCharacter).magicResist;
                this->allyVector->at(this->pickedCharacter).magicResistLevel += 1;
                this->allyVector->at(this->pickedCharacter).magicResist += 25;
            }
            if (this->allyVector->at(this->pickedCharacter).magicResist * pow(this->allyVector->at(this->pickedCharacter).magicResistLevel, 2) <= this->player->money)
            {
                this->possibleUpgrade[4] = true;
            }
            else
            {
                this->possibleUpgrade[4] = false;
            }
            std::string moneyString = std::to_string(this->player->money);
            this->moneyText.setString(moneyString);
            std::string magicResistLevel = std::to_string(this->allyVector->at(this->pickedCharacter).magicResistLevel);
            std::string magicResistNextLevel = "( + ";
            if (this->allyVector->at(this->pickedCharacter).magicResistLevel < 8)
            {
                magicResistNextLevel += "5 )";
            }
            else
            {
                magicResistNextLevel += "25 )";
            }
            if (this->allyVector->at(this->pickedCharacter).magicResistLevel != 10)
            {
                this->magicResistUpgradeText.setString("MAGIC  RESIST  LEVEL:  " + magicResistLevel + "\n" + "NEXT  LEVEL:  " + magicResistNextLevel);
            }
            else
            {
                this->magicResistUpgradeText.setString("MAGIC  RESIST  LEVEL:  MAX");
                this->possibleUpgrade[4] = false;
                this->magicResistUpgradeText.setPosition(sf::Vector2f(0.55 * this->desktopSize.width, 0.805 * this->desktopSize.height));
            }
        }
        // SUPER POWER LEVEL
        if (this->upgradeButtonVector.at(2).getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y)) && this->possibleUpgrade[2] == true)
        {
            this->player->money -= this->allyVector->at(this->pickedCharacter).superPowerLevel * 500;
            this->allyVector->at(this->pickedCharacter).superPowerLevel += 1;
            this->allyVector->at(this->pickedCharacter).superPower += 0.5;
            if ((this->allyVector->at(this->pickedCharacter).superPowerLevel) * 500 <= this->player->money)
            {
                this->possibleUpgrade[2] = true;
            }
            else
            {
                this->possibleUpgrade[2] = false;
            }
            std::string moneyString = std::to_string(this->player->money);
            this->moneyText.setString(moneyString);
            std::string superPowerLevel = std::to_string(this->allyVector->at(this->pickedCharacter).superPowerLevel);
            std::string superPowerNextLevel = "( + 0.5 )";
            if (this->allyVector->at(this->pickedCharacter).superPowerLevel != 10)
            {
                this->superPowerUpgradeText.setString("SUPER  POWER  LEVEL:  " + superPowerLevel + "\n" + "NEXT  LEVEL:  " + superPowerNextLevel);
            }
            else
            {
                this->superPowerUpgradeText.setString("SUPER  POWER  LEVEL:  MAX");
                this->possibleUpgrade[2] = false;
                this->superPowerUpgradeText.setPosition(sf::Vector2f(0.15 * this->desktopSize.width, 0.905 * this->desktopSize.height));
            }
        }
    }
    else if (this->pickedCharacter == 1)
    {
        // LIFE LEVEL
        if (this->upgradeButtonVector.at(0).getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y)) && this->possibleUpgrade[0] == true)
        {
            if (this->allyVector->at(this->pickedCharacter).lifeLevel == 1)
            {
                this->player->money -= this->allyVector->at(this->pickedCharacter).life;
                this->allyVector->at(this->pickedCharacter).lifeLevel += 1;
                this->allyVector->at(this->pickedCharacter).life += 1500;
            }
            else if (this->allyVector->at(this->pickedCharacter).lifeLevel > 1 && this->allyVector->at(this->pickedCharacter).lifeLevel < 5)
            {
                this->player->money -= this->allyVector->at(this->pickedCharacter).life;
                this->allyVector->at(this->pickedCharacter).lifeLevel += 1;
                this->allyVector->at(this->pickedCharacter).life += 2500;
            }
            else
            {
                this->player->money -= this->allyVector->at(this->pickedCharacter).life;
                this->allyVector->at(this->pickedCharacter).lifeLevel += 1;
                this->allyVector->at(this->pickedCharacter).life += 2000;
            }
            std::string moneyString = std::to_string(this->player->money);
            this->moneyText.setString(moneyString);
            std::string lifeLevel = std::to_string(this->allyVector->at(this->pickedCharacter).lifeLevel);
            std::string lifeNextLevel = "( + ";
            if (this->allyVector->at(this->pickedCharacter).lifeLevel == 1)
            {
                lifeNextLevel += "1500 )";
                if (this->allyVector->at(this->pickedCharacter).life + 1500 <= this->player->money)
                {
                    this->possibleUpgrade[0] = true;
                }
                else
                {
                    this->possibleUpgrade[0] = false;
                }
            }
            else if (this->allyVector->at(this->pickedCharacter).lifeLevel > 1 && this->allyVector->at(this->pickedCharacter).lifeLevel < 5)
            {
                lifeNextLevel += "2500 )";
                if (this->allyVector->at(this->pickedCharacter).life + 2500 <= this->player->money)
                {
                    this->possibleUpgrade[0] = true;
                }
                else
                {
                    this->possibleUpgrade[0] = false;
                }
            }
            else
            {
                lifeNextLevel += "2000 )";
                if (this->allyVector->at(this->pickedCharacter).life + 2000 <= this->player->money)
                {
                    this->possibleUpgrade[0] = true;
                }
                else
                {
                    this->possibleUpgrade[0] = false;
                }
            }
            if (this->allyVector->at(this->pickedCharacter).lifeLevel != 10)
            {
                this->lifeUpgradeText.setString("LIFE  LEVEL:  " + lifeLevel + "\n" + "NEXT  LEVEL:  " + lifeNextLevel);
            }
            else
            {
                this->lifeUpgradeText.setString("LIFE  LEVEL:  MAX");
                this->possibleUpgrade[0] = false;
                this->lifeUpgradeText.setPosition(sf::Vector2f(0.15 * this->desktopSize.width, 0.705 * this->desktopSize.height));
            }
        }
        // POWER LEVEL
        if (this->upgradeButtonVector.at(3).getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y)) && this->possibleUpgrade[3] == true)
        {
            if (this->allyVector->at(this->pickedCharacter).powerLevel < 7)
            {
                this->player->money -= pow(this->allyVector->at(this->pickedCharacter).powerLevel, 2) * this->allyVector->at(this->pickedCharacter).power;
                this->allyVector->at(this->pickedCharacter).powerLevel += 1;
                this->allyVector->at(this->pickedCharacter).power += 25;
            }
            else
            {
                this->player->money -= pow(this->allyVector->at(this->pickedCharacter).powerLevel, 2) * this->allyVector->at(this->pickedCharacter).power;
                this->allyVector->at(this->pickedCharacter).powerLevel += 1;
                this->allyVector->at(this->pickedCharacter).power += 50;
            }
            if (this->allyVector->at(this->pickedCharacter).power * pow(this->allyVector->at(this->pickedCharacter).powerLevel, 2) <= this->player->money)
            {
                this->possibleUpgrade[3] = true;
            }
            else
            {
                this->possibleUpgrade[3] = false;
            }
            std::string moneyString = std::to_string(this->player->money);
            this->moneyText.setString(moneyString);
            std::string powerLevel = std::to_string(this->allyVector->at(this->pickedCharacter).powerLevel);
            std::string powerNextLevel = "( + ";
            if (this->allyVector->at(this->pickedCharacter).powerLevel < 7)
            {
                powerNextLevel += "25 )";
            }
            else
            {
                powerNextLevel += "50 )";
            }
            if (this->allyVector->at(this->pickedCharacter).powerLevel != 10)
            {
                this->powerUpgradeText.setString("POWER  LEVEL:  " + powerLevel + "\n" + "NEXT  LEVEL:  " + powerNextLevel);
            }
            else
            {
                this->powerUpgradeText.setString("POWER  LEVEL:  MAX");
                this->possibleUpgrade[3] = false;
                this->powerUpgradeText.setPosition(sf::Vector2f(0.55 * this->desktopSize.width, 0.705 * this->desktopSize.height));
            }
        }
        // ARMOR LEVEL
        if (this->upgradeButtonVector.at(1).getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y)) && this->possibleUpgrade[1] == true)
        {
            if (this->allyVector->at(this->pickedCharacter).armorLevel < 6)
            {
                this->player->money -= pow(this->allyVector->at(this->pickedCharacter).armorLevel, 2) * this->allyVector->at(this->pickedCharacter).armor;
                this->allyVector->at(this->pickedCharacter).armorLevel += 1;
                this->allyVector->at(this->pickedCharacter).armor += 10;
            }
            else if (this->allyVector->at(this->pickedCharacter).armorLevel > 5 && this->allyVector->at(this->pickedCharacter).armorLevel < 9)
            {
                this->player->money -= pow(this->allyVector->at(this->pickedCharacter).armorLevel, 2) * this->allyVector->at(this->pickedCharacter).armor;
                this->allyVector->at(this->pickedCharacter).armorLevel += 1;
                this->allyVector->at(this->pickedCharacter).armor += 25;
            }
            else
            {
                this->player->money -= pow(this->allyVector->at(this->pickedCharacter).armorLevel, 2) * this->allyVector->at(this->pickedCharacter).armor;
                this->allyVector->at(this->pickedCharacter).armorLevel += 1;
                this->allyVector->at(this->pickedCharacter).armor += 50;
            }
            if (this->allyVector->at(this->pickedCharacter).armor * pow(this->allyVector->at(this->pickedCharacter).armorLevel, 2) <= this->player->money)
            {
                this->possibleUpgrade[1] = true;
            }
            else
            {
                this->possibleUpgrade[1] = false;
            }
            std::string moneyString = std::to_string(this->player->money);
            this->moneyText.setString(moneyString);
            std::string armorLevel = std::to_string(this->allyVector->at(this->pickedCharacter).armorLevel);
            std::string armorNextLevel = "( + ";
            if (this->allyVector->at(this->pickedCharacter).armorLevel < 6)
            {
                armorNextLevel += "10 )";
            }
            else if (this->allyVector->at(this->pickedCharacter).armorLevel > 5 && this->allyVector->at(this->pickedCharacter).armorLevel < 9)
            {
                armorNextLevel += "25 )";
            }
            else
            {
                armorNextLevel += "50 )";
            }
            if (this->allyVector->at(this->pickedCharacter).armorLevel != 10)
            {
                this->armorUpgradeText.setString("ARMOR  LEVEL:  " + armorLevel + "\n" + "NEXT  LEVEL:  " + armorNextLevel);
            }
            else
            {
                this->armorUpgradeText.setString("ARMOR  LEVEL:  MAX");
                this->possibleUpgrade[1] = false;
                this->armorUpgradeText.setPosition(sf::Vector2f(0.15 * this->desktopSize.width, 0.805 * this->desktopSize.height));
            }
        }
        // MAGIC RESIST LEVEL
        if (this->upgradeButtonVector.at(4).getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y)) && this->possibleUpgrade[4] == true)
        {
            if (this->allyVector->at(this->pickedCharacter).magicResistLevel < 6)
            {
                this->player->money -= pow(this->allyVector->at(this->pickedCharacter).magicResistLevel, 2) * this->allyVector->at(this->pickedCharacter).magicResist;
                this->allyVector->at(this->pickedCharacter).magicResistLevel += 1;
                this->allyVector->at(this->pickedCharacter).magicResist += 10;
            }
            else if (this->allyVector->at(this->pickedCharacter).magicResistLevel > 5 && this->allyVector->at(this->pickedCharacter).magicResistLevel < 9)
            {
                this->player->money -= pow(this->allyVector->at(this->pickedCharacter).magicResistLevel, 2) * this->allyVector->at(this->pickedCharacter).magicResist;
                this->allyVector->at(this->pickedCharacter).magicResistLevel += 1;
                this->allyVector->at(this->pickedCharacter).magicResist += 25;
            }
            else
            {
                this->player->money -= pow(this->allyVector->at(this->pickedCharacter).magicResistLevel, 2) * this->allyVector->at(this->pickedCharacter).magicResist;
                this->allyVector->at(this->pickedCharacter).magicResistLevel += 1;
                this->allyVector->at(this->pickedCharacter).magicResist += 50;
            }
            if (this->allyVector->at(this->pickedCharacter).magicResist * pow(this->allyVector->at(this->pickedCharacter).magicResistLevel, 2) <= this->player->money)
            {
                this->possibleUpgrade[4] = true;
            }
            else
            {
                this->possibleUpgrade[4] = false;
            }
            std::string moneyString = std::to_string(this->player->money);
            this->moneyText.setString(moneyString);
            std::string magicResistLevel = std::to_string(this->allyVector->at(this->pickedCharacter).magicResistLevel);
            std::string magicResistNextLevel = "( + ";
            if (this->allyVector->at(this->pickedCharacter).magicResistLevel < 6)
            {
                magicResistNextLevel += "10 )";
            }
            else if (this->allyVector->at(this->pickedCharacter).magicResistLevel > 5 && this->allyVector->at(this->pickedCharacter).magicResistLevel < 9)
            {
                magicResistNextLevel += "25 )";
            }
            else
            {
                magicResistNextLevel += "50 )";
            }
            if (this->allyVector->at(this->pickedCharacter).magicResistLevel != 10)
            {
                this->magicResistUpgradeText.setString("MAGIC  RESIST  LEVEL:  " + magicResistLevel + "\n" + "NEXT  LEVEL:  " + magicResistNextLevel);
            }
            else
            {
                this->magicResistUpgradeText.setString("MAGIC  RESIST  LEVEL:  MAX");
                this->possibleUpgrade[4] = false;
                this->magicResistUpgradeText.setPosition(sf::Vector2f(0.55 * this->desktopSize.width, 0.805 * this->desktopSize.height));
            }
        }
        // SUPER POWER LEVEL
        if (this->upgradeButtonVector.at(2).getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y)) && this->possibleUpgrade[2] == true)
        {
            this->player->money -= pow(this->allyVector->at(this->pickedCharacter).superPowerLevel, 2) * 1000;
            this->allyVector->at(this->pickedCharacter).superPowerLevel += 1;
            this->allyVector->at(this->pickedCharacter).superPower += 0.5;
            if ((this->allyVector->at(this->pickedCharacter).superPowerLevel) * 1000 <= this->player->money)
            {
                this->possibleUpgrade[2] = true;
            }
            else
            {
                this->possibleUpgrade[2] = false;
            }
            std::string moneyString = std::to_string(this->player->money);
            this->moneyText.setString(moneyString);
            std::string superPowerLevel = std::to_string(this->allyVector->at(this->pickedCharacter).superPowerLevel);
            std::string superPowerNextLevel = "( + 0.5 )";
            if (this->allyVector->at(this->pickedCharacter).superPowerLevel != 10)
            {
                this->superPowerUpgradeText.setString("SUPER  POWER  LEVEL:  " + superPowerLevel + "\n" + "NEXT  LEVEL:  " + superPowerNextLevel);
            }
            else
            {
                this->superPowerUpgradeText.setString("SUPER  POWER  LEVEL:  MAX");
                this->possibleUpgrade[2] = false;
                this->superPowerUpgradeText.setPosition(sf::Vector2f(0.15 * this->desktopSize.width, 0.905 * this->desktopSize.height));
            }
        }
    }
    else if (this->pickedCharacter == 2)
    {
        // LIFE LEVEL
        if (this->upgradeButtonVector.at(0).getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y)) && this->possibleUpgrade[0] == true)
        {
            if (this->allyVector->at(this->pickedCharacter).lifeLevel < 5)
            {
                this->player->money -= this->allyVector->at(this->pickedCharacter).life;
                this->allyVector->at(this->pickedCharacter).lifeLevel += 1;
                this->allyVector->at(this->pickedCharacter).life += 5000;
            }
            else
            {
                this->player->money -= this->allyVector->at(this->pickedCharacter).life;
                this->allyVector->at(this->pickedCharacter).lifeLevel += 1;
                this->allyVector->at(this->pickedCharacter).life += 2500;
            }
            std::string moneyString = std::to_string(this->player->money);
            this->moneyText.setString(moneyString);
            std::string lifeLevel = std::to_string(this->allyVector->at(this->pickedCharacter).lifeLevel);
            std::string lifeNextLevel = "( + ";
            if (this->allyVector->at(this->pickedCharacter).lifeLevel < 5)
            {
                lifeNextLevel += "5000 )";
                if (this->allyVector->at(this->pickedCharacter).life + 5000 <= this->player->money)
                {
                    this->possibleUpgrade[0] = true;
                }
                else
                {
                    this->possibleUpgrade[0] = false;
                }
            }
            else
            {
                lifeNextLevel += "2500 )";
                if (this->allyVector->at(this->pickedCharacter).life + 2500 <= this->player->money)
                {
                    this->possibleUpgrade[0] = true;
                }
                else
                {
                    this->possibleUpgrade[0] = false;
                }
            }
            if (this->allyVector->at(this->pickedCharacter).lifeLevel != 10)
            {
                this->lifeUpgradeText.setString("LIFE  LEVEL:  " + lifeLevel + "\n" + "NEXT  LEVEL:  " + lifeNextLevel);
            }
            else
            {
                this->lifeUpgradeText.setString("LIFE  LEVEL:  MAX");
                this->possibleUpgrade[0] = false;
                this->lifeUpgradeText.setPosition(sf::Vector2f(0.15 * this->desktopSize.width, 0.705 * this->desktopSize.height));
            }
        }
        // POWER LEVEL
        if (this->upgradeButtonVector.at(3).getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y)) && this->possibleUpgrade[3] == true)
        {
            this->player->money -= pow(this->allyVector->at(this->pickedCharacter).powerLevel, 2) * this->allyVector->at(this->pickedCharacter).power;
            this->allyVector->at(this->pickedCharacter).powerLevel += 1;
            this->allyVector->at(this->pickedCharacter).power += 100;
            if (this->allyVector->at(this->pickedCharacter).power * pow(this->allyVector->at(this->pickedCharacter).powerLevel, 2) <= this->player->money)
            {
                this->possibleUpgrade[3] = true;
            }
            else
            {
                this->possibleUpgrade[3] = false;
            }
            std::string moneyString = std::to_string(this->player->money);
            this->moneyText.setString(moneyString);
            std::string powerLevel = std::to_string(this->allyVector->at(this->pickedCharacter).powerLevel);
            std::string powerNextLevel = "( + 100 )";
            if (this->allyVector->at(this->pickedCharacter).powerLevel != 10)
            {
                this->powerUpgradeText.setString("POWER  LEVEL:  " + powerLevel + "\n" + "NEXT  LEVEL:  " + powerNextLevel);
            }
            else
            {
                this->powerUpgradeText.setString("POWER  LEVEL:  MAX");
                this->possibleUpgrade[3] = false;
                this->powerUpgradeText.setPosition(sf::Vector2f(0.55 * this->desktopSize.width, 0.705 * this->desktopSize.height));
            }
        }
        // ARMOR LEVEL
        if (this->upgradeButtonVector.at(1).getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y)) && this->possibleUpgrade[1] == true)
        {
            this->player->money -= pow(this->allyVector->at(this->pickedCharacter).armorLevel, 2) * this->allyVector->at(this->pickedCharacter).armor;
            this->allyVector->at(this->pickedCharacter).armorLevel += 1;
            this->allyVector->at(this->pickedCharacter).armor += 50;
            if (this->allyVector->at(this->pickedCharacter).armor * pow(this->allyVector->at(this->pickedCharacter).armorLevel, 2) <= this->player->money)
            {
                this->possibleUpgrade[1] = true;
            }
            else
            {
                this->possibleUpgrade[1] = false;
            }
            std::string moneyString = std::to_string(this->player->money);
            this->moneyText.setString(moneyString);
            std::string armorLevel = std::to_string(this->allyVector->at(this->pickedCharacter).armorLevel);
            std::string armorNextLevel = "( + 50 )";
            if (this->allyVector->at(this->pickedCharacter).armorLevel != 10)
            {
                this->armorUpgradeText.setString("ARMOR  LEVEL:  " + armorLevel + "\n" + "NEXT  LEVEL:  " + armorNextLevel);
            }
            else
            {
                this->armorUpgradeText.setString("ARMOR  LEVEL:  MAX");
                this->possibleUpgrade[1] = false;
                this->armorUpgradeText.setPosition(sf::Vector2f(0.15 * this->desktopSize.width, 0.805 * this->desktopSize.height));
            }
        }
        // MAGIC RESIST LEVEL
        if (this->upgradeButtonVector.at(4).getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y)) && this->possibleUpgrade[4] == true)
        {
            this->player->money -= pow(this->allyVector->at(this->pickedCharacter).magicResistLevel, 2) * this->allyVector->at(this->pickedCharacter).magicResist;
            this->allyVector->at(this->pickedCharacter).magicResistLevel += 1;
            this->allyVector->at(this->pickedCharacter).magicResist += 50;
            if (this->allyVector->at(this->pickedCharacter).magicResist * pow(this->allyVector->at(this->pickedCharacter).magicResistLevel, 2) <= this->player->money)
            {
                this->possibleUpgrade[4] = true;
            }
            else
            {
                this->possibleUpgrade[4] = false;
            }
            std::string moneyString = std::to_string(this->player->money);
            this->moneyText.setString(moneyString);
            std::string magicResistLevel = std::to_string(this->allyVector->at(this->pickedCharacter).magicResistLevel);
            std::string magicResistNextLevel = "( + 50 )";
            if (this->allyVector->at(this->pickedCharacter).magicResistLevel != 10)
            {
                this->magicResistUpgradeText.setString("MAGIC  RESIST  LEVEL:  " + magicResistLevel + "\n" + "NEXT  LEVEL:  " + magicResistNextLevel);
            }
            else
            {
                this->magicResistUpgradeText.setString("MAGIC  RESIST  LEVEL:  MAX");
                this->possibleUpgrade[4] = false;
                this->magicResistUpgradeText.setPosition(sf::Vector2f(0.55 * this->desktopSize.width, 0.805 * this->desktopSize.height));
            }
        }
        // SUPER POWER LEVEL
        if (this->upgradeButtonVector.at(2).getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y)) && this->possibleUpgrade[2] == true)
        {
            this->player->money -= pow(this->allyVector->at(this->pickedCharacter).superPowerLevel, 2) * 2000;
            this->allyVector->at(this->pickedCharacter).superPowerLevel += 1;
            this->allyVector->at(this->pickedCharacter).superPower += 0.5;
            if ((this->allyVector->at(this->pickedCharacter).superPowerLevel) * 2000 <= this->player->money)
            {
                this->possibleUpgrade[2] = true;
            }
            else
            {
                this->possibleUpgrade[2] = false;
            }
            std::string moneyString = std::to_string(this->player->money);
            this->moneyText.setString(moneyString);
            std::string superPowerLevel = std::to_string(this->allyVector->at(this->pickedCharacter).superPowerLevel);
            std::string superPowerNextLevel = "( + 0.5 )";
            if (this->allyVector->at(this->pickedCharacter).superPowerLevel != 10)
            {
                this->superPowerUpgradeText.setString("SUPER  POWER  LEVEL:  " + superPowerLevel + "\n" + "NEXT  LEVEL:  " + superPowerNextLevel);
            }
            else
            {
                this->superPowerUpgradeText.setString("SUPER  POWER  LEVEL:  MAX");
                this->possibleUpgrade[2] = false;
                this->superPowerUpgradeText.setPosition(sf::Vector2f(0.15 * this->desktopSize.width, 0.905 * this->desktopSize.height));
            }
        }
    }
    this->lifeText.setString(std::to_string(int(this->allyVector->at(this->pickedCharacter).life)));
    this->powerText.setString(std::to_string(int(this->allyVector->at(this->pickedCharacter).power)));
    this->armorText.setString(std::to_string(int(this->allyVector->at(this->pickedCharacter).armor)));
    this->magicResistText.setString(std::to_string(int(this->allyVector->at(this->pickedCharacter).magicResist)));
    this->superPowerText.setString(std::to_string(this->allyVector->at(this->pickedCharacter).superPower).substr(0, 3));
    this->upgradeCharacterText();
}

void Shop::upgradeCharacterText()
{
    if (this->pickedCharacter == 0)
    {
        std::string moneyString = std::to_string(this->player->money);
        this->moneyText.setString(moneyString);
        // LIFE LEVEL
        std::string lifeLevel = std::to_string(this->allyVector->at(this->pickedCharacter).lifeLevel);
        std::string lifeNextLevel = "( + ";
        if (this->allyVector->at(this->pickedCharacter).lifeLevel == 1)
        {
            lifeNextLevel += "150 )";
            this->lifeUpgradeCostText.setString(std::to_string(int(this->allyVector->at(this->pickedCharacter).life) + 150));
            this->lifeUpgradeCostText.setCharacterSize(25);
            this->lifeUpgradeCostText.setFont(this->menuFont);
            this->lifeUpgradeCostText.setPosition(sf::Vector2f(0.36 * this->desktopSize.width, 0.7 * this->desktopSize.height));
            this->lifeUpgradeCostText.setFillColor(sf::Color(254, 250, 224));
            if (this->allyVector->at(this->pickedCharacter).life + 150 <= this->player->money)
            {
                this->possibleUpgrade[0] = true;
            }
            else
            {
                this->possibleUpgrade[0] = false;
            }
        }
        else if (this->allyVector->at(this->pickedCharacter).lifeLevel > 1 && this->allyVector->at(this->pickedCharacter).lifeLevel < 7)
        {
            lifeNextLevel += "250 )";
            this->lifeUpgradeCostText.setString(std::to_string(int(this->allyVector->at(this->pickedCharacter).life) + 250));
            this->lifeUpgradeCostText.setCharacterSize(25);
            this->lifeUpgradeCostText.setFont(this->menuFont);
            this->lifeUpgradeCostText.setPosition(sf::Vector2f(0.36 * this->desktopSize.width, 0.7 * this->desktopSize.height));
            this->lifeUpgradeCostText.setFillColor(sf::Color(254, 250, 224));
            if (this->allyVector->at(this->pickedCharacter).life + 250 <= this->player->money)
            {
                this->possibleUpgrade[0] = true;
            }
            else
            {
                this->possibleUpgrade[0] = false;
            }
        }
        else if (this->allyVector->at(this->pickedCharacter).lifeLevel == 7)
        {
            lifeNextLevel += "1000 )";
            this->lifeUpgradeCostText.setString(std::to_string(int(this->allyVector->at(this->pickedCharacter).life) + 1000));
            this->lifeUpgradeCostText.setCharacterSize(25);
            this->lifeUpgradeCostText.setFont(this->menuFont);
            this->lifeUpgradeCostText.setPosition(sf::Vector2f(0.36 * this->desktopSize.width, 0.7 * this->desktopSize.height));
            this->lifeUpgradeCostText.setFillColor(sf::Color(254, 250, 224));
            if (this->allyVector->at(this->pickedCharacter).life + 1000 <= this->player->money)
            {
                this->possibleUpgrade[0] = true;
            }
            else
            {
                this->possibleUpgrade[0] = false;
            }
        }
        else
        {
            lifeNextLevel += "2500 )";
            this->lifeUpgradeCostText.setString(std::to_string(int(this->allyVector->at(this->pickedCharacter).life) + 2500));
            this->lifeUpgradeCostText.setCharacterSize(25);
            this->lifeUpgradeCostText.setFont(this->menuFont);
            this->lifeUpgradeCostText.setPosition(sf::Vector2f(0.36 * this->desktopSize.width, 0.7 * this->desktopSize.height));
            this->lifeUpgradeCostText.setFillColor(sf::Color(254, 250, 224));
            if (this->allyVector->at(this->pickedCharacter).life + 2500 <= this->player->money)
            {
                this->possibleUpgrade[0] = true;
            }
            else
            {
                this->possibleUpgrade[0] = false;
            }
        }
        if (this->allyVector->at(this->pickedCharacter).lifeLevel != 10)
        {
            this->lifeUpgradeText.setString("LIFE  LEVEL:  " + lifeLevel + "\n" + "NEXT  LEVEL:  " + lifeNextLevel);
        }
        else
        {
            this->lifeUpgradeText.setString("LIFE  LEVEL:  MAX");
            this->lifeUpgradeText.setPosition(sf::Vector2f(0.15 * this->desktopSize.width, 0.705 * this->desktopSize.height));
        }
        // POWER LEVEL
        if (this->allyVector->at(this->pickedCharacter).power * pow(this->allyVector->at(this->pickedCharacter).powerLevel, 2) <= this->player->money)
        {
            this->possibleUpgrade[3] = true;
        }
        else
        {
            this->possibleUpgrade[3] = false;
        }
        std::string powerLevel = std::to_string(this->allyVector->at(this->pickedCharacter).powerLevel);
        std::string powerNextLevel = "( + 10 )";
        this->powerUpgradeCostText.setString(std::to_string(int(this->allyVector->at(this->pickedCharacter).power * pow(this->allyVector->at(this->pickedCharacter).powerLevel, 2))));
        this->powerUpgradeCostText.setCharacterSize(25);
        this->powerUpgradeCostText.setFont(this->menuFont);
        this->powerUpgradeCostText.setPosition(sf::Vector2f(0.9 * this->desktopSize.width, 0.7 * this->desktopSize.height));
        this->powerUpgradeCostText.setFillColor(sf::Color(254, 250, 224));
        if (this->allyVector->at(this->pickedCharacter).powerLevel != 10)
        {
            this->powerUpgradeText.setString("POWER  LEVEL:  " + powerLevel + "\n" + "NEXT  LEVEL:  " + powerNextLevel);
        }
        else
        {
            this->powerUpgradeText.setString("POWER  LEVEL:  MAX");
            this->possibleUpgrade[3] = false;
            this->powerUpgradeText.setPosition(sf::Vector2f(0.55 * this->desktopSize.width, 0.705 * this->desktopSize.height));
        }
        // ARMOR LEVEL
        if (this->allyVector->at(this->pickedCharacter).armor * pow(this->allyVector->at(this->pickedCharacter).armorLevel, 2) <= this->player->money)
        {
            this->possibleUpgrade[1] = true;
        }
        else
        {
            this->possibleUpgrade[1] = false;
        }
        std::string armorLevel = std::to_string(this->allyVector->at(this->pickedCharacter).armorLevel);
        std::string armorNextLevel = "( + ";
        this->armorUpgradeCostText.setString(std::to_string(int(this->allyVector->at(this->pickedCharacter).armor* pow(this->allyVector->at(this->pickedCharacter).armorLevel, 2))));
        this->armorUpgradeCostText.setCharacterSize(25);
        this->armorUpgradeCostText.setFont(this->menuFont);
        this->armorUpgradeCostText.setPosition(sf::Vector2f(0.36 * this->desktopSize.width, 0.8 * this->desktopSize.height));
        this->armorUpgradeCostText.setFillColor(sf::Color(254, 250, 224));
        if (this->allyVector->at(this->pickedCharacter).armorLevel < 8)
        {
            armorNextLevel += "5 )";
        }
        else
        {
            armorNextLevel += "25 )";
        }
        if (this->allyVector->at(this->pickedCharacter).armorLevel != 10)
        {
            this->armorUpgradeText.setString("ARMOR  LEVEL:  " + armorLevel + "\n" + "NEXT  LEVEL:  " + armorNextLevel);
        }
        else
        {
            this->armorUpgradeText.setString("ARMOR  LEVEL:  MAX");
            this->possibleUpgrade[1] = false;
            this->armorUpgradeText.setPosition(sf::Vector2f(0.15 * this->desktopSize.width, 0.805 * this->desktopSize.height));
        }
        // MAGIC RESIST LEVEL
        if (this->allyVector->at(this->pickedCharacter).magicResist * pow(this->allyVector->at(this->pickedCharacter).magicResistLevel, 2) <= this->player->money)
        {
            this->possibleUpgrade[4] = true;
        }
        else
        {
            this->possibleUpgrade[4] = false;
        }
        std::string magicResistLevel = std::to_string(this->allyVector->at(this->pickedCharacter).magicResistLevel);
        std::string magicResistNextLevel = "( + ";
        this->magicResistUpgradeCostText.setString(std::to_string(int(this->allyVector->at(this->pickedCharacter).magicResist* pow(this->allyVector->at(this->pickedCharacter).magicResistLevel, 2))));
        this->magicResistUpgradeCostText.setCharacterSize(25);
        this->magicResistUpgradeCostText.setFont(this->menuFont);
        this->magicResistUpgradeCostText.setPosition(sf::Vector2f(0.9 * this->desktopSize.width, 0.8 * this->desktopSize.height));
        this->magicResistUpgradeCostText.setFillColor(sf::Color(254, 250, 224));
        if (this->allyVector->at(this->pickedCharacter).magicResistLevel < 8)
        {
            magicResistNextLevel += "5 )";
        }
        else
        {
            magicResistNextLevel += "25 )";
        }
        if (this->allyVector->at(this->pickedCharacter).magicResistLevel != 10)
        {
            this->magicResistUpgradeText.setString("MAGIC  RESIST  LEVEL:  " + magicResistLevel + "\n" + "NEXT  LEVEL:  " + magicResistNextLevel);
        }
        else
        {
            this->magicResistUpgradeText.setString("MAGIC  RESIST  LEVEL:  MAX");
            this->possibleUpgrade[4] = false;
            this->magicResistUpgradeText.setPosition(sf::Vector2f(0.55 * this->desktopSize.width, 0.805 * this->desktopSize.height));
        }
        // SUPER POWER LEVEL
        if ((this->allyVector->at(this->pickedCharacter).superPowerLevel) * 500 <= this->player->money)
        {
            this->possibleUpgrade[2] = true;
        }
        else
        {
            this->possibleUpgrade[2] = false;
        }
        std::string superPowerLevel = std::to_string(this->allyVector->at(this->pickedCharacter).superPowerLevel);
        std::string superPowerNextLevel = "( + 0.5 )";
        this->superPowerUpgradeCostText.setString(std::to_string(int((this->allyVector->at(this->pickedCharacter).superPowerLevel) * 500)));
        this->superPowerUpgradeCostText.setCharacterSize(25);
        this->superPowerUpgradeCostText.setFont(this->menuFont);
        this->superPowerUpgradeCostText.setPosition(sf::Vector2f(0.36 * this->desktopSize.width, 0.9 * this->desktopSize.height));
        this->superPowerUpgradeCostText.setFillColor(sf::Color(254, 250, 224));
        if (this->allyVector->at(this->pickedCharacter).superPowerLevel != 10)
        {
            this->superPowerUpgradeText.setString("SUPER  POWER  LEVEL:  " + superPowerLevel + "\n" + "NEXT  LEVEL:  " + superPowerNextLevel);
        }
        else
        {
            this->superPowerUpgradeText.setString("SUPER  POWER  LEVEL:  MAX");
            this->possibleUpgrade[2] = false;
            this->superPowerUpgradeText.setPosition(sf::Vector2f(0.15 * this->desktopSize.width, 0.905 * this->desktopSize.height));
        }
    }
    else if (this->pickedCharacter == 1)
    {
        std::string moneyString = std::to_string(this->player->money);
        this->moneyText.setString(moneyString);
        // LIFE LEVEL
        std::string lifeLevel = std::to_string(this->allyVector->at(this->pickedCharacter).lifeLevel);
        std::string lifeNextLevel = "( + ";
        if (this->allyVector->at(this->pickedCharacter).lifeLevel == 1)
        {
            lifeNextLevel += "1500 )";
            this->lifeUpgradeCostText.setString(std::to_string(int(this->allyVector->at(this->pickedCharacter).life) + 1500));
            this->lifeUpgradeCostText.setCharacterSize(25);
            this->lifeUpgradeCostText.setFont(this->menuFont);
            this->lifeUpgradeCostText.setPosition(sf::Vector2f(0.36 * this->desktopSize.width, 0.7 * this->desktopSize.height));
            this->lifeUpgradeCostText.setFillColor(sf::Color(254, 250, 224));
            if (this->allyVector->at(this->pickedCharacter).life + 1500 <= this->player->money)
            {
                this->possibleUpgrade[0] = true;
            }
            else
            {
                this->possibleUpgrade[0] = false;
            }
        }
        else if (this->allyVector->at(this->pickedCharacter).lifeLevel > 1 && this->allyVector->at(this->pickedCharacter).lifeLevel < 5)
        {
            lifeNextLevel += "2500 )";
            this->lifeUpgradeCostText.setString(std::to_string(int(this->allyVector->at(this->pickedCharacter).life) + 2500));
            this->lifeUpgradeCostText.setCharacterSize(25);
            this->lifeUpgradeCostText.setFont(this->menuFont);
            this->lifeUpgradeCostText.setPosition(sf::Vector2f(0.36 * this->desktopSize.width, 0.7 * this->desktopSize.height));
            this->lifeUpgradeCostText.setFillColor(sf::Color(254, 250, 224));
            if (this->allyVector->at(this->pickedCharacter).life + 2500 <= this->player->money)
            {
                this->possibleUpgrade[0] = true;
            }
            else
            {
                this->possibleUpgrade[0] = false;
            }
        }
        else
        {
            lifeNextLevel += "2000 )";
            this->lifeUpgradeCostText.setString(std::to_string(int(this->allyVector->at(this->pickedCharacter).life) + 2000));
            this->lifeUpgradeCostText.setCharacterSize(25);
            this->lifeUpgradeCostText.setFont(this->menuFont);
            this->lifeUpgradeCostText.setPosition(sf::Vector2f(0.36 * this->desktopSize.width, 0.7 * this->desktopSize.height));
            this->lifeUpgradeCostText.setFillColor(sf::Color(254, 250, 224));
            if (this->allyVector->at(this->pickedCharacter).life + 2000 <= this->player->money)
            {
                this->possibleUpgrade[0] = true;
            }
            else
            {
                this->possibleUpgrade[0] = false;
            }
        }
        if (this->allyVector->at(this->pickedCharacter).lifeLevel != 10)
        {
            this->lifeUpgradeText.setString("LIFE  LEVEL:  " + lifeLevel + "\n" + "NEXT  LEVEL:  " + lifeNextLevel);
        }
        else
        {
            this->lifeUpgradeText.setString("LIFE  LEVEL:  MAX");
            this->possibleUpgrade[0] = false;
            this->lifeUpgradeText.setPosition(sf::Vector2f(0.15 * this->desktopSize.width, 0.705 * this->desktopSize.height));
        }
        // POWER LEVEL
        if (this->allyVector->at(this->pickedCharacter).power * pow(this->allyVector->at(this->pickedCharacter).powerLevel, 2) <= this->player->money)
        {
            this->possibleUpgrade[3] = true;
        }
        else
        {
            this->possibleUpgrade[3] = false;
        }
        std::string powerLevel = std::to_string(this->allyVector->at(this->pickedCharacter).powerLevel);
        std::string powerNextLevel = "( + ";
        this->powerUpgradeCostText.setString(std::to_string(int(this->allyVector->at(this->pickedCharacter).power* pow(this->allyVector->at(this->pickedCharacter).powerLevel, 2))));
        this->powerUpgradeCostText.setCharacterSize(25);
        this->powerUpgradeCostText.setFont(this->menuFont);
        this->powerUpgradeCostText.setPosition(sf::Vector2f(0.9 * this->desktopSize.width, 0.7 * this->desktopSize.height));
        this->powerUpgradeCostText.setFillColor(sf::Color(254, 250, 224));
        if (this->allyVector->at(this->pickedCharacter).powerLevel < 7)
        {
            powerNextLevel += "25 )";
        }
        else
        {
            powerNextLevel += "50 )";
        }
        if (this->allyVector->at(this->pickedCharacter).powerLevel != 10)
        {
            this->powerUpgradeText.setString("POWER  LEVEL:  " + powerLevel + "\n" + "NEXT  LEVEL:  " + powerNextLevel);
        }
        else
        {
            this->powerUpgradeText.setString("POWER  LEVEL:  MAX");
            this->possibleUpgrade[3] = false;
            this->powerUpgradeText.setPosition(sf::Vector2f(0.55 * this->desktopSize.width, 0.705 * this->desktopSize.height));
        }
        // ARMOR LEVEL
        if (this->allyVector->at(this->pickedCharacter).armor * pow(this->allyVector->at(this->pickedCharacter).armorLevel, 2) <= this->player->money)
        {
            this->possibleUpgrade[1] = true;
        }
        else
        {
            this->possibleUpgrade[1] = false;
        }
        std::string armorLevel = std::to_string(this->allyVector->at(this->pickedCharacter).armorLevel);
        std::string armorNextLevel = "( + ";
        this->armorUpgradeCostText.setString(std::to_string(int(this->allyVector->at(this->pickedCharacter).armor* pow(this->allyVector->at(this->pickedCharacter).armorLevel, 2))));
        this->armorUpgradeCostText.setCharacterSize(25);
        this->armorUpgradeCostText.setFont(this->menuFont);
        this->armorUpgradeCostText.setPosition(sf::Vector2f(0.36 * this->desktopSize.width, 0.8 * this->desktopSize.height));
        this->armorUpgradeCostText.setFillColor(sf::Color(254, 250, 224));
        if (this->allyVector->at(this->pickedCharacter).armorLevel < 6)
        {
            armorNextLevel += "10 )";
        }
        else if (this->allyVector->at(this->pickedCharacter).armorLevel > 5 && this->allyVector->at(this->pickedCharacter).armorLevel < 9)
        {
            armorNextLevel += "25 )";
        }
        else
        {
            armorNextLevel += "50 )";
        }
        if (this->allyVector->at(this->pickedCharacter).armorLevel != 10)
        {
            this->armorUpgradeText.setString("ARMOR  LEVEL:  " + armorLevel + "\n" + "NEXT  LEVEL:  " + armorNextLevel);
        }
        else
        {
            this->armorUpgradeText.setString("ARMOR  LEVEL:  MAX");
            this->possibleUpgrade[1] = false;
            this->armorUpgradeText.setPosition(sf::Vector2f(0.15 * this->desktopSize.width, 0.805 * this->desktopSize.height));
        }
        // MAGIC RESIST LEVEL
        if (this->allyVector->at(this->pickedCharacter).magicResist * pow(this->allyVector->at(this->pickedCharacter).magicResistLevel, 2) <= this->player->money)
        {
            this->possibleUpgrade[4] = true;
        }
        else
        {
            this->possibleUpgrade[4] = false;
        }
        std::string magicResistLevel = std::to_string(this->allyVector->at(this->pickedCharacter).magicResistLevel);
        std::string magicResistNextLevel = "( + ";
        this->magicResistUpgradeCostText.setString(std::to_string(int(this->allyVector->at(this->pickedCharacter).magicResist* pow(this->allyVector->at(this->pickedCharacter).magicResistLevel, 2))));
        this->magicResistUpgradeCostText.setCharacterSize(25);
        this->magicResistUpgradeCostText.setFont(this->menuFont);
        this->magicResistUpgradeCostText.setPosition(sf::Vector2f(0.9 * this->desktopSize.width, 0.8 * this->desktopSize.height));
        this->magicResistUpgradeCostText.setFillColor(sf::Color(254, 250, 224));
        if (this->allyVector->at(this->pickedCharacter).magicResistLevel < 6)
        {
            magicResistNextLevel += "10 )";
        }
        else if (this->allyVector->at(this->pickedCharacter).magicResistLevel > 5 && this->allyVector->at(this->pickedCharacter).magicResistLevel < 9)
        {
            magicResistNextLevel += "25 )";
        }
        else
        {
            magicResistNextLevel += "50 )";
        }
        if (this->allyVector->at(this->pickedCharacter).magicResistLevel != 10)
        {
            this->magicResistUpgradeText.setString("MAGIC  RESIST  LEVEL:  " + magicResistLevel + "\n" + "NEXT  LEVEL:  " + magicResistNextLevel);
        }
        else
        {
            this->magicResistUpgradeText.setString("MAGIC  RESIST  LEVEL:  MAX");
            this->possibleUpgrade[4] = false;
            this->magicResistUpgradeText.setPosition(sf::Vector2f(0.55 * this->desktopSize.width, 0.805 * this->desktopSize.height));
        }
        // SUPER POWER LEVEL
        if ((this->allyVector->at(this->pickedCharacter).superPowerLevel) * 1000 <= this->player->money)
        {
            this->possibleUpgrade[2] = true;
        }
        else
        {
            this->possibleUpgrade[2] = false;
        }
        std::string superPowerLevel = std::to_string(this->allyVector->at(this->pickedCharacter).superPowerLevel);
        std::string superPowerNextLevel = "( + 0.5 )";
        this->superPowerUpgradeCostText.setString(std::to_string(int((this->allyVector->at(this->pickedCharacter).superPowerLevel) * 1000)));
        this->superPowerUpgradeCostText.setCharacterSize(25);
        this->superPowerUpgradeCostText.setFont(this->menuFont);
        this->superPowerUpgradeCostText.setPosition(sf::Vector2f(0.36 * this->desktopSize.width, 0.9 * this->desktopSize.height));
        this->superPowerUpgradeCostText.setFillColor(sf::Color(254, 250, 224));
        if (this->allyVector->at(this->pickedCharacter).superPowerLevel != 10)
        {
            this->superPowerUpgradeText.setString("SUPER  POWER  LEVEL:  " + superPowerLevel + "\n" + "NEXT  LEVEL:  " + superPowerNextLevel);
        }
        else
        {
            this->superPowerUpgradeText.setString("SUPER  POWER  LEVEL:  MAX");
            this->possibleUpgrade[2] = false;
            this->superPowerUpgradeText.setPosition(sf::Vector2f(0.15 * this->desktopSize.width, 0.905 * this->desktopSize.height));
        }
    }
    else if (this->pickedCharacter == 2)
    {
        std::string moneyString = std::to_string(this->player->money);
        this->moneyText.setString(moneyString);
        // LIFE LEVEL
        std::string lifeLevel = std::to_string(this->allyVector->at(this->pickedCharacter).lifeLevel);
        std::string lifeNextLevel = "( + ";
        if (this->allyVector->at(this->pickedCharacter).lifeLevel < 5)
        {
            lifeNextLevel += "5000 )";
            this->lifeUpgradeCostText.setString(std::to_string(int(this->allyVector->at(this->pickedCharacter).life) + 5000));
            this->lifeUpgradeCostText.setCharacterSize(25);
            this->lifeUpgradeCostText.setFont(this->menuFont);
            this->lifeUpgradeCostText.setPosition(sf::Vector2f(0.36 * this->desktopSize.width, 0.7 * this->desktopSize.height));
            this->lifeUpgradeCostText.setFillColor(sf::Color(254, 250, 224));
            if (this->allyVector->at(this->pickedCharacter).life + 5000 <= this->player->money)
            {
                this->possibleUpgrade[0] = true;
            }
            else
            {
                this->possibleUpgrade[0] = false;
            }
        }
        else
        {
            lifeNextLevel += "2500 )";
            this->lifeUpgradeCostText.setString(std::to_string(int(this->allyVector->at(this->pickedCharacter).life) + 2500));
            this->lifeUpgradeCostText.setCharacterSize(25);
            this->lifeUpgradeCostText.setFont(this->menuFont);
            this->lifeUpgradeCostText.setPosition(sf::Vector2f(0.36 * this->desktopSize.width, 0.7 * this->desktopSize.height));
            this->lifeUpgradeCostText.setFillColor(sf::Color(254, 250, 224));
            if (this->allyVector->at(this->pickedCharacter).life + 2500 <= this->player->money)
            {
                this->possibleUpgrade[0] = true;
            }
            else
            {
                this->possibleUpgrade[0] = false;
            }
        }
        if (this->allyVector->at(this->pickedCharacter).lifeLevel != 10)
        {
            this->lifeUpgradeText.setString("LIFE  LEVEL:  " + lifeLevel + "\n" + "NEXT  LEVEL:  " + lifeNextLevel);
        }
        else
        {
            this->lifeUpgradeText.setString("LIFE  LEVEL:  MAX");
            this->possibleUpgrade[0] = false;
            this->lifeUpgradeText.setPosition(sf::Vector2f(0.15 * this->desktopSize.width, 0.705 * this->desktopSize.height));
        }
        // POWER LEVEL
        if (this->allyVector->at(this->pickedCharacter).power * pow(this->allyVector->at(this->pickedCharacter).powerLevel, 2) <= this->player->money)
        {
            this->possibleUpgrade[3] = true;
        }
        else
        {
            this->possibleUpgrade[3] = false;
        }
        std::string powerLevel = std::to_string(this->allyVector->at(this->pickedCharacter).powerLevel);
        std::string powerNextLevel = "( + 100 )";
        this->powerUpgradeCostText.setString(std::to_string(int(this->allyVector->at(this->pickedCharacter).power* pow(this->allyVector->at(this->pickedCharacter).powerLevel, 2))));
        this->powerUpgradeCostText.setCharacterSize(25);
        this->powerUpgradeCostText.setFont(this->menuFont);
        this->powerUpgradeCostText.setPosition(sf::Vector2f(0.9 * this->desktopSize.width, 0.7 * this->desktopSize.height));
        this->powerUpgradeCostText.setFillColor(sf::Color(254, 250, 224));
        if (this->allyVector->at(this->pickedCharacter).powerLevel != 10)
        {
            this->powerUpgradeText.setString("POWER  LEVEL:  " + powerLevel + "\n" + "NEXT  LEVEL:  " + powerNextLevel);
        }
        else
        {
            this->powerUpgradeText.setString("POWER  LEVEL:  MAX");
            this->possibleUpgrade[3] = false;
            this->powerUpgradeText.setPosition(sf::Vector2f(0.55 * this->desktopSize.width, 0.705 * this->desktopSize.height));
        }
        // ARMOR LEVEL
        if (this->allyVector->at(this->pickedCharacter).armor * pow(this->allyVector->at(this->pickedCharacter).armorLevel, 2) <= this->player->money)
        {
            this->possibleUpgrade[1] = true;
        }
        else
        {
            this->possibleUpgrade[1] = false;
        }
        std::string armorLevel = std::to_string(this->allyVector->at(this->pickedCharacter).armorLevel);
        std::string armorNextLevel = "( + 50 )";
        this->armorUpgradeCostText.setString(std::to_string(int(this->allyVector->at(this->pickedCharacter).armor* pow(this->allyVector->at(this->pickedCharacter).armorLevel, 2))));
        this->armorUpgradeCostText.setCharacterSize(25);
        this->armorUpgradeCostText.setFont(this->menuFont);
        this->armorUpgradeCostText.setPosition(sf::Vector2f(0.36 * this->desktopSize.width, 0.8 * this->desktopSize.height));
        this->armorUpgradeCostText.setFillColor(sf::Color(254, 250, 224));
        if (this->allyVector->at(this->pickedCharacter).armorLevel != 10)
        {
            this->armorUpgradeText.setString("ARMOR  LEVEL:  " + armorLevel + "\n" + "NEXT  LEVEL:  " + armorNextLevel);
        }
        else
        {
            this->armorUpgradeText.setString("ARMOR  LEVEL:  MAX");
            this->possibleUpgrade[1] = false;
            this->armorUpgradeText.setPosition(sf::Vector2f(0.15 * this->desktopSize.width, 0.805 * this->desktopSize.height));
        }
        // MAGIC RESIST LEVEL
        if (this->allyVector->at(this->pickedCharacter).magicResist * pow(this->allyVector->at(this->pickedCharacter).magicResistLevel, 2) <= this->player->money)
        {
            this->possibleUpgrade[4] = true;
        }
        else
        {
            this->possibleUpgrade[4] = false;
        }
        std::string magicResistLevel = std::to_string(this->allyVector->at(this->pickedCharacter).magicResistLevel);
        std::string magicResistNextLevel = "( + 50 )";
        this->magicResistUpgradeCostText.setString(std::to_string(int(this->allyVector->at(this->pickedCharacter).magicResist* pow(this->allyVector->at(this->pickedCharacter).magicResistLevel, 2))));
        this->magicResistUpgradeCostText.setCharacterSize(25);
        this->magicResistUpgradeCostText.setFont(this->menuFont);
        this->magicResistUpgradeCostText.setPosition(sf::Vector2f(0.9 * this->desktopSize.width, 0.8 * this->desktopSize.height));
        this->magicResistUpgradeCostText.setFillColor(sf::Color(254, 250, 224));
        if (this->allyVector->at(this->pickedCharacter).magicResistLevel != 10)
        {
            this->magicResistUpgradeText.setString("MAGIC  RESIST  LEVEL:  " + magicResistLevel + "\n" + "NEXT  LEVEL:  " + magicResistNextLevel);
        }
        else
        {
            this->magicResistUpgradeText.setString("MAGIC  RESIST  LEVEL:  MAX");
            this->possibleUpgrade[4] = false;
            this->magicResistUpgradeText.setPosition(sf::Vector2f(0.55 * this->desktopSize.width, 0.805 * this->desktopSize.height));
        }
        // SUPER POWER LEVEL
        if ((this->allyVector->at(this->pickedCharacter).superPowerLevel) * 2000 <= this->player->money)
        {
            this->possibleUpgrade[2] = true;
        }
        else
        {
            this->possibleUpgrade[2] = false;
        }
        std::string superPowerLevel = std::to_string(this->allyVector->at(this->pickedCharacter).superPowerLevel);
        std::string superPowerNextLevel = "( + 0.5 )";
        this->superPowerUpgradeCostText.setString(std::to_string(int((this->allyVector->at(this->pickedCharacter).superPowerLevel) * 2000)));
        this->superPowerUpgradeCostText.setCharacterSize(25);
        this->superPowerUpgradeCostText.setFont(this->menuFont);
        this->superPowerUpgradeCostText.setPosition(sf::Vector2f(0.36 * this->desktopSize.width, 0.9 * this->desktopSize.height));
        this->superPowerUpgradeCostText.setFillColor(sf::Color(254, 250, 224));
        if (this->allyVector->at(this->pickedCharacter).superPowerLevel != 10)
        {
            this->superPowerUpgradeText.setString("SUPER  POWER  LEVEL:  " + superPowerLevel + "\n" + "NEXT  LEVEL:  " + superPowerNextLevel);
        }
        else
        {
            this->superPowerUpgradeText.setString("SUPER  POWER  LEVEL:  MAX");
            this->possibleUpgrade[2] = false;
            this->superPowerUpgradeText.setPosition(sf::Vector2f(0.15 * this->desktopSize.width, 0.905 * this->desktopSize.height));
        }
    }
    this->lifeText.setString(std::to_string(int(this->allyVector->at(this->pickedCharacter).life)));
    this->powerText.setString(std::to_string(int(this->allyVector->at(this->pickedCharacter).power)));
    this->armorText.setString(std::to_string(int(this->allyVector->at(this->pickedCharacter).armor)));
    this->magicResistText.setString(std::to_string(int(this->allyVector->at(this->pickedCharacter).magicResist)));
    this->superPowerText.setString(std::to_string(this->allyVector->at(this->pickedCharacter).superPower).substr(0, 3));
}

Shop::~Shop()
{
    this->file.close();
}
