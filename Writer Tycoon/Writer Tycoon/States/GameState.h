#pragma once

#include "State.h"
#include "SettingsState.h"
#include "../GUI/PauseMenu.h"
#include "../GUI/Popup.h"
#include "../Map/TileMap.h"

// Forward Declarations
class State;
class SettingsState;
class PauseMenu;
class Popup;
class TileMap;

class GameState :
    public State
{
private:
    sf::Font font;
    sf::Texture buttonIdleTexture;
    sf::Texture buttonPressedTexture;
    sf::Texture popupFrameTexture;

    PauseMenu* pauseMenu;
    Popup* popup;

    Player* player;

    TileMap map;

    // Initalizer Functions
    void initTextures();
    void initFonts();
    void initKeybinds();
    void initPauseMenu();
    void initPopups();
    void initGUI();
    void initEntities();

public:
    // Constructor/Destructor
    GameState(StateData* stateData);
    virtual ~GameState();

    // Functions
    void updateEvents(sf::Event& sfEvent);
    void updateInput(const float& dt);
    void updateGUI(const float& dt, const sf::Vector2f& mousePosView);
    void updatePauseMenuButtons();
    void update(const float& dt);
    void render(sf::RenderTarget* target = nullptr);
};

