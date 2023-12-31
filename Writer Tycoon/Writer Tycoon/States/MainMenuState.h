#pragma once

#include "GameState.h"
#include "EditorState.h"
#include "SettingsState.h"

// Forward Declarations
class GameState;
class EditorState;
class SettingsState;

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
    void initGUI();

public:
    // Constructor/Destructor
    MainMenuState(StateData* stateData);
    virtual ~MainMenuState();

    // Functions
    void updateEvents(sf::Event& sfEvent);
    void updateInput(const float& dt);
    void updateGUI(const float& dt);
    void update(const float& dt);
    void renderGUI(sf::RenderTarget& target);
    void render(sf::RenderTarget* target = nullptr);
};

