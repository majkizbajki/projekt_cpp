#pragma once
#include <SFML/Graphics.hpp>
#include "Character.h"
#include "Ally.h"

class Enemy : public Character
{
public:
	short type; // 0 - power, 1 - magic

	Enemy();
	void move(Ally* player);
	void attack(Ally* player);
	void dead();
	void loadPickedTexture(int enemyType, int enemyID);
	void updateTexture(std::vector<sf::Texture>* textureVector, float* deltaTime, const float* deltaTimeMax, float* pauseTime, int* clip, Ally* player);
	void updateTexture(std::vector<sf::Texture>* textureVector, float* deltaTime, const float* deltaTimeMax, float* pauseTime, int* clip);
	void animationInterval();
	~Enemy();

	// Texture
	std::vector<sf::Texture> enemyMoveTexture;
	std::vector<sf::Texture> enemyAttackTexture;
	std::vector<sf::Texture> enemyDeadTexture;

	// Sprite
	sf::Sprite enemySprite;

	// Animation
	bool attackAnimation = false;
	bool deadAnimation = false;
	bool endRound = false;

	float pauseTimeAttack = 0.0f;

private:
	const sf::VideoMode desktopSize = sf::VideoMode::getDesktopMode();

	// Animation
	sf::Clock clock;

	float deltaTimeMove = 0.0f;
	float pauseTimeMove = 0.0f;
	const float deltaTimeMaxMove = 0.06f;
	int clipMove = 0;

	float deltaTimeAttack = 0.0f;
	const float deltaTimeMaxAttack = 0.05f;
	int clipAttack = 0;

	float deltaTimeDead = 0.0f;
	float pauseTimeDead = 0.0f;
	const float deltaTimeMaxDead = 0.06f;
	int clipDead = 0;
};

