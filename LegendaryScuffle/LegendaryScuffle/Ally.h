#pragma once
#include <SFML/Graphics.hpp>
#include "Character.h"

class Ally : public Character
{
public:

	// Shop
	bool isUnlocked;
	int lifeLevel;
	int powerLevel;
	int magicResistLevel;
	int armorLevel;
	int superPowerLevel;
	sf::Sprite getSprite();
	/////////////////////////

	double magicResist;
	double armor;
	double superPower;

	void move();
	void attack();
	void dead();
	void loadPickedTexture(int pickedCharacter);
	void updateTexture(std::vector<sf::Texture>* textureVector, float* deltaTime, const float* deltaTimeMax, float* pauseTime, int* clip);
	void animationInterval();

	// Texture
	std::vector<sf::Texture> playerMoveTexture;
	std::vector<sf::Texture> playerStaticAttackTexture;
	std::vector<sf::Texture> playerDynamicAttackTexture;
	std::vector<sf::Texture> playerDeadTexture;

	// Sprite
	sf::Sprite playerSprite;

	// Animation
	bool attackAnimation = false;

protected:
	sf::Sprite shopSprite;

private:
	const sf::VideoMode desktopSize = sf::VideoMode::getDesktopMode();

	// Animation
	sf::Clock clock;

	float deltaTimeMove = 0.0f;
    float pauseTimeMove = 0.0f;
	const float deltaTimeMaxMove = 0.06f;
	int clipMove = 0;

	float deltaTimeAttack = 0.0f;
	float pauseTimeAttack = 0.0f;
	const float deltaTimeMaxAttack = 0.05f;
	int clipAttack = 0;
	
};

