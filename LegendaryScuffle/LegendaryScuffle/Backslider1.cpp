#include "Backslider1.h"

Backslider1::Backslider1()
{
	// Shop
	this->isUnlocked = true;
	this->armorLevel = 1;
	this->lifeLevel = 1;
	this->magicResistLevel = 1;
	this->powerLevel = 1;
	this->superPowerLevel = 1;

	// Texture and sprite
	this->texture.loadFromFile("assets/player/player01.png");
	this->texture.setSmooth(true);
	this->shopSprite.setTexture(this->texture);

	// HP text
	this->hpAmountText.setString("HP: " + std::to_string(this->life));
	this->font.loadFromFile("assets/fonts/FredokaOne-Regular.ttf");
	this->hpAmountText.setFont(font);
	this->hpAmountText.setFillColor(sf::Color(254, 250, 224));
	this->hpAmountText.setCharacterSize(20);
	this->hpAmountText.setPosition(sf::Vector2f(this->playerSprite.getGlobalBounds().left + 270, this->playerSprite.getGlobalBounds().top + 500));

	// Game textures
	this->loadPickedTexture(0);
}

Backslider1::~Backslider1()
{
}
