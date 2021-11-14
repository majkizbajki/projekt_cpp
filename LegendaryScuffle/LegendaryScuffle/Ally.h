#pragma once
#include <SFML/Graphics.hpp>
#include "Character.h"

class Ally : public Character
{
public:
	double magicResist;
	double armor;
	double superPower;
	
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

