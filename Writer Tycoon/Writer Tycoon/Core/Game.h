#pragma once

#include "GraphicsSettings.h"
#include "../States/MainMenuState.h"

// Forward Declarations
class GraphicsSettings;
class MainMenuState;

class Game
{
private:
	// Variables
	StateData stateData;
	GraphicsSettings gSettings;
	sf::RenderWindow* window;
	sf::Event sfEvent;
	std::vector<sf::VideoMode> videoModes;
	sf::ContextSettings windowSettings;
	bool fullscreen;

	sf::Clock dtClock;
	float dt;

	std::stack<State*> states;

	std::map<std::string, int> supportedKeys;

	float gridSize;

	// Initialization
	void initVariables();
	void initGraphicsSettings();
	void initWindow();
	void initKeys();
	void initStateData();
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
