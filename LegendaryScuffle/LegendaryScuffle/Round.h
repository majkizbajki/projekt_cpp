#pragma once
#include <SFML/Graphics.hpp>
#include "Enemy.h"
#include "Satyr1.h"
#include "Satyr2.h"
#include "Satyr3.h"

class Round
{
public:
    Satyr1* satyr1 = new Satyr1();
    Satyr2* satyr2 = new Satyr2();
    Satyr3* satyr3 = new Satyr3();
    std::vector<Enemy> enemyVector;
    int round = 1;

    // Textures
    sf::Texture barrelsTexture;
    sf::Texture fountainTexture;
    sf::Texture treeTexture;
    std::vector<sf::Texture> mapTextures;
    // Sprites
    sf::Sprite barrelsSprite;
    sf::Sprite fountainSprite;
    sf::Sprite treeSprite;
    std::vector<sf::Sprite> mapSprites;

	Round();
    void generateRound();
    ~Round();
private:
    const sf::VideoMode desktopSize = sf::VideoMode::getDesktopMode();
};

