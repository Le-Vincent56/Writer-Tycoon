#pragma once

#include "State.h"

class GameState :
    public State
{
private:
    Player* player;

    // Initalizer Functions
    void initKeybinds();
    void initTextures();
    void initEntities();

public:
    // Constructor/Destructor
    GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
    virtual ~GameState();

    // Functions
    void updateInput(const float& dt);
    void update(const float& dt);
    void render(sf::RenderTarget* target = nullptr);
};

