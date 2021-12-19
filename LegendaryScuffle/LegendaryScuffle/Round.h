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
    sf::Texture leftWallTexture;
    sf::Texture topWallTexture;
    sf::Texture barrelsTexture;
    sf::Texture fountainTexture;
    sf::Texture tree1Texture;
    sf::Texture tree2Texture;
    sf::Texture tree3Texture;
    std::vector<sf::Texture> mapTextures;
    // Sprites
    sf::Sprite leftWallSprite;
    sf::Sprite topWallSprite;
    sf::Sprite barrelsSprite;
    sf::Sprite fountainSprite;
    sf::Sprite tree1Sprite;
    sf::Sprite tree2Sprite;
    sf::Sprite tree3Sprite;
    std::vector<sf::Sprite> randomSprites;
    std::vector<sf::Sprite> mapSprites;

	Round();
    void generateRound();
    ~Round();
private:
    const sf::VideoMode desktopSize = sf::VideoMode::getDesktopMode();
};

