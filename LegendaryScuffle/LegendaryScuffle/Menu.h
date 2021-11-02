#pragma once

#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>

class Menu
{
public:
    bool isMenuWindowOpen = true;

    // Fonts
    sf::Font menuFont;

    // Buttons
    sf::RectangleShape startGameButton;
    sf::RectangleShape shopButton;
    sf::RectangleShape rulesButton;
    sf::RectangleShape exitButton;
    
    
    Menu();
    void playPauseMusic();
    void animationInterval();
    void updateAnimation(sf::Texture* texture, int* clip, int lastClip, float* deltaTime, const float* deltaTimeMax, float* pauseTime, std::string source);
    void drawMenu(sf::RenderWindow* window);

private:
    const sf::VideoMode desktopSize = sf::VideoMode::getDesktopMode();
    
    // Fonts
    sf::Font titleFont;


    // Texts
    sf::Text gameTitle;
    sf::Text startGameButtonText;
    sf::Text shopButtonText;
    sf::Text rulesButtonText;
    sf::Text exitButtonText;


    // Menu animation
    sf::Clock clock;

    float deltaTime1 = 0.0f;
    float deltaTime2 = 0.0f;
    float pauseTime1 = 2.2f;
    float pauseTime2 = 0.0f;
    const float deltaTimeMax1 = 0.07f;
    const float deltaTimeMax2 = 0.08f;
    int clip1 = 0;
    int clip2 = 0;

    sf::Texture animationTexture1;
    sf::Sprite animationSprite1;

    sf::Texture animationTexture2;
    sf::Sprite animationSprite2;


    // Music
    sf::Music musicTheme;

    sf::Texture soundOnTexture;
    sf::Texture soundOffTexture;
    
    sf::Sprite soundButton;
    
};

