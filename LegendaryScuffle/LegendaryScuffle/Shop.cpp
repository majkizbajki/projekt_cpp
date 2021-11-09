#include "Shop.h"
#include <iostream>

Shop::Shop(sf::Font* menuFont, std::vector<Ally>* allyVector)
{
    this->isShopOpen = false;
    this->unlockedCharacter = false;
    this->enoughMoney = false;
    this->pickedCharacter = 1;
    this->allyVector = allyVector;

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
            sprite.setPosition(sf::Vector2f(0.1 * this->desktopSize.width, 0.2 * this->desktopSize.height));
        }
        else if (i % 3 == 1)
        {
            sprite.setPosition(sf::Vector2f(0.4 * this->desktopSize.width, 0.2 * this->desktopSize.height));
        }
        else if (i % 3 == 2)
        {
            sprite.setPosition(sf::Vector2f(0.7 * this->desktopSize.width, 0.2 * this->desktopSize.height));
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
    this->lockedCharacterText.setPosition(sf::Vector2f(0.25 * this->desktopSize.width, 0.7 * this->desktopSize.height));

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
    this->buyButtonText.setPosition(sf::Vector2f(0.49 * this->desktopSize.width, 0.87 * this->desktopSize.height));
    this->buyButton.setSize(sf::Vector2f(400, 90));
    this->buyButton.setFillColor(sf::Color(221, 161, 94));
    this->buyButton.setPosition(sf::Vector2f(0.4 * this->desktopSize.width, 0.85 * this->desktopSize.height));
}

void Shop::openShop(sf::RectangleShape* button, sf::RenderWindow* window, bool* isMenuWindowOpen)
{
    float buttonX = button->getPosition().x;
    float buttonY = button->getPosition().y;
    float buttonWidth = button->getGlobalBounds().width;
    float buttonHeight = button->getGlobalBounds().height;

    float mousePositionX = sf::Mouse::getPosition().x;
    float mousePositionY = sf::Mouse::getPosition().y;

    if (mousePositionX >= buttonX && mousePositionX <= (buttonX + buttonWidth) && mousePositionY >= buttonY && mousePositionY <= (buttonY + buttonHeight))
    {
        this->isShopOpen = true;
        *isMenuWindowOpen = false;

        drawShop(window);
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
        for (int i = 0; i < this->blockedSprites.size(); i++)
        {
            window->draw(this->blockedSprites[i]);
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
                for (int i = 0; i < this->blockedSprites.size(); i++)
                {
                    window->draw(this->blockedSprites[i]);
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

    window->display();
}

void Shop::pickCharacter()
{
    if (this->characterSprites[0].getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y)))
    {
        this->pickedCharacter = 0;
        this->pickCharacterGlow.setPosition(sf::Vector2f(0.1 * this->desktopSize.width, 0.2 * this->desktopSize.height));

        this->unlockedCharacter = this->allyVector->at(0).isUnlocked;
        this->enoughMoney = true;
    }
    else if (this->characterSprites[1].getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y)))
    {
        this->pickedCharacter = 1;
        this->pickCharacterGlow.setPosition(sf::Vector2f(0.4 * this->desktopSize.width, 0.2 * this->desktopSize.height));

        this->unlockedCharacter = this->allyVector->at(1).isUnlocked;
        this->enoughMoney = true;
    }
    else if (this->characterSprites[2].getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y)))
    {
        this->pickedCharacter = 1;
        this->pickCharacterGlow.setPosition(sf::Vector2f(0.7 * this->desktopSize.width, 0.2 * this->desktopSize.height));
    
        this->unlockedCharacter = this->allyVector->at(2).isUnlocked;
        this->enoughMoney = false;
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
        this->allyVector->at(this->pickedCharacter).isUnlocked = true;
    }
}

Shop::~Shop()
{
}
