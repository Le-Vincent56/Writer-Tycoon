#pragma once

#include "States/GameState.h"

class Game
{
private:
	// Variables
	sf::RenderWindow* window;
	sf::Event sfEvent;

	sf::Clock dtClock;
	float dt;

	std::stack<State*> states;

	// Initialization
	void initWindow();
	void initStates();

public:
	// Constructor/Destructor
	Game();
	virtual ~Game();

	// Functions
	void endApplication();
	void updateDt();
	void updateSFMLEvents();
	void update();
	void render();
	void run();
};
