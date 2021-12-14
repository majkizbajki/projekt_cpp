#include "Round.h"

Round::Round()
{
    this->barrelsTexture.loadFromFile("assets/other.png",sf::IntRect(131,3532,57,83));
    this->barrelsTexture.setSmooth(true);
    this->mapTextures.push_back(this->barrelsTexture);

    this->fountainTexture.loadFromFile("assets/other.png", sf::IntRect(0, 3712, 96, 94));
    this->fountainTexture.setSmooth(true);
    this->mapTextures.push_back(this->fountainTexture);

    this->treeTexture.loadFromFile("assets/other.png", sf::IntRect(66, 32, 60, 64));
    this->treeTexture.setSmooth(true);
    this->mapTextures.push_back(this->treeTexture);

    this->barrelsSprite.setTexture(this->mapTextures[0]);
    this->barrelsSprite.setPosition(sf::Vector2f(0.6 * this->desktopSize.width, 0.4 * this->desktopSize.height));
    this->barrelsSprite.scale(3, 3);
    this->mapSprites.push_back(this->barrelsSprite);

    this->fountainSprite.setTexture(this->mapTextures[1]);
    this->fountainSprite.setPosition(sf::Vector2f(0.4 * this->desktopSize.width, 0.7 * this->desktopSize.height));
    this->fountainSprite.scale(2, 2);
    this->mapSprites.push_back(this->fountainSprite);

    this->treeSprite.setTexture(this->mapTextures[2]);
    this->treeSprite.setPosition(sf::Vector2f(0.2 * this->desktopSize.width, 0.2 * this->desktopSize.height));
    this->treeSprite.scale(3, 3);
    this->mapSprites.push_back(this->treeSprite);
}

void Round::generateRound()
{
    this->enemyVector.push_back(*this->satyr1);
    this->enemyVector.push_back(*this->satyr2);
    this->enemyVector.push_back(*this->satyr3);
}

Round::~Round()
{
    delete this->satyr1;
    delete this->satyr2;
    delete this->satyr3;
    this->enemyVector.clear();
}
