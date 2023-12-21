#pragma once

#include "State.h"
#include "SettingsState.h"
#include "..\GUI\PauseMenu.h"

class GameState :
    public State
{
private:
    sf::Font font;
    sf::Texture buttonIdle;
    sf::Texture buttonPressed;

    PauseMenu* pauseMenu;

    Player* player;

    // Initalizer Functions
    void initTextures();
    void initFonts();
    void initKeybinds();
    void initPauseMenu();
    void initEntities();

public:
    // Constructor/Destructor
    GameState(sf::RenderWindow* window, 
        std::map<std::string, int>* supportedKeys, 
        std::stack<State*>* states);
    virtual ~GameState();

    // Functions
    void updateEvents(sf::Event& sfEvent);
    void updateInput(const float& dt);
    void updatePauseMenuButtons();
    void update(const float& dt);
    void render(sf::RenderTarget* target = nullptr);
};

