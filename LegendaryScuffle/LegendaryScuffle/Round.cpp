#include "Round.h"
#include <random>

Round::Round()
{
    this->topWallTexture.loadFromFile("assets/other.png", sf::IntRect(0, 869, 32, 23));
    this->topWallTexture.setSmooth(true);
    this->mapTextures.push_back(this->topWallTexture);

    this->leftWallTexture.loadFromFile("assets/other.png", sf::IntRect(43, 837, 9, 56));
    this->leftWallTexture.setSmooth(true);
    this->mapTextures.push_back(this->leftWallTexture);

    this->barrels1Texture.loadFromFile("assets/other.png",sf::IntRect(131,3532,57,83));
    this->barrels1Texture.setSmooth(true);
    this->mapTextures.push_back(this->barrels1Texture);

    this->barrels2Texture.loadFromFile("assets/other.png", sf::IntRect(2, 3544, 59, 71));
    this->barrels2Texture.setSmooth(true);
    this->mapTextures.push_back(this->barrels2Texture);

    this->barrels3Texture.loadFromFile("assets/other.png", sf::IntRect(66, 3544, 60, 72));
    this->barrels3Texture.setSmooth(true);
    this->mapTextures.push_back(this->barrels3Texture);

    this->fountainTexture.loadFromFile("assets/other.png", sf::IntRect(0, 3712, 96, 94));
    this->fountainTexture.setSmooth(true);
    this->mapTextures.push_back(this->fountainTexture);

    this->monument1Texture.loadFromFile("assets/other.png", sf::IntRect(129, 3617, 30, 61));
    this->monument1Texture.setSmooth(true);
    this->mapTextures.push_back(this->monument1Texture);

    this->monument2Texture.loadFromFile("assets/other.png", sf::IntRect(96, 3683, 32, 59));
    this->monument2Texture.setSmooth(true);
    this->mapTextures.push_back(this->monument2Texture);

    this->monument3Texture.loadFromFile("assets/other.png", sf::IntRect(129, 3686, 30, 56));
    this->monument3Texture.setSmooth(true);
    this->mapTextures.push_back(this->monument3Texture);

    this->monument4Texture.loadFromFile("assets/other.png", sf::IntRect(101, 3745, 54, 62));
    this->monument4Texture.setSmooth(true);
    this->mapTextures.push_back(this->monument4Texture);

    this->tree1Texture.loadFromFile("assets/other.png", sf::IntRect(66, 32, 60, 64));
    this->tree1Texture.setSmooth(true);
    this->mapTextures.push_back(this->tree1Texture);

    this->tree2Texture.loadFromFile("assets/other.png", sf::IntRect(2, 32, 60, 64));
    this->tree2Texture.setSmooth(true);
    this->mapTextures.push_back(this->tree2Texture);

    this->tree3Texture.loadFromFile("assets/other.png", sf::IntRect(130, 32, 60, 64));
    this->tree3Texture.setSmooth(true);
    this->mapTextures.push_back(this->tree3Texture);


    this->topWallSprite.setTexture(this->mapTextures[0]);
    this->topWallSprite.setPosition(sf::Vector2f(0, 0));
    this->topWallSprite.scale(2, 3);
    this->mapSprites.push_back(this->topWallSprite);
    this->topWallSprite.setPosition(sf::Vector2f(64, 0));
    this->mapSprites.push_back(this->topWallSprite);
    this->topWallSprite.setPosition(sf::Vector2f(128, 0));
    this->mapSprites.push_back(this->topWallSprite);
    this->topWallSprite.setPosition(sf::Vector2f(192, 0));
    this->mapSprites.push_back(this->topWallSprite);
    this->topWallSprite.setPosition(sf::Vector2f(256, 0));
    this->mapSprites.push_back(this->topWallSprite);
    this->topWallSprite.setPosition(sf::Vector2f(320, 0));
    this->mapSprites.push_back(this->topWallSprite);
    this->topWallSprite.setPosition(sf::Vector2f(384, 0));
    this->mapSprites.push_back(this->topWallSprite);
    this->topWallSprite.setPosition(sf::Vector2f(448, 0));
    this->mapSprites.push_back(this->topWallSprite);
    this->topWallSprite.setPosition(sf::Vector2f(512, 0));
    this->mapSprites.push_back(this->topWallSprite);
    this->topWallSprite.setPosition(sf::Vector2f(576, 0));
    this->mapSprites.push_back(this->topWallSprite);
    this->topWallSprite.setPosition(sf::Vector2f(640, 0));
    this->mapSprites.push_back(this->topWallSprite);
    this->topWallSprite.setPosition(sf::Vector2f(704, 0));
    this->mapSprites.push_back(this->topWallSprite);
    this->topWallSprite.setPosition(sf::Vector2f(768, 0));
    this->mapSprites.push_back(this->topWallSprite);
    this->topWallSprite.setPosition(sf::Vector2f(832, 0));
    this->mapSprites.push_back(this->topWallSprite);
    this->topWallSprite.setPosition(sf::Vector2f(896, 0));
    this->mapSprites.push_back(this->topWallSprite);
    this->topWallSprite.setPosition(sf::Vector2f(960, 0));
    this->mapSprites.push_back(this->topWallSprite);
    this->topWallSprite.setPosition(sf::Vector2f(1024, 0));
    this->mapSprites.push_back(this->topWallSprite);
    this->topWallSprite.setPosition(sf::Vector2f(1088, 0));
    this->mapSprites.push_back(this->topWallSprite);
    this->topWallSprite.setPosition(sf::Vector2f(1152, 0));
    this->mapSprites.push_back(this->topWallSprite);
    this->topWallSprite.setPosition(sf::Vector2f(1216, 0));
    this->mapSprites.push_back(this->topWallSprite);
    this->topWallSprite.setPosition(sf::Vector2f(1280, 0));
    this->mapSprites.push_back(this->topWallSprite);
    this->topWallSprite.setPosition(sf::Vector2f(1344, 0));
    this->mapSprites.push_back(this->topWallSprite);
    this->topWallSprite.setPosition(sf::Vector2f(1408, 0));
    this->mapSprites.push_back(this->topWallSprite);
    this->topWallSprite.setPosition(sf::Vector2f(1472, 0));
    this->mapSprites.push_back(this->topWallSprite);
    this->topWallSprite.setPosition(sf::Vector2f(1536, 0));
    this->mapSprites.push_back(this->topWallSprite);
    this->topWallSprite.setPosition(sf::Vector2f(1600, 0));
    this->mapSprites.push_back(this->topWallSprite);
    this->topWallSprite.setPosition(sf::Vector2f(1664, 0));
    this->mapSprites.push_back(this->topWallSprite);
    this->topWallSprite.setPosition(sf::Vector2f(1728, 0));
    this->mapSprites.push_back(this->topWallSprite);
    this->topWallSprite.setPosition(sf::Vector2f(1792, 0));
    this->mapSprites.push_back(this->topWallSprite);
    this->topWallSprite.setPosition(sf::Vector2f(1856, 0));
    this->mapSprites.push_back(this->topWallSprite);
    this->topWallSprite.setPosition(sf::Vector2f(1920, 0));
    this->mapSprites.push_back(this->topWallSprite);

    this->leftWallSprite.setTexture(this->mapTextures[1]);
    this->leftWallSprite.setPosition(sf::Vector2f(0, -80));
    this->leftWallSprite.scale(3, 3);
    this->mapSprites.push_back(this->leftWallSprite);
    this->leftWallSprite.setPosition(sf::Vector2f(0, 20));
    this->mapSprites.push_back(this->leftWallSprite);
    this->leftWallSprite.setPosition(sf::Vector2f(0, 120));
    this->mapSprites.push_back(this->leftWallSprite);
    this->leftWallSprite.setPosition(sf::Vector2f(0, 220));
    this->mapSprites.push_back(this->leftWallSprite);
    this->leftWallSprite.setPosition(sf::Vector2f(0, 320));
    this->mapSprites.push_back(this->leftWallSprite);
    this->leftWallSprite.setPosition(sf::Vector2f(0, 420));
    this->mapSprites.push_back(this->leftWallSprite);
    this->leftWallSprite.setPosition(sf::Vector2f(0, 520));
    this->mapSprites.push_back(this->leftWallSprite);
    this->leftWallSprite.setPosition(sf::Vector2f(0, 620));
    this->mapSprites.push_back(this->leftWallSprite);
    this->leftWallSprite.setPosition(sf::Vector2f(0, 720));
    this->mapSprites.push_back(this->leftWallSprite);
    this->leftWallSprite.setPosition(sf::Vector2f(0, 820));
    this->mapSprites.push_back(this->leftWallSprite);
    this->leftWallSprite.setPosition(sf::Vector2f(0, 920));
    this->mapSprites.push_back(this->leftWallSprite);
    this->leftWallSprite.setPosition(sf::Vector2f(1894, -80));
    this->mapSprites.push_back(this->leftWallSprite);
    this->leftWallSprite.setPosition(sf::Vector2f(1894, 20));
    this->mapSprites.push_back(this->leftWallSprite);
    this->leftWallSprite.setPosition(sf::Vector2f(1894, 120));
    this->mapSprites.push_back(this->leftWallSprite);
    this->leftWallSprite.setPosition(sf::Vector2f(1894, 220));
    this->mapSprites.push_back(this->leftWallSprite);
    this->leftWallSprite.setPosition(sf::Vector2f(1894, 320));
    this->mapSprites.push_back(this->leftWallSprite);
    this->leftWallSprite.setPosition(sf::Vector2f(1894, 420));
    this->mapSprites.push_back(this->leftWallSprite);
    this->leftWallSprite.setPosition(sf::Vector2f(1894, 520));
    this->mapSprites.push_back(this->leftWallSprite);
    this->leftWallSprite.setPosition(sf::Vector2f(1894, 620));
    this->mapSprites.push_back(this->leftWallSprite);
    this->leftWallSprite.setPosition(sf::Vector2f(1894, 720));
    this->mapSprites.push_back(this->leftWallSprite);
    this->leftWallSprite.setPosition(sf::Vector2f(1894, 820));
    this->mapSprites.push_back(this->leftWallSprite);
    this->leftWallSprite.setPosition(sf::Vector2f(1894, 920));
    this->mapSprites.push_back(this->leftWallSprite);

    this->barrels1Sprite.setTexture(this->mapTextures[2]);
    this->barrels1Sprite.setPosition(sf::Vector2f(0.6 * this->desktopSize.width, 0.4 * this->desktopSize.height));
    this->barrels1Sprite.scale(3, 3);
    this->randomSprites.push_back(this->barrels1Sprite);

    this->barrels2Sprite.setTexture(this->mapTextures[3]);
    this->barrels2Sprite.setPosition(sf::Vector2f(0.6 * this->desktopSize.width, 0.4 * this->desktopSize.height));
    this->barrels2Sprite.scale(3, 3);
    this->randomSprites.push_back(this->barrels2Sprite);

    this->barrels3Sprite.setTexture(this->mapTextures[4]);
    this->barrels3Sprite.setPosition(sf::Vector2f(0.6 * this->desktopSize.width, 0.4 * this->desktopSize.height));
    this->barrels3Sprite.scale(3, 3);
    this->randomSprites.push_back(this->barrels3Sprite);

    this->fountainSprite.setTexture(this->mapTextures[5]);
    this->fountainSprite.setPosition(sf::Vector2f(0.4 * this->desktopSize.width, 0.7 * this->desktopSize.height));
    this->fountainSprite.scale(2, 2);
    this->randomSprites.push_back(this->fountainSprite);

    this->monument1Sprite.setTexture(this->mapTextures[6]);
    this->monument1Sprite.setPosition(sf::Vector2f(0.4 * this->desktopSize.width, 0.7 * this->desktopSize.height));
    this->monument1Sprite.scale(2, 2);
    this->randomSprites.push_back(this->monument1Sprite);

    this->monument2Sprite.setTexture(this->mapTextures[7]);
    this->monument2Sprite.setPosition(sf::Vector2f(0.4 * this->desktopSize.width, 0.7 * this->desktopSize.height));
    this->monument2Sprite.scale(2, 2);
    this->randomSprites.push_back(this->monument2Sprite);

    this->monument3Sprite.setTexture(this->mapTextures[8]);
    this->monument3Sprite.setPosition(sf::Vector2f(0.4 * this->desktopSize.width, 0.7 * this->desktopSize.height));
    this->monument3Sprite.scale(2, 2);
    this->randomSprites.push_back(this->monument3Sprite);

    this->monument4Sprite.setTexture(this->mapTextures[9]);
    this->monument4Sprite.setPosition(sf::Vector2f(0.4 * this->desktopSize.width, 0.7 * this->desktopSize.height));
    this->monument4Sprite.scale(2, 2);
    this->randomSprites.push_back(this->monument4Sprite);

    this->tree1Sprite.setTexture(this->mapTextures[10]);
    this->tree1Sprite.setPosition(sf::Vector2f(0.2 * this->desktopSize.width, 0.2 * this->desktopSize.height));
    this->tree1Sprite.scale(3, 3);
    this->randomSprites.push_back(this->tree1Sprite);

    this->tree2Sprite.setTexture(this->mapTextures[11]);
    this->tree2Sprite.setPosition(sf::Vector2f(0.2 * this->desktopSize.width, 0.2 * this->desktopSize.height));
    this->tree2Sprite.scale(3, 3);
    this->randomSprites.push_back(this->tree2Sprite);

    this->tree3Sprite.setTexture(this->mapTextures[12]);
    this->tree3Sprite.setPosition(sf::Vector2f(0.2 * this->desktopSize.width, 0.2 * this->desktopSize.height));
    this->tree3Sprite.scale(3, 3);
    this->randomSprites.push_back(this->tree3Sprite);
}

void Round::generateRound()
{
    this->enemyVector.clear();
    this->mapSprites.clear();

    this->topWallSprite.setTexture(this->mapTextures[0]);
    this->topWallSprite.setPosition(sf::Vector2f(0, 0));
    this->mapSprites.push_back(this->topWallSprite);
    this->topWallSprite.setPosition(sf::Vector2f(64, 0));
    this->mapSprites.push_back(this->topWallSprite);
    this->topWallSprite.setPosition(sf::Vector2f(128, 0));
    this->mapSprites.push_back(this->topWallSprite);
    this->topWallSprite.setPosition(sf::Vector2f(192, 0));
    this->mapSprites.push_back(this->topWallSprite);
    this->topWallSprite.setPosition(sf::Vector2f(256, 0));
    this->mapSprites.push_back(this->topWallSprite);
    this->topWallSprite.setPosition(sf::Vector2f(320, 0));
    this->mapSprites.push_back(this->topWallSprite);
    this->topWallSprite.setPosition(sf::Vector2f(384, 0));
    this->mapSprites.push_back(this->topWallSprite);
    this->topWallSprite.setPosition(sf::Vector2f(448, 0));
    this->mapSprites.push_back(this->topWallSprite);
    this->topWallSprite.setPosition(sf::Vector2f(512, 0));
    this->mapSprites.push_back(this->topWallSprite);
    this->topWallSprite.setPosition(sf::Vector2f(576, 0));
    this->mapSprites.push_back(this->topWallSprite);
    this->topWallSprite.setPosition(sf::Vector2f(640, 0));
    this->mapSprites.push_back(this->topWallSprite);
    this->topWallSprite.setPosition(sf::Vector2f(704, 0));
    this->mapSprites.push_back(this->topWallSprite);
    this->topWallSprite.setPosition(sf::Vector2f(768, 0));
    this->mapSprites.push_back(this->topWallSprite);
    this->topWallSprite.setPosition(sf::Vector2f(832, 0));
    this->mapSprites.push_back(this->topWallSprite);
    this->topWallSprite.setPosition(sf::Vector2f(896, 0));
    this->mapSprites.push_back(this->topWallSprite);
    this->topWallSprite.setPosition(sf::Vector2f(960, 0));
    this->mapSprites.push_back(this->topWallSprite);
    this->topWallSprite.setPosition(sf::Vector2f(1024, 0));
    this->mapSprites.push_back(this->topWallSprite);
    this->topWallSprite.setPosition(sf::Vector2f(1088, 0));
    this->mapSprites.push_back(this->topWallSprite);
    this->topWallSprite.setPosition(sf::Vector2f(1152, 0));
    this->mapSprites.push_back(this->topWallSprite);
    this->topWallSprite.setPosition(sf::Vector2f(1216, 0));
    this->mapSprites.push_back(this->topWallSprite);
    this->topWallSprite.setPosition(sf::Vector2f(1280, 0));
    this->mapSprites.push_back(this->topWallSprite);
    this->topWallSprite.setPosition(sf::Vector2f(1344, 0));
    this->mapSprites.push_back(this->topWallSprite);
    this->topWallSprite.setPosition(sf::Vector2f(1408, 0));
    this->mapSprites.push_back(this->topWallSprite);
    this->topWallSprite.setPosition(sf::Vector2f(1472, 0));
    this->mapSprites.push_back(this->topWallSprite);
    this->topWallSprite.setPosition(sf::Vector2f(1536, 0));
    this->mapSprites.push_back(this->topWallSprite);
    this->topWallSprite.setPosition(sf::Vector2f(1600, 0));
    this->mapSprites.push_back(this->topWallSprite);
    this->topWallSprite.setPosition(sf::Vector2f(1664, 0));
    this->mapSprites.push_back(this->topWallSprite);
    this->topWallSprite.setPosition(sf::Vector2f(1728, 0));
    this->mapSprites.push_back(this->topWallSprite);
    this->topWallSprite.setPosition(sf::Vector2f(1792, 0));
    this->mapSprites.push_back(this->topWallSprite);
    this->topWallSprite.setPosition(sf::Vector2f(1856, 0));
    this->mapSprites.push_back(this->topWallSprite);
    this->topWallSprite.setPosition(sf::Vector2f(1920, 0));
    this->mapSprites.push_back(this->topWallSprite);

    this->leftWallSprite.setTexture(this->mapTextures[1]);
    this->leftWallSprite.setPosition(sf::Vector2f(0, -80));
    this->mapSprites.push_back(this->leftWallSprite);
    this->leftWallSprite.setPosition(sf::Vector2f(0, 20));
    this->mapSprites.push_back(this->leftWallSprite);
    this->leftWallSprite.setPosition(sf::Vector2f(0, 120));
    this->mapSprites.push_back(this->leftWallSprite);
    this->leftWallSprite.setPosition(sf::Vector2f(0, 220));
    this->mapSprites.push_back(this->leftWallSprite);
    this->leftWallSprite.setPosition(sf::Vector2f(0, 320));
    this->mapSprites.push_back(this->leftWallSprite);
    this->leftWallSprite.setPosition(sf::Vector2f(0, 420));
    this->mapSprites.push_back(this->leftWallSprite);
    this->leftWallSprite.setPosition(sf::Vector2f(0, 520));
    this->mapSprites.push_back(this->leftWallSprite);
    this->leftWallSprite.setPosition(sf::Vector2f(0, 620));
    this->mapSprites.push_back(this->leftWallSprite);
    this->leftWallSprite.setPosition(sf::Vector2f(0, 720));
    this->mapSprites.push_back(this->leftWallSprite);
    this->leftWallSprite.setPosition(sf::Vector2f(0, 820));
    this->mapSprites.push_back(this->leftWallSprite);
    this->leftWallSprite.setPosition(sf::Vector2f(0, 920));
    this->mapSprites.push_back(this->leftWallSprite);
    this->leftWallSprite.setPosition(sf::Vector2f(1894, -80));
    this->mapSprites.push_back(this->leftWallSprite);
    this->leftWallSprite.setPosition(sf::Vector2f(1894, 20));
    this->mapSprites.push_back(this->leftWallSprite);
    this->leftWallSprite.setPosition(sf::Vector2f(1894, 120));
    this->mapSprites.push_back(this->leftWallSprite);
    this->leftWallSprite.setPosition(sf::Vector2f(1894, 220));
    this->mapSprites.push_back(this->leftWallSprite);
    this->leftWallSprite.setPosition(sf::Vector2f(1894, 320));
    this->mapSprites.push_back(this->leftWallSprite);
    this->leftWallSprite.setPosition(sf::Vector2f(1894, 420));
    this->mapSprites.push_back(this->leftWallSprite);
    this->leftWallSprite.setPosition(sf::Vector2f(1894, 520));
    this->mapSprites.push_back(this->leftWallSprite);
    this->leftWallSprite.setPosition(sf::Vector2f(1894, 620));
    this->mapSprites.push_back(this->leftWallSprite);
    this->leftWallSprite.setPosition(sf::Vector2f(1894, 720));
    this->mapSprites.push_back(this->leftWallSprite);
    this->leftWallSprite.setPosition(sf::Vector2f(1894, 820));
    this->mapSprites.push_back(this->leftWallSprite);
    this->leftWallSprite.setPosition(sf::Vector2f(1894, 920));
    this->mapSprites.push_back(this->leftWallSprite);

    if (this->round <= 3)
    {
        this->enemyVector.push_back(*this->satyr1);
    }
    else if (this->round > 3 && this->round <= 6)
    {
        this->enemyVector.push_back(*this->satyr1);
        this->enemyVector.push_back(*this->satyr2);
    }
    else
    {
        this->enemyVector.push_back(*this->satyr3);
    }

    for (int i = 0; i < 4; i++)
    {
        if (i == 0)
        {
            int random = rand() % this->randomSprites.size();
            int x = rand() % 200 + 300;
            int y = rand() % 600 + 200;
            this->randomSprites[random].setPosition(sf::Vector2f(x, y));
            this->mapSprites.push_back(this->randomSprites[random]);
        }
        if (i == 1)
        {
            int random = rand() % this->randomSprites.size();
            int x = rand() % 200 + 600;
            int y = rand() % 600 + 200;
            this->randomSprites[random].setPosition(sf::Vector2f(x, y));
            this->mapSprites.push_back(this->randomSprites[random]);
        }
        if (i == 2)
        {
            int random = rand() % this->randomSprites.size();
            int x = rand() % 200 + 900;
            int y = rand() % 600 + 200;
            this->randomSprites[random].setPosition(sf::Vector2f(x, y));
            this->mapSprites.push_back(this->randomSprites[random]);
        }
        if (i == 3)
        {
            int random = rand() % this->randomSprites.size();
            int x = rand() % 200 + 1200;
            int y = rand() % 600 + 200;
            this->randomSprites[random].setPosition(sf::Vector2f(x, y));
            this->mapSprites.push_back(this->randomSprites[random]);
        }
    }
}

Round::~Round()
{
    delete this->satyr1;
    delete this->satyr2;
    delete this->satyr3;
    this->enemyVector.clear();
}
