#include "Satyr2.h"

Satyr2::Satyr2()
{
	this->type = 0;
	this->life = 50.0;
	this->power = 20.0;
	this->moveSpeed = 1.5;

	std::string hpText = "HP: ";
	this->hpAmountText.setString(hpText + std::to_string(this->life));

	// Game textures
	this->loadPickedTexture(1,2);
}

Satyr2::~Satyr2()
{
}
