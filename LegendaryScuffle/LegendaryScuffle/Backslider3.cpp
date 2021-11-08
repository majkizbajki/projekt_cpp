#include "Backslider3.h"

Backslider3::Backslider3()
{
	this->armor = 10.0;
	this->life = 100.0;
	this->magicResist = 10.0;
	this->power = 10.0;

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
	this->sprite.setTexture(this->texture);
}

Backslider3::~Backslider3()
{
}
