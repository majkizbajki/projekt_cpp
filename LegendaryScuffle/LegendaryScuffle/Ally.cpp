#include "Ally.h"
#include "Enemy.h"

sf::Sprite Ally::getSprite()
{
	return this->shopSprite;
}

void Ally::move(std::vector<sf::Sprite>* mapSprites)
{
    if (this->life > 0)
    {
        float positionX1 = this->playerSprite.getGlobalBounds().left;
        float positionY1 = this->playerSprite.getGlobalBounds().top;
        float positionX2 = this->playerSprite.getGlobalBounds().left + this->playerSprite.getGlobalBounds().width;
        float positionY2 = this->playerSprite.getGlobalBounds().top + this->playerSprite.getGlobalBounds().height;
        bool goUp = true;
        bool goDown = true;
        bool goLeft = true;
        bool goRight = true;
        if (positionX1 <= -30)
        {
            goLeft = false;
        }
        if (positionY1 <= 30)
        {
            goUp = false;
        }
        if (positionX2 >= 1940)
        {
            goRight = false;
        }
        if (positionY2 >= 1080)
        {
            goDown = false;
        }

        for (int i = 0; i < mapSprites->size(); i++)
        {
            if (Collision::PixelPerfectTest(this->playerSprite, mapSprites->at(i)))
            {
                if (this->playerSprite.getGlobalBounds().left < mapSprites->at(i).getGlobalBounds().left)
                {
                    goRight = false;
                }
                if (this->playerSprite.getGlobalBounds().left > mapSprites->at(i).getGlobalBounds().left)
                {
                    goLeft = false;
                }
                if (this->playerSprite.getGlobalBounds().top < mapSprites->at(i).getGlobalBounds().top)
                {
                    goDown = false;
                }
                if (this->playerSprite.getGlobalBounds().top > mapSprites->at(i).getGlobalBounds().top)
                {
                    goUp = false;
                }
            }
        }

        if (this->attackAnimation == false)
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && goUp)
            {
                this->playerSprite.move(sf::Vector2f(0, -3));
                this->updatePlayerTexture(&this->playerMoveTexture, &this->deltaTimeMove, &this->deltaTimeMaxMove, &this->pauseTimeMove, &this->clipMove);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && goLeft)
            {
                if (this->playerSprite.getScale().x > 0)
                {
                    this->playerSprite.setPosition(sf::Vector2f(this->playerSprite.getPosition().x + this->playerSprite.getGlobalBounds().width, this->playerSprite.getPosition().y));
                }
                this->playerSprite.move(sf::Vector2f(-3, 0));
                this->updatePlayerTexture(&this->playerMoveTexture, &this->deltaTimeMove, &this->deltaTimeMaxMove, &this->pauseTimeMove, &this->clipMove);
                this->playerSprite.setScale(-0.25, 0.25);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && goDown)
            {
                this->playerSprite.move(sf::Vector2f(0, 3));
                this->updatePlayerTexture(&this->playerMoveTexture, &this->deltaTimeMove, &this->deltaTimeMaxMove, &this->pauseTimeMove, &this->clipMove);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && goRight)
            {
                if (this->playerSprite.getScale().x < 0)
                {
                    this->playerSprite.setPosition(sf::Vector2f(this->playerSprite.getPosition().x - this->playerSprite.getGlobalBounds().width, this->playerSprite.getPosition().y));
                }
                this->playerSprite.move(sf::Vector2f(3, 0));
                this->updatePlayerTexture(&this->playerMoveTexture, &this->deltaTimeMove, &this->deltaTimeMaxMove, &this->pauseTimeMove, &this->clipMove);
                this->playerSprite.setScale(0.25, 0.25);
            }
        }
    }
}

void Ally::attack(std::vector<Enemy>* enemyVector, std::vector<sf::Sprite>* mapSprites)
{
    if (this->life > 0)
    {
        float positionX1 = this->playerSprite.getGlobalBounds().left;
        float positionY1 = this->playerSprite.getGlobalBounds().top;
        float positionX2 = this->playerSprite.getGlobalBounds().left + this->playerSprite.getGlobalBounds().width;
        float positionY2 = this->playerSprite.getGlobalBounds().top + this->playerSprite.getGlobalBounds().height;
        bool goUp = true;
        bool goDown = true;
        bool goLeft = true;
        bool goRight = true;
        if (positionX1 <= -30)
        {
            goLeft = false;
        }
        if (positionY1 <= 30)
        {
            goUp = false;
        }
        if (positionX2 >= 1940)
        {
            goRight = false;
        }
        if (positionY2 >= 1080)
        {
            goDown = false;
        }

        for (int i = 0; i < mapSprites->size(); i++)
        {
            if (Collision::PixelPerfectTest(this->playerSprite, mapSprites->at(i)))
            {
                if (this->playerSprite.getGlobalBounds().left < mapSprites->at(i).getGlobalBounds().left)
                {
                    goRight = false;
                }
                if (this->playerSprite.getGlobalBounds().left > mapSprites->at(i).getGlobalBounds().left)
                {
                    goLeft = false;
                }
                if (this->playerSprite.getGlobalBounds().top < mapSprites->at(i).getGlobalBounds().top)
                {
                    goDown = false;
                }
                if (this->playerSprite.getGlobalBounds().top > mapSprites->at(i).getGlobalBounds().top)
                {
                    goUp = false;
                }
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && this->attackAnimation == true && goUp)
        {
            this->playerSprite.move(sf::Vector2f(0, -3));
            this->updatePlayerTexture(&this->playerDynamicAttackTexture, &this->deltaTimeAttack, &this->deltaTimeMaxAttack, &this->pauseTimeAttack, &this->clipAttack, enemyVector);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && this->attackAnimation == true && goLeft)
        {
            this->playerSprite.move(sf::Vector2f(-3, 0));
            this->updatePlayerTexture(&this->playerDynamicAttackTexture, &this->deltaTimeAttack, &this->deltaTimeMaxAttack, &this->pauseTimeAttack, &this->clipAttack, enemyVector);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && this->attackAnimation == true && goDown)
        {
            this->playerSprite.move(sf::Vector2f(0, 3));
            this->updatePlayerTexture(&this->playerDynamicAttackTexture, &this->deltaTimeAttack, &this->deltaTimeMaxAttack, &this->pauseTimeAttack, &this->clipAttack, enemyVector);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && this->attackAnimation == true && goRight)
        {
            this->playerSprite.move(sf::Vector2f(3, 0));
            this->updatePlayerTexture(&this->playerDynamicAttackTexture, &this->deltaTimeAttack, &this->deltaTimeMaxAttack, &this->pauseTimeAttack, &this->clipAttack, enemyVector);
        }
        else if (this->attackAnimation == true)
        {
            this->updatePlayerTexture(&this->playerStaticAttackTexture, &this->deltaTimeAttack, &this->deltaTimeMaxAttack, &this->pauseTimeAttack, &this->clipAttack, enemyVector);
        }
    }
}

void Ally::dead()
{
    if (this->life <= 0 && this->deadAnimation == true)
    {
        this->updatePlayerTexture(&this->playerDeadTexture, &this->deltaTimeDead, &this->deltaTimeMaxDead, &this->pauseTimeDead, &this->clipDead);
    }
}

void Ally::setStatistics(int pickedCharacter)
{
    if (pickedCharacter == 0)
    {
        // LIFE
        switch (this->lifeLevel)
        {
        case 1:
            this->life = 100;
            break;
        case 2:
            this->life = 250;
            break;
        case 3:
            this->life = 500;
            break;
        case 4:
            this->life = 750;
            break;
        case 5:
            this->life = 1000;
            break;
        case 6:
            this->life = 1250;
            break;
        case 7:
            this->life = 1500;
            break;
        case 8:
            this->life = 2500;
            break;
        case 9:
            this->life = 5000;
            break;
        case 10:
            this->life = 7500;
            break;
        default:
            this->life = 100;
            break;
        }

        // POWER
        switch (this->powerLevel)
        {
        case 1:
            this->power = 10;
            break;
        case 2:
            this->power = 20;
            break;
        case 3:
            this->power = 30;
            break;
        case 4:
            this->power = 40;
            break;
        case 5:
            this->power = 50;
            break;
        case 6:
            this->power = 60;
            break;
        case 7:
            this->power = 70;
            break;
        case 8:
            this->power = 80;
            break;
        case 9:
            this->power = 90;
            break;
        case 10:
            this->power = 100;
            break;
        default:
            this->power = 10;
            break;
        }

        // ARMOR
        switch (this->armorLevel)
        {
        case 1:
            this->armor = 15;
            break;
        case 2:
            this->armor = 20;
            break;
        case 3:
            this->armor = 25;
            break;
        case 4:
            this->armor = 30;
            break;
        case 5:
            this->armor = 35;
            break;
        case 6:
            this->armor = 40;
            break;
        case 7:
            this->armor = 45;
            break;
        case 8:
            this->armor = 50;
            break;
        case 9:
            this->armor = 75;
            break;
        case 10:
            this->armor = 100;
            break;
        default:
            this->armor = 15;
            break;
        }

        // MAGIC RESIST
        switch (this->magicResistLevel)
        {
        case 1:
            this->magicResist = 15;
            break;
        case 2:
            this->magicResist = 20;
            break;
        case 3:
            this->magicResist = 25;
            break;
        case 4:
            this->magicResist = 30;
            break;
        case 5:
            this->magicResist = 35;
            break;
        case 6:
            this->magicResist = 40;
            break;
        case 7:
            this->magicResist = 45;
            break;
        case 8:
            this->magicResist = 50;
            break;
        case 9:
            this->magicResist = 75;
            break;
        case 10:
            this->magicResist = 100;
            break;
        default:
            this->magicResist = 15;
            break;
        }

        // SUPER POWER
        switch (this->superPowerLevel)
        {
        case 1:
            this->superPower = 1;
            break;
        case 2:
            this->superPower = 1.5;
            break;
        case 3:
            this->superPower = 2;
            break;
        case 4:
            this->superPower = 2.5;
            break;
        case 5:
            this->superPower = 3;
            break;
        case 6:
            this->superPower = 3.5;
            break;
        case 7:
            this->superPower = 4;
            break;
        case 8:
            this->superPower = 4.5;
            break;
        case 9:
            this->superPower = 5;
            break;
        case 10:
            this->superPower = 5.5;
            break;
        default:
            this->superPower = 1;
            break;
        }
    }
    else if (pickedCharacter == 1)
    {
    // LIFE
    switch (this->lifeLevel)
    {
    case 1:
        this->life = 1000;
        break;
    case 2:
        this->life = 2500;
        break;
    case 3:
        this->life = 5000;
        break;
    case 4:
        this->life = 7500;
        break;
    case 5:
        this->life = 10000;
        break;
    case 6:
        this->life = 12000;
        break;
    case 7:
        this->life = 14000;
        break;
    case 8:
        this->life = 16000;
        break;
    case 9:
        this->life = 18000;
        break;
    case 10:
        this->life = 20000;
        break;
    default:
        this->life = 1000;
        break;
    }

    // POWER
    switch (this->powerLevel)
    {
    case 1:
        this->power = 50;
        break;
    case 2:
        this->power = 75;
        break;
    case 3:
        this->power = 100;
        break;
    case 4:
        this->power = 125;
        break;
    case 5:
        this->power = 150;
        break;
    case 6:
        this->power = 175;
        break;
    case 7:
        this->power = 200;
        break;
    case 8:
        this->power = 250;
        break;
    case 9:
        this->power = 300;
        break;
    case 10:
        this->power = 350;
        break;
    default:
        this->power = 50;
        break;
    }

    // ARMOR
    switch (this->armorLevel)
    {
    case 1:
        this->armor = 25;
        break;
    case 2:
        this->armor = 35;
        break;
    case 3:
        this->armor = 45;
        break;
    case 4:
        this->armor = 55;
        break;
    case 5:
        this->armor = 65;
        break;
    case 6:
        this->armor = 75;
        break;
    case 7:
        this->armor = 100;
        break;
    case 8:
        this->armor = 125;
        break;
    case 9:
        this->armor = 150;
        break;
    case 10:
        this->armor = 200;
        break;
    default:
        this->armor = 25;
        break;
    }

    // MAGIC RESIST
    switch (this->magicResistLevel)
    {
    case 1:
        this->magicResist = 25;
        break;
    case 2:
        this->magicResist = 35;
        break;
    case 3:
        this->magicResist = 45;
        break;
    case 4:
        this->magicResist = 55;
        break;
    case 5:
        this->magicResist = 65;
        break;
    case 6:
        this->magicResist = 75;
        break;
    case 7:
        this->magicResist = 100;
        break;
    case 8:
        this->magicResist = 125;
        break;
    case 9:
        this->magicResist = 150;
        break;
    case 10:
        this->magicResist = 200;
        break;
    default:
        this->magicResist = 50;
        break;
    }

    // SUPER POWER
    switch (this->superPowerLevel)
    {
    case 1:
        this->superPower = 1;
        break;
    case 2:
        this->superPower = 1.5;
        break;
    case 3:
        this->superPower = 2;
        break;
    case 4:
        this->superPower = 2.5;
        break;
    case 5:
        this->superPower = 3;
        break;
    case 6:
        this->superPower = 3.5;
        break;
    case 7:
        this->superPower = 4;
        break;
    case 8:
        this->superPower = 4.5;
        break;
    case 9:
        this->superPower = 5;
        break;
    case 10:
        this->superPower = 5.5;
        break;
    default:
        this->superPower = 1;
        break;
    }
    }
    else if (pickedCharacter == 2)
    {
    // LIFE
    switch (this->lifeLevel)
    {
    case 1:
        this->life = 5000;
        break;
    case 2:
        this->life = 10000;
        break;
    case 3:
        this->life = 15000;
        break;
    case 4:
        this->life = 20000;
        break;
    case 5:
        this->life = 25000;
        break;
    case 6:
        this->life = 27500;
        break;
    case 7:
        this->life = 30000;
        break;
    case 8:
        this->life = 32500;
        break;
    case 9:
        this->life = 35000;
        break;
    case 10:
        this->life = 37500;
        break;
    default:
        this->life = 5000;
        break;
    }

    // POWER
    switch (this->powerLevel)
    {
    case 1:
        this->power = 100;
        break;
    case 2:
        this->power = 200;
        break;
    case 3:
        this->power = 300;
        break;
    case 4:
        this->power = 400;
        break;
    case 5:
        this->power = 500;
        break;
    case 6:
        this->power = 600;
        break;
    case 7:
        this->power = 700;
        break;
    case 8:
        this->power = 800;
        break;
    case 9:
        this->power = 900;
        break;
    case 10:
        this->power = 1000;
        break;
    default:
        this->power = 100;
        break;
    }

    // ARMOR
    switch (this->armorLevel)
    {
    case 1:
        this->armor = 50;
        break;
    case 2:
        this->armor = 100;
        break;
    case 3:
        this->armor = 150;
        break;
    case 4:
        this->armor = 200;
        break;
    case 5:
        this->armor = 250;
        break;
    case 6:
        this->armor = 300;
        break;
    case 7:
        this->armor = 350;
        break;
    case 8:
        this->armor = 400;
        break;
    case 9:
        this->armor = 450;
        break;
    case 10:
        this->armor = 500;
        break;
    default:
        this->armor = 50;
        break;
    }

    // MAGIC RESIST
    switch (this->magicResistLevel)
    {
    case 1:
        this->magicResist = 50;
        break;
    case 2:
        this->magicResist = 100;
        break;
    case 3:
        this->magicResist = 150;
        break;
    case 4:
        this->magicResist = 200;
        break;
    case 5:
        this->magicResist = 250;
        break;
    case 6:
        this->magicResist = 300;
        break;
    case 7:
        this->magicResist = 350;
        break;
    case 8:
        this->magicResist = 400;
        break;
    case 9:
        this->magicResist = 450;
        break;
    case 10:
        this->magicResist = 500;
        break;
    default:
        this->magicResist = 50;
        break;
    }

    // SUPER POWER
    switch (this->superPowerLevel)
    {
    case 1:
        this->superPower = 1;
        break;
    case 2:
        this->superPower = 1.5;
        break;
    case 3:
        this->superPower = 2;
        break;
    case 4:
        this->superPower = 2.5;
        break;
    case 5:
        this->superPower = 3;
        break;
    case 6:
        this->superPower = 3.5;
        break;
    case 7:
        this->superPower = 4;
        break;
    case 8:
        this->superPower = 4.5;
        break;
    case 9:
        this->superPower = 5;
        break;
    case 10:
        this->superPower = 5.5;
        break;
    default:
        this->superPower = 1;
        break;
    }
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

void Ally::updatePlayerTexture(std::vector<sf::Texture>* textureVector, float* deltaTime, const float* deltaTimeMax, float* pauseTime, int* clip, std::vector<Enemy>* enemyVector)
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
                for (int i = 0; i < enemyVector->size(); i++)
                {
                    if (Collision::PixelPerfectTest(this->playerSprite, enemyVector->at(i).enemySprite))
                    {
                        enemyVector->at(i).life -= this->power;
                    }
                }
            }
            if (&this->clipDead == clip)
            {
                this->deadAnimation = false;
                this->endGame = true;
            }
        }
        *deltaTime = 0.0f;

        this->playerSprite.setTexture(textureVector->at(*clip));
    }
}

void Ally::updatePlayerTexture(std::vector<sf::Texture>* textureVector, float* deltaTime, const float* deltaTimeMax, float* pauseTime, int* clip)
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
            }
            if (&this->clipDead == clip)
            {
                this->deadAnimation = false;
                this->endGame = true;
            }
        }
        *deltaTime = 0.0f;

        this->playerSprite.setTexture(textureVector->at(*clip));
    }
}

void Ally::animationInterval()
{
    float clockLaps = this->clock.restart().asSeconds();
    this->deltaTimeMove += clockLaps;
    this->pauseTimeMove += clockLaps;
    this->deltaTimeAttack += clockLaps;
    this->pauseTimeAttack += clockLaps;
    this->deltaTimeDead += clockLaps;
    this->pauseTimeDead += clockLaps;
}

Ally::~Ally()
{
}

void Ally::updateHPText()
{
    this->hpAmountText.setString("HP: " + std::to_string(int(this->life)));
    this->hpAmountText.setPosition(sf::Vector2f(this->playerSprite.getGlobalBounds().left + 75, this->playerSprite.getGlobalBounds().top + 15));
}
