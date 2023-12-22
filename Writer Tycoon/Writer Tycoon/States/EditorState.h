#pragma once

#include "State.h"
#include "SettingsState.h"
#include "../GUI/PauseMenu.h"
#include "../Map/TileMap.h"

// Forward Declarations
class State;
class SettingsState;
class PauseMenu;
class TileMap;

class EditorState :
    public State
{
private:
    // Variables
    sf::Font font;

    sf::Texture buttonIdleTexture;
    sf::Texture buttonPressedTexture;
    std::map<std::string, Button*> buttons;

    PauseMenu* pauseMenu;

    TileMap map;

    // Functions
    void initVariables();
    void initBackground();
    void initTextures();
    void initFonts();
    void initKeybinds();
    void initPauseMenu();
    void initGUI();

public:
    // Constructor/Destructor
    EditorState(StateData* stateData);
    virtual ~EditorState();

    // Functions
    void updateEvents(sf::Event& sfEvent);
    void updateInput(const float& dt);
    void updateGUI();
    void updatePauseMenuButtons();
    void update(const float& dt);
    void renderGUI(sf::RenderTarget& target);
    void render(sf::RenderTarget* target = nullptr);
};