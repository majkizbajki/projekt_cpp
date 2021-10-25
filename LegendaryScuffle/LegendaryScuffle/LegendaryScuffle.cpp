#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>

void menuUpdateAnimation(sf::Texture* texture, int* clip, int lastClip, float* deltaTime, float* deltaTimeMax, float* pauseTime, std::string source);

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
        }

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
        if (pauseTime1 >= 3.0f)
        {
            menuUpdateAnimation(&menuAnimationTexture1, &clip1, 11, &deltaTime1, &maxDelta1, &pauseTime1, "assets/player/player01/slashing/slashing");
        }
        menuUpdateAnimation(&menuAnimationTexture2, &clip2, 11, &deltaTime2, &maxDelta2, &pauseTime2, "assets/player/player02/running/running");
        window.draw(menuAnimationSprite1);
        window.draw(menuAnimationSprite2);

        window.display();
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