#include "Backslider1.h"

Backslider1::Backslider1()
{
	this->armor = 15.0;
	this->life = 100.0;
	this->magicResist = 15.0;
	this->power = 10.0;
	this->superPower = 1.0;

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
	this->sprite.setTexture(this->texture);
}

Backslider1::~Backslider1()
{
}
