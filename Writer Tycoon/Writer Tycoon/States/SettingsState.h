#pragma once

#include "State.h"

class SettingsState :
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
    SettingsState(sf::RenderWindow* window, 
        std::map<std::string, int>* supportedKeys, 
        std::stack<State*>* states);
    virtual ~SettingsState();

    // Functions
    void updateInput(const float& dt);
    void updateButtons();
    void update(const float& dt);
    void renderButtons(sf::RenderTarget& target);
    void render(sf::RenderTarget* target = nullptr);
};

