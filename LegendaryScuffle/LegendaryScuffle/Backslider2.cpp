#include "Backslider2.h"
#include <fstream>
#include <string>

Backslider2::Backslider2()
{
	this->file.open("saves/backslider2.txt", std::ios::in | std::ios::out);
	if (this->file.good() == true)
	{
		std::string text;
		while (std::getline(this->file, text))
		{
			std::size_t f = text.find("isUnlocked");
			if (f != std::string::npos)
			{
				std::string isUnlocked = text.substr(f + 11);
				this->isUnlocked = std::stoi(isUnlocked);
			}

			f = text.find("armorLevel");
			if (f != std::string::npos)
			{
				std::string armorLevel = text.substr(f + 11);
				this->armorLevel = std::stoi(armorLevel);
			}

			f = text.find("lifeLevel");
			if (f != std::string::npos)
			{
				std::string lifeLevel = text.substr(f + 10);
				this->lifeLevel = std::stoi(lifeLevel);
			}

			f = text.find("magicResistLevel");
			if (f != std::string::npos)
			{
				std::string magicResistLevel = text.substr(f + 17);
				this->magicResistLevel = std::stoi(magicResistLevel);
			}

			f = text.find("powerLevel");
			if (f != std::string::npos)
			{
				std::string powerLevel = text.substr(f + 11);
				this->powerLevel = std::stoi(powerLevel);
			}

			f = text.find("superPowerLevel");
			if (f != std::string::npos)
			{
				std::string superPowerLevel = text.substr(f + 16);
				this->superPowerLevel = std::stoi(superPowerLevel);
			}
		}

		this->file.close();
	}
	else
	{
		// Shop
		this->isUnlocked = false;
		this->armorLevel = 1;
		this->lifeLevel = 1;
		this->magicResistLevel = 1;
		this->powerLevel = 1;
		this->superPowerLevel = 1;

		this->file.close();
	}

	// LIFE
	switch (this->lifeLevel)
	{
	case 1:
		this->life = 1000;
		break;
	case 2:
		this->life = 2500;
		break;
	case 3:
		this->life = 5000;
		break;
	case 4:
		this->life = 7500;
		break;
	case 5:
		this->life = 10000;
		break;
	case 6:
		this->life = 12000;
		break;
	case 7:
		this->life = 14000;
		break;
	case 8:
		this->life = 16000;
		break;
	case 9:
		this->life = 18000;
		break;
	case 10:
		this->life = 20000;
		break;
	default:
		this->life = 1000;
		break;
	}

	// POWER
	switch (this->powerLevel)
	{
	case 1:
		this->power = 50;
		break;
	case 2:
		this->power = 75;
		break;
	case 3:
		this->power = 100;
		break;
	case 4:
		this->power = 125;
		break;
	case 5:
		this->power = 150;
		break;
	case 6:
		this->power = 175;
		break;
	case 7:
		this->power = 200;
		break;
	case 8:
		this->power = 250;
		break;
	case 9:
		this->power = 300;
		break;
	case 10:
		this->power = 350;
		break;
	default:
		this->power = 50;
		break;
	}

	// ARMOR
	switch (this->armorLevel)
	{
	case 1:
		this->armor = 25;
		break;
	case 2:
		this->armor = 35;
		break;
	case 3:
		this->armor = 45;
		break;
	case 4:
		this->armor = 55;
		break;
	case 5:
		this->armor = 65;
		break;
	case 6:
		this->armor = 75;
		break;
	case 7:
		this->armor = 100;
		break;
	case 8:
		this->armor = 125;
		break;
	case 9:
		this->armor = 150;
		break;
	case 10:
		this->armor = 200;
		break;
	default:
		this->armor = 25;
		break;
	}

	// MAGIC RESIST
	switch (this->magicResistLevel)
	{
	case 1:
		this->magicResist = 25;
		break;
	case 2:
		this->magicResist = 35;
		break;
	case 3:
		this->magicResist = 45;
		break;
	case 4:
		this->magicResist = 55;
		break;
	case 5:
		this->magicResist = 65;
		break;
	case 6:
		this->magicResist = 75;
		break;
	case 7:
		this->magicResist = 100;
		break;
	case 8:
		this->magicResist = 125;
		break;
	case 9:
		this->magicResist = 150;
		break;
	case 10:
		this->magicResist = 200;
		break;
	default:
		this->magicResist = 50;
		break;
	}

	// SUPER POWER
	switch (this->superPowerLevel)
	{
	case 1:
		this->superPower = 1;
		break;
	case 2:
		this->superPower = 1.5;
		break;
	case 3:
		this->superPower = 2;
		break;
	case 4:
		this->superPower = 2.5;
		break;
	case 5:
		this->superPower = 3;
		break;
	case 6:
		this->superPower = 3.5;
		break;
	case 7:
		this->superPower = 4;
		break;
	case 8:
		this->superPower = 4.5;
		break;
	case 9:
		this->superPower = 5;
		break;
	case 10:
		this->superPower = 5.5;
		break;
	default:
		this->superPower = 1;
		break;
	}

	// Texture and sprite
	this->texture.loadFromFile("assets/player/player02.png");
	this->texture.setSmooth(true);
	this->shopSprite.setTexture(this->texture);

	// HP text
	this->hpAmountText.setString("HP: " + std::to_string(this->life));
	this->font.loadFromFile("assets/fonts/FredokaOne-Regular.ttf");
	this->hpAmountText.setFont(font);
	this->hpAmountText.setFillColor(sf::Color(254, 250, 224));
	this->hpAmountText.setCharacterSize(20);
	this->hpAmountText.setPosition(sf::Vector2f(this->playerSprite.getGlobalBounds().left + 250, this->playerSprite.getGlobalBounds().top + 100));

	// Game textures
	this->loadPickedTexture(1);
}

Backslider2::~Backslider2()
{
	this->file.close();
}
