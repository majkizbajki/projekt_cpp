#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include <vector>

void menuUpdateAnimation(sf::Texture* texture, int* clip, int lastClip, float* deltaTime, float* deltaTimeMax, float* pauseTime, std::string source);
void menuMusicPlay(sf::Sprite* button, sf::Texture* on, sf::Texture* off, sf::Music* music);
void openRules(sf::RectangleShape* button, sf::Sprite* mainWindowButton, std::vector <sf::Text>* rulesControlsAssets, sf::RenderWindow* window, bool* isMenuWindowOpen);
void closeRules(sf::Sprite* button, bool* isMenuWindowOpen);

int main()
{
    const sf::VideoMode desktopSize = sf::VideoMode::getDesktopMode();

    sf::RenderWindow window(sf::VideoMode(desktopSize.width, 0.96*desktopSize.height), "SFML works!", sf::Style::Fullscreen);
    window.setFramerateLimit(60);

    // Fonts
    
    sf::Font menuFont;
    menuFont.loadFromFile("assets/fonts/LuckiestGuy-Regular.ttf");

    sf::Font titleFont;
    titleFont.loadFromFile("assets/fonts/FredokaOne-Regular.ttf");

    // Game title

    sf::Text gameTitle("LEGENDARY SCUFFLE", titleFont);
    gameTitle.setCharacterSize(94);
    gameTitle.setFillColor(sf::Color(254, 250, 224));
    gameTitle.setPosition(sf::Vector2f(0.25 * desktopSize.width, 0.1 * desktopSize.height));

    // startGameButton with text

    sf::RectangleShape startGameButton;
    startGameButton.setSize(sf::Vector2f(desktopSize.width*0.3, desktopSize.height*0.08));
    startGameButton.setFillColor(sf::Color(221, 161, 94));
    startGameButton.setPosition(sf::Vector2f(0.55*desktopSize.width, 0.3*desktopSize.height));

    sf::Text startGameText("START GAME",menuFont);
    startGameText.setCharacterSize(40);
    startGameText.setFillColor(sf::Color(40, 54, 24));
    startGameText.setPosition(sf::Vector2f(0.55 * desktopSize.width + startGameButton.getSize().x/2 - startGameText.getGlobalBounds().width/2, 0.3 * desktopSize.height + startGameText.getCharacterSize()/2));

    // openShopButton with text

    sf::RectangleShape openShopButton;
    openShopButton.setSize(sf::Vector2f(desktopSize.width * 0.3, desktopSize.height * 0.08));
    openShopButton.setFillColor(sf::Color(221, 161, 94));
    openShopButton.setPosition(sf::Vector2f(0.55 * desktopSize.width, 0.42 * desktopSize.height));

    sf::Text openShopText("SHOP", menuFont);
    openShopText.setCharacterSize(40);
    openShopText.setFillColor(sf::Color(40, 54, 24));
    openShopText.setPosition(sf::Vector2f(0.55 * desktopSize.width + openShopButton.getSize().x / 2 - openShopText.getGlobalBounds().width / 2, 0.42 * desktopSize.height + openShopText.getCharacterSize() / 2));

    // openRulesButton with text

    sf::RectangleShape openRulesButton;
    openRulesButton.setSize(sf::Vector2f(desktopSize.width * 0.3, desktopSize.height * 0.08));
    openRulesButton.setFillColor(sf::Color(221, 161, 94));
    openRulesButton.setPosition(sf::Vector2f(0.15 * desktopSize.width, 0.65 * desktopSize.height));

    sf::Text openRulesText("RULES / CONTROLS", menuFont);
    openRulesText.setCharacterSize(40);
    openRulesText.setFillColor(sf::Color(40, 54, 24));
    openRulesText.setPosition(sf::Vector2f(0.15 * desktopSize.width + openRulesButton.getSize().x / 2 - openRulesText.getGlobalBounds().width / 2, 0.65 * desktopSize.height + openShopText.getCharacterSize() / 2));

    // exitButton with text

    sf::RectangleShape exitButton;
    exitButton.setSize(sf::Vector2f(desktopSize.width * 0.3, desktopSize.height * 0.08));
    exitButton.setFillColor(sf::Color(221, 161, 94));
    exitButton.setPosition(sf::Vector2f(0.15 * desktopSize.width, 0.77 * desktopSize.height));

    sf::Text exitText("EXIT", menuFont);
    exitText.setCharacterSize(40);
    exitText.setFillColor(sf::Color(40, 54, 24));
    exitText.setPosition(sf::Vector2f(0.15 * desktopSize.width + exitButton.getSize().x / 2 - exitText.getGlobalBounds().width / 2, 0.77 * desktopSize.height + openShopText.getCharacterSize() / 2));

    // Menu animation

    sf::Clock clock;
    float clockLaps;

    float deltaTime1 = 0.0f;
    float deltaTime2 = 0.0f;
    float pauseTime1 = 2.2f;
    float pauseTime2 = 0.0f;
    float maxDelta1 = 0.07f;
    float maxDelta2 = 0.08f;
    int clip1 = 0;
    int clip2 = 0;

    sf::Texture menuAnimationTexture1;
    menuAnimationTexture1.loadFromFile("assets/player/player01/slashing/slashing000.png");
    menuAnimationTexture1.setSmooth(true);

    sf::Sprite menuAnimationSprite1;
    menuAnimationSprite1.setTexture(menuAnimationTexture1);
    menuAnimationSprite1.setPosition(sf::Vector2f(0.2 * desktopSize.width, 0.2 * desktopSize.height));
    menuAnimationSprite1.setScale(0.5, 0.5);

    sf::Texture menuAnimationTexture2;
    menuAnimationTexture2.loadFromFile("assets/player/player02/running/running000.png");
    menuAnimationTexture2.setSmooth(true);

    sf::Sprite menuAnimationSprite2;
    menuAnimationSprite2.setTexture(menuAnimationTexture2);
    menuAnimationSprite2.setPosition(sf::Vector2f(0.8 * desktopSize.width, 0.5 * desktopSize.height));
    menuAnimationSprite2.setScale(-0.5, 0.5);

    // Music theme

    bool isMusicOn = true;

    sf::Music musicTheme;
    if (!musicTheme.openFromFile("assets/music/menu/musicTheme.wav"))
        return -1;
    if (isMusicOn)
    {
        musicTheme.play();
    }
    else
    {
        musicTheme.pause();
    }
    musicTheme.setLoop(true);

    // Music ON/OFF button

    bool isMusicClickable = true;

    sf::Texture menuSoundOnTexture;
    menuSoundOnTexture.loadFromFile("assets/music/icon/sound-on.png");
    menuSoundOnTexture.setSmooth(true);

    sf::Texture menuSoundOffTexture;
    menuSoundOffTexture.loadFromFile("assets/music/icon/no-sound.png");
    menuSoundOffTexture.setSmooth(true);
    
    sf::Sprite menuSoundOnButton;
    menuSoundOnButton.setTexture(menuSoundOnTexture);
    menuSoundOnButton.setPosition(sf::Vector2f(0.9 * desktopSize.width, 0.05 * desktopSize.height));

    // isMenuWindowOpen

    bool isMenuWindowOpen = true;

    // Back to menu button

    sf::Texture LeftArrow;
    LeftArrow.loadFromFile("assets/left-arrow.png");
    LeftArrow.setSmooth(true);

    sf::Sprite LeftArrowButton;
    LeftArrowButton.setTexture(LeftArrow);
    LeftArrowButton.setPosition(sf::Vector2f(0.05 * desktopSize.width, 0.05 * desktopSize.height));

    // Rules text

    sf::Text rulesText("RULES", menuFont);
    rulesText.setCharacterSize(50);
    rulesText.setFillColor(sf::Color(254, 250, 224));
    rulesText.setPosition(sf::Vector2f(0.25 * desktopSize.width, 0.2 * desktopSize.height));

    sf::Text rulesDescriptionText("The main goal of the game is to survive as many\n rounds as possible fighting against the enemies.\n During the game you can get money and bonuses\n that you can spend on character upgrades and\n become even stronger. The game ends when\n all your life is lost and you start over.", menuFont);
    rulesDescriptionText.setCharacterSize(30);
    rulesDescriptionText.setFillColor(sf::Color(254, 250, 224));
    rulesDescriptionText.setPosition(sf::Vector2f(0.1 * desktopSize.width, 0.3 * desktopSize.height));

    // Controls text

    sf::Text controlsText("CONTROLS", menuFont);
    controlsText.setCharacterSize(50);
    controlsText.setFillColor(sf::Color(254, 250, 224));
    controlsText.setPosition(sf::Vector2f(0.7 * desktopSize.width, 0.2 * desktopSize.height));

    sf::Text wasdText("W,A,S,D - moving",menuFont);
    wasdText.setCharacterSize(30);
    wasdText.setFillColor(sf::Color(254, 250, 224));
    wasdText.setPosition(sf::Vector2f(0.6 * desktopSize.width, 0.3 * desktopSize.height));

    sf::Text spaceText("Space - shooting/atacking", menuFont);
    spaceText.setCharacterSize(30);
    spaceText.setFillColor(sf::Color(254, 250, 224));
    spaceText.setPosition(sf::Vector2f(0.6 * desktopSize.width, 0.4 * desktopSize.height));

    sf::Text superPowerText("R - using super power", menuFont);
    superPowerText.setCharacterSize(30);
    superPowerText.setFillColor(sf::Color(254, 250, 224));
    superPowerText.setPosition(sf::Vector2f(0.6 * desktopSize.width, 0.5 * desktopSize.height));

    // Rules / controls sf::text vector

    std::vector <sf::Text> rulesControlsAssets;
    rulesControlsAssets.push_back(rulesText);
    rulesControlsAssets.push_back(rulesDescriptionText);
    rulesControlsAssets.push_back(controlsText);
    rulesControlsAssets.push_back(wasdText);
    rulesControlsAssets.push_back(spaceText);
    rulesControlsAssets.push_back(superPowerText);

    while (window.isOpen())
    {
        clockLaps = clock.restart().asSeconds();
        deltaTime1 += clockLaps;
        deltaTime2 += clockLaps;
        pauseTime1 += clockLaps;
        pauseTime2 += clockLaps;

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                window.close();
            else if (event.type == sf::Event::MouseButtonReleased)
            {
                if (isMenuWindowOpen)
                {
                    menuMusicPlay(&menuSoundOnButton, &menuSoundOnTexture, &menuSoundOffTexture, &musicTheme);
                    openRules(&openRulesButton, &LeftArrowButton, &rulesControlsAssets, &window, &isMenuWindowOpen);
                }
                else
                {
                    closeRules(&LeftArrowButton, &isMenuWindowOpen);
                }
            }
        }

        if (isMenuWindowOpen)
        {
            window.clear(sf::Color(96, 108, 56));

            window.draw(gameTitle);
            window.draw(startGameButton);
            window.draw(startGameText);
            window.draw(openShopButton);
            window.draw(openShopText);
            window.draw(openRulesButton);
            window.draw(openRulesText);
            window.draw(exitButton);
            window.draw(exitText);
            window.draw(menuSoundOnButton);
            if (pauseTime1 >= 3.0f)
            {
                menuUpdateAnimation(&menuAnimationTexture1, &clip1, 11, &deltaTime1, &maxDelta1, &pauseTime1, "assets/player/player01/slashing/slashing");
            }
            menuUpdateAnimation(&menuAnimationTexture2, &clip2, 11, &deltaTime2, &maxDelta2, &pauseTime2, "assets/player/player02/running/running");
            window.draw(menuAnimationSprite1);
            window.draw(menuAnimationSprite2);

            window.display();
        }
    }

    return 0;
}

void menuUpdateAnimation(sf::Texture* texture, int * clip, int lastClip, float * deltaTime, float * deltaTimeMax, float * pauseTime, std::string source)
{
    std::string png = ".png";

    std::string c = "000";
    if (*deltaTime >= *deltaTimeMax)
    {
        if (*clip > 9)
        {
            c = "0";
            c.append(std::to_string(*clip));
        }
        else if (*clip > 99)
        {
            c = std::to_string(*clip);
        }
        else
        {
            c = "00";
            c.append(std::to_string(*clip));
        }

        if (*clip < lastClip)
        {
            *clip += 1;
        }
        else
        {
            *pauseTime = 0.0f;
            *clip = 0;
        }
        *deltaTime = 0.0f;

        source.append(c);
        source.append(png);

        texture->loadFromFile(source);
    }
}

void menuMusicPlay(sf::Sprite* button, sf::Texture* on, sf::Texture* off, sf::Music* music)
{
    float buttonX = button->getPosition().x;
    float buttonY = button->getPosition().y;
    float buttonWidth = button->getGlobalBounds().width;
    float buttonHeight = button->getGlobalBounds().height;
        
    float mousePositionX = sf::Mouse::getPosition().x;
    float mousePositionY = sf::Mouse::getPosition().y;

    if (mousePositionX >= buttonX && mousePositionX <= (buttonX+buttonWidth) && mousePositionY >= buttonY && mousePositionY <= (buttonY+buttonHeight))
    {
        if (button->getTexture() == on)
        {
            button->setTexture(*off);
            music->pause();
        }
        else
        {
            button->setTexture(*on);
            music->play();
        }
            
    }
}

void openRules(sf::RectangleShape* button, sf::Sprite* mainWindowButton, std::vector <sf::Text>* rulesControlsAssets, sf::RenderWindow* window, bool* isMenuWindowOpen)
{
    float buttonX = button->getPosition().x;
    float buttonY = button->getPosition().y;
    float buttonWidth = button->getGlobalBounds().width;
    float buttonHeight = button->getGlobalBounds().height;

    float mousePositionX = sf::Mouse::getPosition().x;
    float mousePositionY = sf::Mouse::getPosition().y;

    if (mousePositionX >= buttonX && mousePositionX <= (buttonX + buttonWidth) && mousePositionY >= buttonY && mousePositionY <= (buttonY + buttonHeight))
    {
        *isMenuWindowOpen = false;

        window->clear(sf::Color(96, 108, 56));
        window->draw(*mainWindowButton);
        for (int i = 0; i < rulesControlsAssets->size(); i++)
        {
            window->draw(rulesControlsAssets->at(i));
        }
        window->display();
    }
}

void closeRules(sf::Sprite* button, bool* isMenuWindowOpen)
{
    float buttonX = button->getPosition().x;
    float buttonY = button->getPosition().y;
    float buttonWidth = button->getGlobalBounds().width;
    float buttonHeight = button->getGlobalBounds().height;

    float mousePositionX = sf::Mouse::getPosition().x;
    float mousePositionY = sf::Mouse::getPosition().y;

    if (mousePositionX >= buttonX && mousePositionX <= (buttonX + buttonWidth) && mousePositionY >= buttonY && mousePositionY <= (buttonY + buttonHeight))
    {
        *isMenuWindowOpen = true;
    }
}