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
    sf::View view;
    sf::RenderTexture renderTexture;
    sf::Sprite renderSprite;

    sf::Font font;
    sf::Texture buttonIdleTexture;
    sf::Texture buttonPressedTexture;
    sf::Texture popupFrameTexture;

    PauseMenu* pauseMenu;
    Popup* popup;

    Player* player;

    TileMap* tileMap;

    // Initalizer Functions
    void initView();
    void initDeferredRender();
    void initTextures();
    void initFonts();
    void initKeybinds();
    void initPauseMenu();
    void initPopups();
    void initGUI();
    void initEntities();
    void initTileMap();

public:
    // Constructor/Destructor
    GameState(StateData* stateData);
    virtual ~GameState();

    // Functions
    void updateView(const float& dt);
    void updateEvents(sf::Event& sfEvent);
    void updateInput(const float& dt);
    void updateGUI(const float& dt);
    void updatePauseMenuButtons();
    void update(const float& dt);
    void render(sf::RenderTarget* target = nullptr);
};

