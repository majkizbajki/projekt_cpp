#include "Rules.h"

Rules::Rules(sf::Font* menuFont)
{
    this->isRulesOpen = false;

	// Back to menu button
	this->leftArrow.loadFromFile("assets/left-arrow.png");
	this->leftArrow.setSmooth(true);

	this->leftArrowButton.setTexture(this->leftArrow);
	this->leftArrowButton.setPosition(sf::Vector2f(0.05 * this->desktopSize.width, 0.05 * this->desktopSize.height));

    // Rules Text
    this->rulesText.setString("RULES");
    this->rulesText.setFont(*menuFont);
    this->rulesText.setCharacterSize(50);
    this->rulesText.setFillColor(sf::Color(254, 250, 224));
    this->rulesText.setPosition(sf::Vector2f(0.25 * this->desktopSize.width, 0.2 * this->desktopSize.height));

    this->rulesDescriptionText.setString("The main goal of the game is to survive as many\n rounds as possible fighting against the enemies.\n During the game you can get money and bonuses\n that you can spend on character upgrades and\n become even stronger. The game ends when\n all your life is lost and you start over.");
    this->rulesDescriptionText.setFont(*menuFont);
    this->rulesDescriptionText.setCharacterSize(30);
    this->rulesDescriptionText.setFillColor(sf::Color(254, 250, 224));
    this->rulesDescriptionText.setPosition(sf::Vector2f(0.1 * this->desktopSize.width, 0.3 * this->desktopSize.height));

    // Controls text
    this->controlsText.setString("CONTROLS");
    this->controlsText.setFont(*menuFont);
    this->controlsText.setCharacterSize(50);
    this->controlsText.setFillColor(sf::Color(254, 250, 224));
    this->controlsText.setPosition(sf::Vector2f(0.7 * desktopSize.width, 0.2 * desktopSize.height));

    this->wasdText.setString("W,A,S,D - moving");
    this->wasdText.setFont(*menuFont);
    this->wasdText.setCharacterSize(30);
    this->wasdText.setFillColor(sf::Color(254, 250, 224));
    this->wasdText.setPosition(sf::Vector2f(0.6 * desktopSize.width, 0.3 * desktopSize.height));

    this->spaceText.setString("Space - shooting/atacking");
    this->spaceText.setFont(*menuFont);
    this->spaceText.setCharacterSize(30);
    this->spaceText.setFillColor(sf::Color(254, 250, 224));
    this->spaceText.setPosition(sf::Vector2f(0.6 * desktopSize.width, 0.4 * desktopSize.height));

    this->superPowerText.setString("R - using super power");
    this->superPowerText.setFont(*menuFont);
    this->superPowerText.setCharacterSize(30);
    this->superPowerText.setFillColor(sf::Color(254, 250, 224));
    this->superPowerText.setPosition(sf::Vector2f(0.6 * desktopSize.width, 0.5 * desktopSize.height));

    // Rules / controls sf::text vector

    this->rulesControlsAssets.push_back(this->rulesText);
    this->rulesControlsAssets.push_back(this->rulesDescriptionText);
    this->rulesControlsAssets.push_back(this->controlsText);
    this->rulesControlsAssets.push_back(this->wasdText);
    this->rulesControlsAssets.push_back(this->spaceText);
    this->rulesControlsAssets.push_back(this->superPowerText);
}

void Rules::openRules(sf::RectangleShape* button, sf::RenderWindow* window, bool* isMenuWindowOpen)
{
    float buttonX = button->getPosition().x;
    float buttonY = button->getPosition().y;
    float buttonWidth = button->getGlobalBounds().width;
    float buttonHeight = button->getGlobalBounds().height;

    float mousePositionX = sf::Mouse::getPosition().x;
    float mousePositionY = sf::Mouse::getPosition().y;

    if (mousePositionX >= buttonX && mousePositionX <= (buttonX + buttonWidth) && mousePositionY >= buttonY && mousePositionY <= (buttonY + buttonHeight))
    {
        this->isRulesOpen = true;
        *isMenuWindowOpen = false;

        window->clear(sf::Color(96, 108, 56));
        window->draw(this->leftArrowButton);
        for (int i = 0; i < this->rulesControlsAssets.size(); i++)
        {
            window->draw(this->rulesControlsAssets.at(i));
        }
        window->display();
    }
}

void Rules::closeRules(bool* isMenuWindowOpen)
{
    float buttonX = this->leftArrowButton.getPosition().x;
    float buttonY = this->leftArrowButton.getPosition().y;
    float buttonWidth = this->leftArrowButton.getGlobalBounds().width;
    float buttonHeight = this->leftArrowButton.getGlobalBounds().height;

    float mousePositionX = sf::Mouse::getPosition().x;
    float mousePositionY = sf::Mouse::getPosition().y;

    if (mousePositionX >= buttonX && mousePositionX <= (buttonX + buttonWidth) && mousePositionY >= buttonY && mousePositionY <= (buttonY + buttonHeight))
    {
        this->isRulesOpen = false;
        *isMenuWindowOpen = true;
    }
}

Rules::~Rules()
{
}