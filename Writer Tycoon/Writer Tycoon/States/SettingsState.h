#pragma once

#include "State.h"
#include "..\GUI\Dropdown.h"

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
    sf::Texture dropdownIdle;
    sf::Texture dropdownActive;

    std::map<std::string, Button*> buttons;
    std::map<std::string, Dropdown*> dropdowns;

    sf::Text optionsText;

    std::vector<sf::VideoMode> modes;

    bool changesMade;

    // Functions
    void initVariables();
    void initBackground();
    void initTextures();
    void initFonts();
    void initKeybinds();
    void initGUI();
    void initText(const float& dropdownCenterX, const float& dropdownWidth,
        const float& dropdownCenterY);

public:
    // Constructor/Destructor
    SettingsState(sf::RenderWindow* window, 
        std::map<std::string, int>* supportedKeys, 
        std::stack<State*>* states);
    virtual ~SettingsState();

    // Functions
    void updateEvents(sf::Event& sfEvent);
    void updateInput(const float& dt);
    void updateGUI(const float& dt);
    void update(const float& dt);
    void renderGUI(sf::RenderTarget& target);
    void render(sf::RenderTarget* target = nullptr);
};

