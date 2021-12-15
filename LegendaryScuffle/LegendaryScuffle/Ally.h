#pragma once
#include <SFML/Graphics.hpp>
#include "Character.h"
#include "Collision.h"
class Enemy;

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

	void move(std::vector<sf::Sprite>* mapSprites);
	void attack(std::vector<Enemy>* enemyVector, std::vector<sf::Sprite>* mapSprites);
	void dead();
	void setStatistics(int pickedCharacter);
	void loadPickedTexture(int pickedCharacter);
	void updatePlayerTexture(std::vector<sf::Texture>* textureVector, float* deltaTime, const float* deltaTimeMax, float* pauseTime, int* clip, std::vector<Enemy>* enemyVector);
	void updatePlayerTexture(std::vector<sf::Texture>* textureVector, float* deltaTime, const float* deltaTimeMax, float* pauseTime, int* clip);
	void animationInterval();
	~Ally();

	// Texture
	std::vector<sf::Texture> playerMoveTexture;
	std::vector<sf::Texture> playerStaticAttackTexture;
	std::vector<sf::Texture> playerDynamicAttackTexture;
	std::vector<sf::Texture> playerDeadTexture;

	// Sprite
	sf::Sprite playerSprite;

	// HP info text
	sf::Text hpAmountText;
	sf::Font font;

	void updateHPText();

	// Animation
	bool attackAnimation = false;
	bool deadAnimation = false;
	bool endGame = false;

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

	float deltaTimeDead = 0.0f;
	float pauseTimeDead = 0.0f;
	const float deltaTimeMaxDead = 0.06f;
	int clipDead = 0;
	
};

