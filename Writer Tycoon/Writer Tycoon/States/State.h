#pragma once

#include "../Core/GraphicsSettings.h"
#include "../Entities/Player.h"

// Forward Declarations
class State;
class GraphicsSettings;
class Player;

class StateData
{
public:
	// Variables
	float gridSize;
	sf::RenderWindow* window;
	GraphicsSettings* gSettings;
	std::map <std::string, int>* supportedKeys;
	std::stack<State*>* states;

	// Constructor/Destructor
	StateData() {};
};

class State
{
private:


protected:
	// Variables
	StateData* stateData;
	sf::RenderWindow* window;
	std::stack<State*>* states;
	std::map<std::string, int>* supportedKeys;
	std::map<std::string, int> keybinds;
	float gridSize;
	bool quit;
	bool paused;

	bool canPressKey;
	float keyTime;

	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;
	sf::Vector2u mousePosGrid;

	// Resources
	std::map<std::string, sf::Texture> textures;

	// Functions
	virtual void initKeybinds() = 0;

public:
	// Constructor/Destructor
	State(StateData* stateData);
	virtual ~State();

	// Accessors
	const bool& getQuit() const;
	const bool getCanPressKey();

	// Functions
	void endState();
	void pauseState();
	void unpauseState();
	void startKeyTimer();
	virtual void updateEvents(sf::Event& sfEvent) = 0;
	virtual void updateKeyTime(const float& dt);
	virtual void updateMousePositions(sf::View* view = nullptr);
	virtual void updateInput(const float& dt) = 0;
	virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderTarget* target = nullptr) = 0;
};

