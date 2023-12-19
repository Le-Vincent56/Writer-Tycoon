#pragma once

#include "GameState.h"
#include "../Resources/Button.h"

class MainMenuState :
    public State
{
private:
    // Variables
    sf::Texture backgroundTexture;
    sf::RectangleShape background;
    sf::Font font;

    sf::Texture buttonIdle;
    sf::Texture buttonPressed;

    std::map<std::string, Button*> buttons;

    // Functions
    void initVariables();
    void initBackground();
    void initTextures();
    void initFonts();
    void initKeybinds();
    void initButtons();

public:
    // Constructor/Destructor
    MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
    virtual ~MainMenuState();

    // Functions
    void updateInput(const float& dt);
    void updateButtons();
    void update(const float& dt);
    void renderButtons(sf::RenderTarget* target = nullptr);
    void render(sf::RenderTarget* target = nullptr);
};

