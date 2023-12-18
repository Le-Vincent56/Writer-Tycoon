#pragma once
#include "Entity.h"
class Player :
    public Entity
{
private:
    // Variables

    // Initializer Functions
    void initVariables();
    void initComponents();

public:
    // Constructor/Destructor
    Player(float x, float y, sf::Texture& texture);
    virtual ~Player();

    // Functions
    void updateInput(std::map<std::string, int> keybinds, const float& dt);
    void update(const float& dt);
};

