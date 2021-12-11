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

	// Game textures
	this->loadPickedTexture(0);
}

Backslider1::~Backslider1()
{
}
