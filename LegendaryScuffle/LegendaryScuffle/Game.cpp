#include "Game.h"

Game::Game(sf::Font* menuFont, short* pickedCharacter,Backslider1* backslider1, Backslider2* backslider2, Backslider3* backslider3)
{
	this->isGameOpen = false;
    this->isGamePaused = false;
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

    this->backslider1 = backslider1;
    this->backslider2 = backslider2;
    this->backslider3 = backslider3;
}

void Game::openGame(sf::RectangleShape* button, sf::RenderWindow* window, bool* isMenuWindowOpen)
{
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
            music->play();

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
        backslider1->move();
        backslider1->attack();
        window->draw(backslider1->playerSprite);
    }
    
    window->display();
}

Game::~Game()
{
}