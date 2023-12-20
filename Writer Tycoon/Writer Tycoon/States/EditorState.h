#pragma once

#include "State.h"

class EditorState :
    public State
{
private:
    // Variables
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
    void initButtons();

public:
    // Constructor/Destructor
    EditorState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
    virtual ~EditorState();

    // Functions
    void updateInput(const float& dt);
    void updateButtons();
    void update(const float& dt);
    void renderButtons(sf::RenderTarget& target);
    void render(sf::RenderTarget* target = nullptr);
};