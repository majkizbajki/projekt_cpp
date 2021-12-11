#include "Satyr2.h"

Satyr2::Satyr2()
{
	this->type = 0;
	this->life = 50.0;
	this->power = 20.0;
	this->moveSpeed = 2;

	// Game textures
	this->loadPickedTexture(1,2);
}

Satyr2::~Satyr2()
{
}
