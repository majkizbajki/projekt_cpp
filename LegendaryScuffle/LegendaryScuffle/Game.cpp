#include "Game.h"
#include <iostream>

Game::Game(sf::Font* menuFont, short* pickedCharacter, std::vector<Ally>* allyVector, std::vector<Enemy>* enemyVector, std::vector<sf::Sprite>* mapSprites)
{
	this->isGameOpen = false;
    this->isGamePaused = false;
    this->isGameEnded = false;
    this->isRoundEnded = false;
    this->pickedCharacter = *pickedCharacter;
    this->gameFont = *menuFont;

    // Continue game button
    this->continueGameButton.setSize(sf::Vector2f(0.3 * this->desktopSize.width, this->desktopSize.height * 0.08));
    this->continueGameButton.setPosition(sf::Vector2f(0.33 * this->desktopSize.width, 0.45 * this->desktopSize.height));
    this->continueGameButton.setFillColor(sf::Color(221, 161, 94));

    this->continueGameText.setFont(this->gameFont);
    this->continueGameText.setString("CONTINUE");
    this->continueGameText.setCharacterSize(40);
    this->continueGameText.setFillColor(sf::Color(40, 54, 24));
    this->continueGameText.setPosition(sf::Vector2f(0.435 * this->desktopSize.width, 0.47 * this->desktopSize.height));

    // Close game button
    this->exitGameButton.setSize(sf::Vector2f(0.3 * this->desktopSize.width, this->desktopSize.height * 0.08));
    this->exitGameButton.setPosition(sf::Vector2f(0.33 * this->desktopSize.width, 0.6 * this->desktopSize.height));
    this->exitGameButton.setFillColor(sf::Color(221, 161, 94));
    
    this->exitGameText.setFont(this->gameFont);
    this->exitGameText.setString("EXIT TO MENU");
    this->exitGameText.setCharacterSize(40);
    this->exitGameText.setFillColor(sf::Color(40, 54, 24));
    this->exitGameText.setPosition(sf::Vector2f(0.42 * this->desktopSize.width, 0.62 * this->desktopSize.height));

    this->allyVector = allyVector;

    this->enemyVector = enemyVector;

    this->mapSprites = mapSprites;
}

void Game::openGame(sf::RectangleShape* button, sf::RenderWindow* window, bool* isMenuWindowOpen)
{
    this->allyVector->at(0).playerSprite.setPosition(sf::Vector2f(192, 486));
    this->allyVector->at(1).playerSprite.setPosition(sf::Vector2f(192, 486));
    this->allyVector->at(2).playerSprite.setPosition(sf::Vector2f(192, 486));

    float buttonX = button->getPosition().x;
    float buttonY = button->getPosition().y;
    float buttonWidth = button->getGlobalBounds().width;
    float buttonHeight = button->getGlobalBounds().height;

    float mousePositionX = sf::Mouse::getPosition().x;
    float mousePositionY = sf::Mouse::getPosition().y;

    if (mousePositionX >= buttonX && mousePositionX <= (buttonX + buttonWidth) && mousePositionY >= buttonY && mousePositionY <= (buttonY + buttonHeight))
    {
        this->isGameOpen = true;
        *isMenuWindowOpen = false;

        this->drawGame(window);
    }
}

void Game::closeGame(bool* isMenuWindowOpen, sf::Music* music)
{
    if (this->isGamePaused)
    {
        float buttonX = this->exitGameButton.getPosition().x;
        float buttonY = this->exitGameButton.getPosition().y;
        float buttonWidth = this->exitGameButton.getGlobalBounds().width;
        float buttonHeight = this->exitGameButton.getGlobalBounds().height;

        float mousePositionX = sf::Mouse::getPosition().x;
        float mousePositionY = sf::Mouse::getPosition().y;

        if (mousePositionX >= buttonX && mousePositionX <= (buttonX + buttonWidth) && mousePositionY >= buttonY && mousePositionY <= (buttonY + buttonHeight))
        {
            this->isGameOpen = false;
            this->isGamePaused = false;
            *isMenuWindowOpen = true;
            music->setVolume(100);
        }
    }
}

void Game::continueGame()
{
    float buttonX = this->continueGameButton.getPosition().x;
    float buttonY = this->continueGameButton.getPosition().y;
    float buttonWidth = this->continueGameButton.getGlobalBounds().width;
    float buttonHeight = this->continueGameButton.getGlobalBounds().height;

    float mousePositionX = sf::Mouse::getPosition().x;
    float mousePositionY = sf::Mouse::getPosition().y;

    if (mousePositionX >= buttonX && mousePositionX <= (buttonX + buttonWidth) && mousePositionY >= buttonY && mousePositionY <= (buttonY + buttonHeight))
    {
        this->isGamePaused = false;
    }
}

void Game::drawGame(sf::RenderWindow* window)
{
    window->clear(sf::Color(96, 108, 56));

    if (this->isGamePaused)
    {
        window->draw(this->continueGameButton);
        window->draw(this->continueGameText);

        window->draw(this->exitGameButton);
        window->draw(this->exitGameText);
    }
    else
    {
        for (int i = 0; i < mapSprites->size(); i++)
        {
            window->draw(mapSprites->at(i));
        }
        if (this->enemyVector->size() > 0)
        {
            for (int i = 0; i < this->enemyVector->size(); i++)
            {
                if (this->enemyVector->at(i).endRound == false)
                {
                    if (this->pickedCharacter == 0)
                    {
                        this->enemyVector->at(i).move(&this->allyVector->at(0),this->mapSprites);
                        this->enemyVector->at(i).attack(&this->allyVector->at(0));
                        if (this->enemyVector->at(i).life >= 0)
                        {
                            this->enemyVector->at(i).updateHPText();
                        }
                        window->draw(this->enemyVector->at(i).hpAmountText);
                    }
                    else if (this->pickedCharacter == 1)
                    {
                        this->enemyVector->at(i).move(&this->allyVector->at(1), this->mapSprites);
                        this->enemyVector->at(i).attack(&this->allyVector->at(1));
                        if (this->enemyVector->at(i).life >= 0)
                        {
                            this->enemyVector->at(i).updateHPText();
                        }
                        window->draw(this->enemyVector->at(i).hpAmountText);
                    }
                    else if (this->pickedCharacter == 2)
                    {
                        this->enemyVector->at(i).move(&this->allyVector->at(2), this->mapSprites);
                        this->enemyVector->at(i).attack(&this->allyVector->at(2));
                        if (this->enemyVector->at(i).life >= 0)
                        {
                            this->enemyVector->at(i).updateHPText();
                        }
                        window->draw(this->enemyVector->at(i).hpAmountText);
                    }
                    window->draw(this->enemyVector->at(i).enemySprite);
                }
            }
        }
        if (this->pickedCharacter == 0)
        {
            this->allyVector->at(0).move(this->mapSprites);
            this->allyVector->at(0).attack(this->enemyVector,this->mapSprites);
            window->draw(this->allyVector->at(0).playerSprite);
            if (this->allyVector->at(0).life >= 0)
            {
                this->allyVector->at(0).updateHPText();
            }
            window->draw(this->allyVector->at(0).hpAmountText);
        }
        else if (this->pickedCharacter == 1 && this->allyVector->at(1).isUnlocked)
        {
            this->allyVector->at(1).move(this->mapSprites);
            this->allyVector->at(1).attack(this->enemyVector,this->mapSprites);
            window->draw(this->allyVector->at(1).playerSprite);
            if (this->allyVector->at(1).life >= 0)
            {
                this->allyVector->at(1).updateHPText();
            }
            window->draw(this->allyVector->at(1).hpAmountText);
        }
        else if (this->pickedCharacter == 2 && this->allyVector->at(2).isUnlocked)
        {
            this->allyVector->at(2).move(this->mapSprites);
            this->allyVector->at(2).attack(this->enemyVector,this->mapSprites);
            window->draw(this->allyVector->at(2).playerSprite);
            if (this->allyVector->at(2).life >= 0)
            {
                this->allyVector->at(2).updateHPText();
            }
            window->draw(this->allyVector->at(2).hpAmountText);
        }
        else
        {
            this->pickedCharacter = 0;
            this->allyVector->at(0).move(this->mapSprites);
            this->allyVector->at(0).attack(this->enemyVector,this->mapSprites);
            if (this->allyVector->at(0).life >= 0)
            {
                this->allyVector->at(0).updateHPText();
            }
            window->draw(this->allyVector->at(0).playerSprite);
        }
    }
    
    window->display();
}

Game::~Game()
{
}