#include "Satyr3.h"

Satyr3::Satyr3()
{
	this->type = 0;
	this->life = 50.0;
	this->power = 20.0;
	this->moveSpeed = 2;

	std::string hpText = "HP: ";
	this->hpAmountText.setString(hpText + std::to_string(this->life));

	// Game textures
	this->loadPickedTexture(1, 3);
}

Satyr3::~Satyr3()
{
}
