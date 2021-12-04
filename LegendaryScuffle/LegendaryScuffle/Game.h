#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <string>
#include "Backslider1.h"
#include "Backslider2.h"
#include "Backslider3.h"
#include "Enemy.h"

class Game
{
public:
	bool isGameOpen;
	bool isGamePaused;
	bool isGameEnded;
	bool isRoundEnded;
	int round = 1;

	short pickedCharacter;
	Backslider1* backslider1;
	Backslider2* backslider2;
	Backslider3* backslider3;
	std::vector<Enemy> enemyVector;

	Game(sf::Font* menuFont,short* pickedCharacter, Backslider1* backslider1, Backslider2* backslider2, Backslider3* backslider3);

	void openGame(sf::RectangleShape* button, sf::RenderWindow* window, bool* isMenuWindowOpen);
	void closeGame(bool* isMenuWindowOpen, sf::Music* music);
	void continueGame();

	void drawGame(sf::RenderWindow* window);
	~Game();

private:
	const sf::VideoMode desktopSize = sf::VideoMode::getDesktopMode();

	// Font
	sf::Font gameFont;

	// Rectangle
	sf::RectangleShape continueGameButton;
	sf::RectangleShape exitGameButton;

	// Text
	sf::Text continueGameText;
	sf::Text exitGameText;

	// Animation
	sf::Clock clock;
};

