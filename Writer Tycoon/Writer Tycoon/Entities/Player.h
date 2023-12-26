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
    Player(float x, float y, sf::Texture& textureSheet);
    virtual ~Player();

    // Functions
    void updateInput(std::map<std::string, int> keybinds, const float& dt);
    void updateMovement(const float& dt);
    void updateAnimation(const float& dt);
    void updateHitbox();
    void update(const float& dt);
    void render(sf::RenderTarget& target);
};

