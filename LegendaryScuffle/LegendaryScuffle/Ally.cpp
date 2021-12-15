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
        if (positionX1 <= -60)
        {
            goLeft = false;
        }
        if (positionY1 <= -45)
        {
            goUp = false;
        }
        if (positionX2 >= 1980)
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
        if (positionX1 <= -60)
        {
            goLeft = false;
        }
        if (positionY1 <= -45)
        {
            goUp = false;
        }
        if (positionX2 >= 1980)
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
        this->armor = 10.0;
        this->life = 100.0;
        this->magicResist = 10.0;
        this->power = 10.0;
        this->superPower = 1.0;
    }
    else if (pickedCharacter == 1)
    {
        this->armor = 25.0;
        this->life = 1000.0;
        this->magicResist = 25.0;
        this->power = 50.0;
        this->superPower = 1.0;
    }
    else if (pickedCharacter == 2)
    {
        this->armor = 50.0;
        this->life = 5000.0;
        this->magicResist = 50.0;
        this->power = 100.0;
        this->superPower = 1.0;
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
