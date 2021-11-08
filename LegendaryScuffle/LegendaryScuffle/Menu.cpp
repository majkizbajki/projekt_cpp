#include "Menu.h"

Menu::Menu()
{
	// Fonts
	this->menuFont.loadFromFile("assets/fonts/LuckiestGuy-Regular.ttf");
	this->titleFont.loadFromFile("assets/fonts/FredokaOne-Regular.ttf");

	// Game title
	this->gameTitle.setString("LEGENDARY SCUFFLE");
	this->gameTitle.setFont(this->titleFont);
	this->gameTitle.setCharacterSize(94);
	this->gameTitle.setFillColor(sf::Color(254, 250, 224));
	this->gameTitle.setPosition(sf::Vector2f(0.25 * this->desktopSize.width, 0.1 * this->desktopSize.height));

	// Start game button 
	this->startGameButton.setSize(sf::Vector2f(this->desktopSize.width * 0.3, this->desktopSize.height * 0.08));
	this->startGameButton.setFillColor(sf::Color(221, 161, 94));
	this->startGameButton.setPosition(sf::Vector2f(0.55 * this->desktopSize.width, 0.3 * this->desktopSize.height));

	this->startGameButtonText.setString("START GAME");
	this->startGameButtonText.setFont(this->menuFont);
	this->startGameButtonText.setCharacterSize(40);
	this->startGameButtonText.setFillColor(sf::Color(40, 54, 24));
	this->startGameButtonText.setPosition(sf::Vector2f(0.55 * this->desktopSize.width + this->startGameButton.getSize().x / 2 - this->startGameButtonText.getGlobalBounds().width / 2, 0.3 * this->desktopSize.height + this->startGameButtonText.getCharacterSize() / 2));

	// Shop button
	this->shopButton.setSize(sf::Vector2f(this->desktopSize.width * 0.3, this->desktopSize.height * 0.08));
	this->shopButton.setFillColor(sf::Color(221, 161, 94));
	this->shopButton.setPosition(sf::Vector2f(0.55 * this->desktopSize.width, 0.42 * this->desktopSize.height));

	this->shopButtonText.setString("SHOP");
	this->shopButtonText.setFont(this->menuFont);
	this->shopButtonText.setCharacterSize(40);
	this->shopButtonText.setFillColor(sf::Color(40, 54, 24));
	this->shopButtonText.setPosition(sf::Vector2f(0.55 * this->desktopSize.width + this->shopButton.getSize().x / 2 - this->shopButtonText.getGlobalBounds().width / 2, 0.42 * this->desktopSize.height + this->shopButtonText.getCharacterSize() / 2));

	// Rules/Controls button
	this->rulesButton.setSize(sf::Vector2f(this->desktopSize.width * 0.3, this->desktopSize.height * 0.08));
	this->rulesButton.setFillColor(sf::Color(221, 161, 94));
	this->rulesButton.setPosition(sf::Vector2f(0.15 * this->desktopSize.width, 0.65 * this->desktopSize.height));

	this->rulesButtonText.setString("RULES / CONTROLS");
	this->rulesButtonText.setFont(this->menuFont);
	this->rulesButtonText.setCharacterSize(40);
	this->rulesButtonText.setFillColor(sf::Color(40, 54, 24));
	this->rulesButtonText.setPosition(sf::Vector2f(0.15 * this->desktopSize.width + rulesButton.getSize().x / 2 - this->rulesButtonText.getGlobalBounds().width / 2, 0.65 * this->desktopSize.height + this->rulesButtonText.getCharacterSize() / 2));

	// Exit buttons
	this->exitButton.setSize(sf::Vector2f(this->desktopSize.width * 0.3, this->desktopSize.height * 0.08));
	this->exitButton.setFillColor(sf::Color(221, 161, 94));
	this->exitButton.setPosition(sf::Vector2f(0.15 * this->desktopSize.width, 0.77 * this->desktopSize.height));
	
	this->exitButtonText.setString("EXIT");
	this->exitButtonText.setFont(this->menuFont);
	this->exitButtonText.setCharacterSize(40);
	this->exitButtonText.setFillColor(sf::Color(40, 54, 24));
	this->exitButtonText.setPosition(sf::Vector2f(0.15 * this->desktopSize.width + this->exitButton.getSize().x / 2 - this->exitButtonText.getGlobalBounds().width / 2, 0.77 * this->desktopSize.height + this->exitButtonText.getCharacterSize() / 2));

	// Animation
	this->animationTexture1.loadFromFile("assets/player/player01/slashing/slashing000.png");
	this->animationTexture1.setSmooth(true);

	this->animationSprite1.setTexture(this->animationTexture1);
	this->animationSprite1.setPosition(sf::Vector2f(0.2 * this->desktopSize.width, 0.2 * this->desktopSize.height));
	this->animationSprite1.setScale(0.5, 0.5);

	this->animationTexture2.loadFromFile("assets/player/player02/running/running000.png");
	this->animationTexture2.setSmooth(true);

	this->animationSprite2.setTexture(this->animationTexture2);
	this->animationSprite2.setPosition(sf::Vector2f(0.8 * this->desktopSize.width, 0.5 * this->desktopSize.height));
	this->animationSprite2.setScale(-0.5, 0.5);

	// Music
	this->musicTheme.openFromFile("assets/music/menu/musicTheme.wav");
	this->musicTheme.setLoop(true);
	this->musicTheme.play();

	this->soundOnTexture.loadFromFile("assets/music/icon/sound-on.png");
	this->soundOnTexture.setSmooth(true);

	this->soundOffTexture.loadFromFile("assets/music/icon/no-sound.png");
	this->soundOffTexture.setSmooth(true);

	this->soundButton.setTexture(this->soundOnTexture);
	this->soundButton.setPosition(sf::Vector2f(0.9 * this->desktopSize.width, 0.05 * this->desktopSize.height));
}

void Menu::playPauseMusic()
{
	float buttonX = this->soundButton.getPosition().x;
	float buttonY = this->soundButton.getPosition().y;
	float buttonWidth = this->soundButton.getGlobalBounds().width;
	float buttonHeight = this->soundButton.getGlobalBounds().height;

	float mousePositionX = sf::Mouse::getPosition().x;
	float mousePositionY = sf::Mouse::getPosition().y;

	if (mousePositionX >= buttonX && mousePositionX <= (buttonX + buttonWidth) && mousePositionY >= buttonY && mousePositionY <= (buttonY + buttonHeight))
	{
		if (this->soundButton.getTexture() == &this->soundOnTexture)
		{
			this->soundButton.setTexture(this->soundOffTexture);
			this->musicTheme.pause();
		}
		else
		{
			this->soundButton.setTexture(this->soundOnTexture);
			this->musicTheme.play();
		}

	}
}

void Menu::animationInterval()
{
	float clockLaps = clock.restart().asSeconds();
	this->deltaTime1 += clockLaps;
	this->deltaTime2 += clockLaps;
	this->pauseTime1 += clockLaps;
	this->pauseTime2 += clockLaps;
}

void Menu::updateAnimation(sf::Texture* texture, int* clip, int lastClip, float* deltaTime, const float* deltaTimeMax, float* pauseTime, std::string source)
{
	std::string png = ".png";

	std::string c = "000";
	if (*deltaTime >= *deltaTimeMax)
	{
		if (*clip > 9)
		{
			c = "0";
			c.append(std::to_string(*clip));
		}
		else if (*clip > 99)
		{
			c = std::to_string(*clip);
		}
		else
		{
			c = "00";
			c.append(std::to_string(*clip));
		}

		if (*clip < lastClip)
		{
			*clip += 1;
		}
		else
		{
			*pauseTime = 0.0f;
			*clip = 0;
		}
		*deltaTime = 0.0f;

		source.append(c);
		source.append(png);

		texture->loadFromFile(source);
	}
}

void Menu::drawMenu(sf::RenderWindow* window)
{
	window->clear(sf::Color(96, 108, 56));

	window->draw(this->gameTitle);
	window->draw(this->startGameButton);
	window->draw(this->startGameButtonText);
	window->draw(this->shopButton);
	window->draw(this->shopButtonText);
	window->draw(this->rulesButton);
	window->draw(this->rulesButtonText);
	window->draw(this->exitButton);
	window->draw(this->exitButtonText);
	window->draw(this->soundButton);
	if (this->pauseTime1 >= 3.0f)
	{
		this->updateAnimation(&this->animationTexture1, &this->clip1, 11, &this->deltaTime1, &this->deltaTimeMax1, &this->pauseTime1, "assets/player/player01/slashing/slashing");
	}
	this->updateAnimation(&this->animationTexture2, &this->clip2, 11, &this->deltaTime2, &this->deltaTimeMax2, &pauseTime2, "assets/player/player02/running/running");
	window->draw(this->animationSprite1);
	window->draw(this->animationSprite2);

	window->display();
}

bool Menu::closeGame()
{
	float buttonX = this->exitButton.getPosition().x;
	float buttonY = this->exitButton.getPosition().y;
	float buttonWidth = this->exitButton.getGlobalBounds().width;
	float buttonHeight = this->exitButton.getGlobalBounds().height;

	float mousePositionX = sf::Mouse::getPosition().x;
	float mousePositionY = sf::Mouse::getPosition().y;

	if (mousePositionX >= buttonX && mousePositionX <= (buttonX + buttonWidth) && mousePositionY >= buttonY && mousePositionY <= (buttonY + buttonHeight))
	{
		return true;
	}
	else
	{
		return false;
	}
}

Menu::~Menu()
{
}
