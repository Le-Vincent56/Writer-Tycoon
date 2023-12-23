#pragma once

#include "State.h"
#include "SettingsState.h"
#include "../GUI/PauseMenu.h"
#include "../Map/TileMap.h"
#include "../Map/Tiles/Tile.h"
#include "../GUI/TextureSelector.h"

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
    bool pressingLeft;
    bool pressingRight;

    sf::Font font;
    sf::Text cursorText;

    sf::Texture buttonIdleTexture;
    sf::Texture buttonPressedTexture;
    sf::Texture buttonSquareIdleTexture;
    sf::Texture buttonSquareActiveTexture;
    std::map<std::string, Button*> buttons;

    PauseMenu* pauseMenu;

    TileMap* tileMap;

    sf::IntRect textureRect;
    sf::RectangleShape selectorRect;

    TextureSelector* textureSelector;

    bool collision;
    short int type;

    // Functions
    void initVariables();
    void initBackground();
    void initTextures();
    void initFonts();
    void initText();
    void initKeybinds();
    void initPauseMenu();
    void initTileMap();
    void initGUI();

public:
    // Constructor/Destructor
    EditorState(StateData* stateData);
    virtual ~EditorState();

    // Functions
    void updateEvents(sf::Event& sfEvent);
    void updateEditorInput(const float& dt);
    void updateInput(const float& dt);
    void updateGUI(const float& dt);
    void updatePauseMenuButtons();
    void update(const float& dt);
    void renderGUI(sf::RenderTarget& target);
    void render(sf::RenderTarget* target = nullptr);
};