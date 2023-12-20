#pragma once

#include "..\Entities\Player.h"
#include "../Resources/Button.h"

class State
{
private:


protected:
	// Variables
	sf::RenderWindow* window;
	std::stack<State*>* states;
	std::map<std::string, int>* supportedKeys;
	std::map<std::string, int> keybinds;
	bool quit;
	bool paused;

	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	// Resources
	std::map<std::string, sf::Texture> textures;

	// Functions
	virtual void initKeybinds() = 0;

public:
	// Constructor/Destructor
	State(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
	virtual ~State();

	// Functions
	const bool& getQuit() const;
	void endState();
	void pauseState();
	void unpauseState();
	virtual void updateMousePositions();
	virtual void updateInput(const float& dt) = 0;
	virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderTarget* target = nullptr) = 0;
};

