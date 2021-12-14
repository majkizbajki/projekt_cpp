#include "Backslider3.h"

Backslider3::Backslider3()
{
	// Shop
	this->isUnlocked = false;
	this->armorLevel = 1;
	this->lifeLevel = 1;
	this->magicResistLevel = 1;
	this->powerLevel = 1;
	this->superPowerLevel = 1;

	// Texture and sprite
	this->texture.loadFromFile("assets/player/player03.png");
	this->texture.setSmooth(true);
	this->shopSprite.setTexture(this->texture);

	// HP text
	std::string hpText = "HP: ";
	this->hpAmountText.setString(hpText + std::to_string(this->life));
	this->font.loadFromFile("assets/fonts/FredokaOne-Regular.ttf");
	this->hpAmountText.setFont(font);
	this->hpAmountText.setFillColor(sf::Color(254, 250, 224));
	this->hpAmountText.setCharacterSize(20);
	this->hpAmountText.setPosition(sf::Vector2f(this->playerSprite.getGlobalBounds().left + 250, this->playerSprite.getGlobalBounds().top + 100));

	// Game textures
	this->loadPickedTexture(2);
}

Backslider3::~Backslider3()
{
}
