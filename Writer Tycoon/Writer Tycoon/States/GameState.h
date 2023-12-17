#pragma once

#include "State.h"
class GameState :
    public State
{
private:

public:
    // Constructor/Destructor
    GameState(sf::RenderWindow* window);
    virtual ~GameState();

    // Functions
    void updateKeybinds(const float& dt);
    void endState();
    void update(const float& dt);
    void render(sf::RenderTarget* target = nullptr);
};

