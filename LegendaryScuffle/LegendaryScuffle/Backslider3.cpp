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

	// Game textures
	this->loadPickedTexture(2);
}

Backslider3::~Backslider3()
{
}
