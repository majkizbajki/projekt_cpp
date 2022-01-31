#include "Enemy.h"
#include <cstdlib>

void Enemy::move(Ally* player, std::vector<sf::Sprite>* mapSprites)
{
    if (this->life > 0)
    {
        if (this->attackAnimation == false)
        {
            float playerX = player->playerSprite.getGlobalBounds().left + player->playerSprite.getGlobalBounds().width / 2 + 35;
            float playerY = player->playerSprite.getGlobalBounds().top + player->playerSprite.getGlobalBounds().height / 2 + 15;
            float enemyX = this->enemySprite.getGlobalBounds().left + this->enemySprite.getGlobalBounds().width / 2;
            float enemyY = this->enemySprite.getGlobalBounds().top + this->enemySprite.getGlobalBounds().height / 2 - 5;
            bool collision = false;

            sf::Sprite touchedSprite;

            for (int i = 0; i < mapSprites->size(); i++)
            {
                if (Collision::PixelPerfectTest(this->enemySprite, mapSprites->at(i)))
                {
                    collision = true;
                    touchedSprite = mapSprites->at(i);
                    break;
                }
            }
            if (!collision)
            {
                if (playerX <= enemyX && !Collision::PixelPerfectTest(player->playerSprite, this->enemySprite))
                {
                    this->enemySprite.move(sf::Vector2f(-1 * this->moveSpeed, 0));
                    if (this->enemySprite.getScale().x > 0 && (enemyX - playerX) >= 5)
                    {
                        this->enemySprite.setScale(-0.45, 0.45);
                        this->enemySprite.setPosition(sf::Vector2f(this->enemySprite.getPosition().x + this->enemySprite.getGlobalBounds().width, this->enemySprite.getPosition().y));
                    }
                }
                if (playerX > enemyX && !Collision::PixelPerfectTest(player->playerSprite, this->enemySprite))
                {
                    this->enemySprite.move(sf::Vector2f(1 * this->moveSpeed, 0));
                    if (this->enemySprite.getScale().x < 0 && (playerX - enemyX) >= 5)
                    {
                        this->enemySprite.setScale(0.45, 0.45);
                        this->enemySprite.setPosition(sf::Vector2f(this->enemySprite.getPosition().x - this->enemySprite.getGlobalBounds().width, this->enemySprite.getPosition().y));
                    }
                }
                if (playerY <= enemyY && !Collision::PixelPerfectTest(player->playerSprite, this->enemySprite))
                {
                    this->enemySprite.move(sf::Vector2f(0, -1 * this->moveSpeed));
                }
                if (playerY > enemyY && !Collision::PixelPerfectTest(player->playerSprite, this->enemySprite))
                {
                    this->enemySprite.move(sf::Vector2f(0, 1 * this->moveSpeed));
                }
            }
            else
            {
                float spriteX = touchedSprite.getGlobalBounds().left;
                float spriteY = touchedSprite.getGlobalBounds().top;
                float spriteW = touchedSprite.getGlobalBounds().left + touchedSprite.getGlobalBounds().width;
                float spriteH = touchedSprite.getGlobalBounds().top + touchedSprite.getGlobalBounds().height;
                
                if (spriteY <= 0.15 * this->desktopSize.height)
                {
                    if (enemyX <= spriteX)
                    {
                        if (playerX <= enemyX)
                        {
                            this->enemySprite.move(sf::Vector2f(-1 * this->moveSpeed, 0));
                        }
                        else
                        {
                            if (enemyY <= spriteY)   // 1
                            {
                                this->enemySprite.move(sf::Vector2f(1 * this->moveSpeed, 0));
                            }
                            else if (enemyY > spriteY && enemyY <= spriteH) // 4
                            {
                                this->enemySprite.move(sf::Vector2f(0, 1 * this->moveSpeed));
                            }
                            else if (enemyY > spriteH)   // 7
                            {
                                this->enemySprite.move(sf::Vector2f(0, 1 * this->moveSpeed));
                            }
                        }
                    }
                    else if (enemyX <= spriteW && enemyX > spriteX)
                    {
                        if (playerX <= enemyX)
                        {
                            this->enemySprite.move(sf::Vector2f(-1 * this->moveSpeed, 0));
                        }
                        else
                        {
                            this->enemySprite.move(sf::Vector2f(1 * this->moveSpeed, 0));
                        }
                    }
                    else if (enemyX > spriteW)
                    {
                        if (playerX <= enemyX)
                        {
                            if (enemyY <= spriteY)   // 3
                            {
                                this->enemySprite.move(sf::Vector2f(-1 * this->moveSpeed, 0));
                            }
                            else if (enemyY > spriteY && enemyY <= spriteH) // 6
                            {
                                this->enemySprite.move(sf::Vector2f(0, 1 * this->moveSpeed));
                            }
                            else if (enemyY > spriteH)  // 9
                            {
                                this->enemySprite.move(sf::Vector2f(0, 1 * this->moveSpeed));
                            }
                        }
                        else
                        {
                            this->enemySprite.move(sf::Vector2f(1 * this->moveSpeed, 0));
                        }
                    }
                }
                else if (spriteH >= 0.85 * this->desktopSize.height)
                {
                    if (enemyX <= spriteX)
                    {
                        if (playerX <= enemyX)
                        {
                            this->enemySprite.move(sf::Vector2f(-1 * this->moveSpeed, 0));
                        }
                        else
                        {
                            if (enemyY <= spriteY)   // 1
                            {
                                this->enemySprite.move(sf::Vector2f(1 * this->moveSpeed, 0));
                            }
                            else if (enemyY > spriteY && enemyY <= spriteH) // 4
                            {
                                this->enemySprite.move(sf::Vector2f(0, -1 * this->moveSpeed));
                            }
                            else if (enemyY > spriteH)   // 7
                            {
                                this->enemySprite.move(sf::Vector2f(0, -1 * this->moveSpeed));
                            }
                        }
                    }
                    else if (enemyX <= spriteW && enemyX > spriteX)
                    {
                        if (playerX <= enemyX)
                        {
                            this->enemySprite.move(sf::Vector2f(-1 * this->moveSpeed, 0));
                        }
                        else
                        {
                            this->enemySprite.move(sf::Vector2f(1 * this->moveSpeed, 0));
                        }
                    }
                    else if (enemyX > spriteW)
                    {
                        if (playerX <= enemyX)
                        {
                            if (enemyY <= spriteY)   // 3
                            {
                                this->enemySprite.move(sf::Vector2f(-1 * this->moveSpeed, 0));
                            }
                            else if (enemyY > spriteY && enemyY <= spriteH) // 6
                            {
                                this->enemySprite.move(sf::Vector2f(0, -1 * this->moveSpeed));
                            }
                            else if (enemyY > spriteH)  // 9
                            {
                                this->enemySprite.move(sf::Vector2f(0, -1 * this->moveSpeed));
                            }
                        }
                        else
                        {
                            this->enemySprite.move(sf::Vector2f(1 * this->moveSpeed, 0));
                        }
                    }
                }
                else
                {
                    if (enemyX <= spriteX)
                    {
                        if (enemyY <= spriteY)  // 1
                        {
                            if (playerX < enemyX)
                            {
                                this->enemySprite.move(sf::Vector2f(-1 * this->moveSpeed, 0));
                            }
                            else if (playerY <= enemyY)
                            {
                                this->enemySprite.move(sf::Vector2f(0, -1 * this->moveSpeed));
                            }
                            else
                            {
                                this->enemySprite.move(sf::Vector2f(0, 1 * this->moveSpeed));
                            }
                        }
                        else if (enemyY > spriteY && enemyY <= spriteH) // 4
                        {
                            if (playerX < enemyX)
                            {
                                this->enemySprite.move(sf::Vector2f(-1 * this->moveSpeed, 0));
                            }
                            else
                            {
                                this->enemySprite.move(sf::Vector2f(0, 1 * this->moveSpeed));
                            }
                        }
                        else if (enemyY > spriteH)  // 7
                        {
                            if (playerX < enemyX)
                            {
                                this->enemySprite.move(sf::Vector2f(-1 * this->moveSpeed, 0));
                            }
                            else if (playerY > enemyY)
                            {
                                this->enemySprite.move(sf::Vector2f(0, 1 * this->moveSpeed));
                            }
                            else
                            {
                                this->enemySprite.move(sf::Vector2f(1 * this->moveSpeed, 0));
                                if (this->enemySprite.getScale().x < 0 && abs(playerX - enemyX) >= 5)
                                {
                                    this->enemySprite.setScale(0.45, 0.45);
                                    this->enemySprite.setPosition(sf::Vector2f(this->enemySprite.getPosition().x - this->enemySprite.getGlobalBounds().width, this->enemySprite.getPosition().y));
                                }
                            }
                        }
                    }
                    else if (enemyX <= spriteW && enemyX > spriteX)
                    {
                        if (enemyY <= spriteY)  // 2
                        {
                            if (playerX < enemyX)
                            {
                                this->enemySprite.move(sf::Vector2f(0, -1 * this->moveSpeed));
                            }
                            else
                            {
                                this->enemySprite.move(sf::Vector2f(-1 * this->moveSpeed, 0));
                                if (this->enemySprite.getScale().x > 0 && abs(enemyX - playerX) >= 5)
                                {
                                    this->enemySprite.setScale(-0.45, 0.45);
                                    this->enemySprite.setPosition(sf::Vector2f(this->enemySprite.getPosition().x + this->enemySprite.getGlobalBounds().width, this->enemySprite.getPosition().y));
                                }
                            }
                        }
                        else if (enemyY > spriteH)  // 8
                        {
                            if (playerX > enemyX)
                            {
                                this->enemySprite.move(sf::Vector2f(0, 1 * this->moveSpeed));
                            }
                            else
                            {
                                this->enemySprite.move(sf::Vector2f(1 * this->moveSpeed, 0));
                                if (this->enemySprite.getScale().x < 0 && abs(playerX - enemyX) >= 5)
                                {
                                    this->enemySprite.setScale(0.45, 0.45);
                                    this->enemySprite.setPosition(sf::Vector2f(this->enemySprite.getPosition().x - this->enemySprite.getGlobalBounds().width, this->enemySprite.getPosition().y));
                                }
                            }
                        }
                    }
                    else if (enemyX > spriteW)
                    {
                        if (enemyY <= spriteY)  // 3
                        {
                            if (playerX > enemyX)
                            {
                                this->enemySprite.move(sf::Vector2f(1 * this->moveSpeed, 0));
                            }
                            else if (playerY <= enemyY)
                            {
                                this->enemySprite.move(sf::Vector2f(0, -1 * this->moveSpeed));
                            }
                            else
                            {
                                this->enemySprite.move(sf::Vector2f(-1 * this->moveSpeed, 0));
                                if (this->enemySprite.getScale().x > 0 && abs(enemyX - playerX) >= 5)
                                {
                                    this->enemySprite.setScale(-0.45, 0.45);
                                    this->enemySprite.setPosition(sf::Vector2f(this->enemySprite.getPosition().x + this->enemySprite.getGlobalBounds().width, this->enemySprite.getPosition().y));
                                }
                            }
                        }
                        else if (enemyY > spriteY && enemyY <= spriteH) // 6
                        {
                            if (playerX > enemyX)
                            {
                                this->enemySprite.move(sf::Vector2f(1 * this->moveSpeed, 0));
                            }
                            else
                            {
                                this->enemySprite.move(sf::Vector2f(0, -1 * this->moveSpeed));
                            }
                        }
                        else if (enemyY > spriteH)  // 9
                        {
                            if (playerX > enemyX)
                            {
                                this->enemySprite.move(sf::Vector2f(1 * this->moveSpeed, 0));
                            }
                            else if (playerY > enemyY)
                            {
                                this->enemySprite.move(sf::Vector2f(0, 1 * this->moveSpeed));
                            }
                            else
                            {
                                this->enemySprite.move(sf::Vector2f(0, -1 * this->moveSpeed));
                            }
                        }
                    }
                }
            }

            this->updateTexture(&this->enemyMoveTexture, &this->deltaTimeMove, &this->deltaTimeMaxMove, &this->pauseTimeMove, &this->clipMove, player);
        }
    }
}

void Enemy::attack(Ally* player)
{
    if (this->life > 0)
    {
        if (this->attackAnimation == true)
        {
            this->updateTexture(&this->enemyAttackTexture, &this->deltaTimeAttack, &this->deltaTimeMaxAttack, &this->pauseTimeAttack, &this->clipAttack, player);
        }
    }
}

void Enemy::dead()
{
    if (this->life <= 0 && this->deadAnimation == true)
    {
        this->updateTexture(&this->enemyDeadTexture, &this->deltaTimeDead, &this->deltaTimeMaxDead, &this->pauseTimeDead, &this->clipDead);
    }
}

void Enemy::loadPickedTexture(int enemyType, int enemyID)
{
    // Enemy textures
    std::string path = "assets\\enemy\\enemy0" + std::to_string(enemyType) + std::to_string(enemyID) + "\\";
    for (int i = 0; i < 12; i++)
    {
        if (i < 10)
        {
            std::string run = "running\\running00" + std::to_string(i) + ".png";
            sf::Texture texture;
            texture.loadFromFile(path + run);
            texture.setSmooth(true);
            this->enemyMoveTexture.push_back(texture);

            std::string attack = "attacking\\attacking00" + std::to_string(i) + ".png";
            texture.loadFromFile(path + attack);
            texture.setSmooth(true);
            this->enemyAttackTexture.push_back(texture);

            std::string dead = "dead\\dead00" + std::to_string(i) + ".png";
            texture.loadFromFile(path + dead);
            texture.setSmooth(true);
            this->enemyDeadTexture.push_back(texture);
        }
        else
        {
            std::string run = "running\\running0" + std::to_string(i) + ".png";
            sf::Texture texture;
            texture.loadFromFile(path + run);
            texture.setSmooth(true);
            this->enemyMoveTexture.push_back(texture);

            std::string attack = "attacking\\attacking0" + std::to_string(i) + ".png";
            texture.loadFromFile(path + attack);
            texture.setSmooth(true);
            this->enemyAttackTexture.push_back(texture);

            std::string dead = "dead\\dead0" + std::to_string(i) + ".png";
            texture.loadFromFile(path + dead);
            texture.setSmooth(true);
            this->enemyDeadTexture.push_back(texture);
        }
    }

    // Enemy Sprite
    this->enemySprite.setTexture(this->enemyMoveTexture[0]);
    this->enemySprite.setScale(-0.45, 0.45);
    this->enemySprite.setPosition(sf::Vector2f(0.9 * this->desktopSize.width, 0.45 * this->desktopSize.height));
}

void Enemy::updateTexture(std::vector<sf::Texture>* textureVector, float* deltaTime, const float* deltaTimeMax, float* pauseTime, int* clip, Ally* player)
{
    this->animationInterval();
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
                if (this->type == 0)
                {
                    if (this->power - player->armor > 0)
                    {
                        player->life -= (this->power - player->armor);
                    }
                }
                else if (this->type == 1)
                {
                    if (this->power - player->magicResist > 0)
                    {
                        player->life -= (this->power - player->magicResist);
                    }
                }
            }
            if (&this->clipDead == clip)
            {
                this->deadAnimation = false;
            }
        }
        *deltaTime = 0.0f;

        this->enemySprite.setTexture(textureVector->at(*clip));
    }
}

void Enemy::updateTexture(std::vector<sf::Texture>* textureVector, float* deltaTime, const float* deltaTimeMax, float* pauseTime, int* clip)
{
    this->animationInterval();
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
            if (&this->clipDead == clip)
            {
                this->deadAnimation = false;
                this->endRound = true;
            }
        }
        *deltaTime = 0.0f;

        this->enemySprite.setTexture(textureVector->at(*clip));
    }
}

void Enemy::animationInterval()
{
    float clockLaps = this->clock.restart().asSeconds();
    this->deltaTimeMove += clockLaps;
    this->pauseTimeMove += clockLaps;
    this->deltaTimeAttack += clockLaps;
    this->pauseTimeAttack += clockLaps;
    this->deltaTimeDead += clockLaps;
    this->pauseTimeDead += clockLaps;
}

void Enemy::updateHPText()
{
    this->hpAmountText.setString("HP: " + std::to_string(int(this->life)));
    this->hpAmountText.setPosition(sf::Vector2f(this->enemySprite.getGlobalBounds().left + 85, this->enemySprite.getGlobalBounds().top));
}
