#include "Satyr2.h"

Satyr2::Satyr2()
{
	this->type = 0;
	this->life = 50.0;
	this->power = 20.0;
	this->moveSpeed = 1.5;

	// HP text
	this->hpAmountText.setString("HP: " + std::to_string(this->life));
	this->font.loadFromFile("assets/fonts/FredokaOne-Regular.ttf");
	this->hpAmountText.setFont(font);
	this->hpAmountText.setFillColor(sf::Color(254, 250, 224));
	this->hpAmountText.setCharacterSize(20);
	this->hpAmountText.setPosition(sf::Vector2f(this->enemySprite.getGlobalBounds().left + 270, this->enemySprite.getGlobalBounds().top + 500));

	// Game textures
	this->loadPickedTexture(1,2);
}

Satyr2::~Satyr2()
{
}
