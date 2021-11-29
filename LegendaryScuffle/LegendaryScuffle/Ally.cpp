#include "Ally.h"
#include <iostream>

sf::Sprite Ally::getSprite()
{
	return this->shopSprite;
}

void Ally::move()
{
    if (this->life > 0)
    {
        if (this->attackAnimation == false)
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            {
                this->playerSprite.move(sf::Vector2f(0, -3));
                this->updateTexture(&this->playerMoveTexture, &this->deltaTimeMove, &this->deltaTimeMaxMove, &this->pauseTimeMove, &this->clipMove);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            {
                if (this->playerSprite.getScale().x > 0)
                {
                    this->playerSprite.setPosition(sf::Vector2f(this->playerSprite.getPosition().x + this->playerSprite.getGlobalBounds().width, this->playerSprite.getPosition().y));
                }
                this->playerSprite.move(sf::Vector2f(-3, 0));
                this->updateTexture(&this->playerMoveTexture, &this->deltaTimeMove, &this->deltaTimeMaxMove, &this->pauseTimeMove, &this->clipMove);
                this->playerSprite.setScale(-0.25, 0.25);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            {
                this->playerSprite.move(sf::Vector2f(0, 3));
                this->updateTexture(&this->playerMoveTexture, &this->deltaTimeMove, &this->deltaTimeMaxMove, &this->pauseTimeMove, &this->clipMove);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            {
                if (this->playerSprite.getScale().x < 0)
                {
                    this->playerSprite.setPosition(sf::Vector2f(this->playerSprite.getPosition().x - this->playerSprite.getGlobalBounds().width, this->playerSprite.getPosition().y));
                }
                this->playerSprite.move(sf::Vector2f(3, 0));
                this->updateTexture(&this->playerMoveTexture, &this->deltaTimeMove, &this->deltaTimeMaxMove, &this->pauseTimeMove, &this->clipMove);
                this->playerSprite.setScale(0.25, 0.25);
            }
        }
    }
}

void Ally::attack()
{
    if (this->life > 0)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && this->attackAnimation == true)
        {
            this->playerSprite.move(sf::Vector2f(0, -3));
            this->updateTexture(&this->playerDynamicAttackTexture, &this->deltaTimeAttack, &this->deltaTimeMaxAttack, &this->pauseTimeAttack, &this->clipAttack);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && this->attackAnimation == true)
        {
            this->playerSprite.move(sf::Vector2f(-3, 0));
            this->updateTexture(&this->playerDynamicAttackTexture, &this->deltaTimeAttack, &this->deltaTimeMaxAttack, &this->pauseTimeAttack, &this->clipAttack);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && this->attackAnimation == true)
        {
            this->playerSprite.move(sf::Vector2f(0, 3));
            this->updateTexture(&this->playerDynamicAttackTexture, &this->deltaTimeAttack, &this->deltaTimeMaxAttack, &this->pauseTimeAttack, &this->clipAttack);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && this->attackAnimation == true)
        {
            this->playerSprite.move(sf::Vector2f(3, 0));
            this->updateTexture(&this->playerDynamicAttackTexture, &this->deltaTimeAttack, &this->deltaTimeMaxAttack, &this->pauseTimeAttack, &this->clipAttack);
        }
        else if (this->attackAnimation == true)
        {
            this->updateTexture(&this->playerStaticAttackTexture, &this->deltaTimeAttack, &this->deltaTimeMaxAttack, &this->pauseTimeAttack, &this->clipAttack);
        }
    }
}

void Ally::dead()
{
    if (this->life <= 0 && this->deadAnimation == true)
    {
        this->updateTexture(&this->playerDeadTexture, &this->deltaTimeDead, &this->deltaTimeMaxDead, &this->pauseTimeDead, &this->clipDead);
    }
}

void Ally::loadPickedTexture(int pickedCharacter)
{
    // Player textures
    std::string path = "assets\\player\\player0" + std::to_string(pickedCharacter+1) + "\\";
    for (int i = 0; i < 12; i++)
    {
        if (i < 10)
        {
            std::string run = "running\\running00" + std::to_string(i) + ".png";
            sf::Texture texture;
            texture.loadFromFile(path + run);
            texture.setSmooth(true);
            this->playerMoveTexture.push_back(texture);

            std::string staticAttack = "slashing\\slashing00" + std::to_string(i) + ".png";
            texture.loadFromFile(path + staticAttack);
            texture.setSmooth(true);
            this->playerStaticAttackTexture.push_back(texture);

            std::string dynamicAttack = "slashingrun\\slashingrun00" + std::to_string(i) + ".png";
            texture.loadFromFile(path + dynamicAttack);
            texture.setSmooth(true);
            this->playerDynamicAttackTexture.push_back(texture);

            std::string dead = "dead\\dead00" + std::to_string(i) + ".png";
            texture.loadFromFile(path + dead);
            texture.setSmooth(true);
            this->playerDeadTexture.push_back(texture);
        }
        else
        {
            std::string run = "running\\running0" + std::to_string(i) + ".png";
            sf::Texture texture;
            texture.loadFromFile(path + run);
            texture.setSmooth(true);
            this->playerMoveTexture.push_back(texture);

            std::string staticAttack = "slashing\\slashing0" + std::to_string(i) + ".png";
            texture.loadFromFile(path + staticAttack);
            texture.setSmooth(true);
            this->playerStaticAttackTexture.push_back(texture);

            std::string dynamicAttack = "slashingrun\\slashingrun0" + std::to_string(i) + ".png";
            texture.loadFromFile(path + dynamicAttack);
            texture.setSmooth(true);
            this->playerDynamicAttackTexture.push_back(texture);

            std::string dead = "dead\\dead0" + std::to_string(i) + ".png";
            texture.loadFromFile(path + dead);
            texture.setSmooth(true);
            this->playerDeadTexture.push_back(texture);
        }
    }

    // Player Sprite
    this->playerSprite.setTexture(this->playerMoveTexture[0]);
    this->playerSprite.setScale(0.25, 0.25);
    this->playerSprite.setPosition(sf::Vector2f(0.1 * this->desktopSize.width, 0.45 * this->desktopSize.height));
}

void Ally::updateTexture(std::vector<sf::Texture>* textureVector, float* deltaTime, const float* deltaTimeMax, float* pauseTime, int* clip)
{
    if (*deltaTime >= *deltaTimeMax)
    {
        if (*clip < 11)
        {
            *clip += 1;
        }
        else
        {
            *pauseTime = 0.0f;
            *clip = 0;
            if (&this->clipAttack == clip)
            {
                this->attackAnimation = false;
            }
            if (&this->clipDead == clip)
            {
                this->deadAnimation = false;
                this->endRound = true;
            }
        }
        *deltaTime = 0.0f;

        this->playerSprite.setTexture(textureVector->at(*clip));
    }
}

void Ally::animationInterval()
{
    float clockLaps = clock.restart().asSeconds();
    this->deltaTimeMove += clockLaps;
    this->pauseTimeMove += clockLaps;
    this->deltaTimeAttack += clockLaps;
    this->pauseTimeAttack += clockLaps;
    this->deltaTimeDead += clockLaps;
    this->pauseTimeDead += clockLaps;
}
