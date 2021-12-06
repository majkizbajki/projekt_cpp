#include "Satyr1.h"

Satyr1::Satyr1()
{
	this->type = 0;
	this->life = 50.0;
	this->power = 20.0;
	
	// Game textures
	this->loadPickedTexture(1, 1);
}

Satyr1::~Satyr1()
{
}
