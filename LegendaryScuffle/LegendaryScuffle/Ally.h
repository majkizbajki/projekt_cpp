#pragma once
#include <SFML/Graphics.hpp>
#include "Character.h"

class Ally : public Character
{
public:
	float magicResist;
	float armor;
	
	// Shop
	bool isUnlocked;
	int lifeLevel;
	int powerLevel;
	int magicResistLevel;
	int armorLevel;
	int superPowerLevel;
	
	sf::Sprite getSprite();

protected:
	sf::Sprite sprite;
};

