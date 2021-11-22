#include "Backslider2.h"

Backslider2::Backslider2()
{
	this->armor = 25.0;
	this->life = 1000.0;
	this->magicResist = 25.0;
	this->power = 50.0;
	this->superPower = 1.0;

	// Shop
	this->isUnlocked = false;
	this->armorLevel = 1;
	this->lifeLevel = 1;
	this->magicResistLevel = 1;
	this->powerLevel = 1;
	this->superPowerLevel = 1;

	// Texture and sprite
	this->texture.loadFromFile("assets/player/player02.png");
	this->texture.setSmooth(true);
	this->shopSprite.setTexture(this->texture);

	// Game textures
	this->loadPickedTexture(1);
}

Backslider2::~Backslider2()
{
}
