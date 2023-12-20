#include "State.h"

State::State(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
{
	// Assign variables
	this->window = window;
	this->supportedKeys = supportedKeys;
	this->states = states;
	this->quit = false;
	this->paused = false;
	this->canPressKey = true;
	this->keyTime = 5.0f;
}

// Constructor/Destructor
State::~State()
{
}

// Accessors
const bool& State::getQuit() const
{
	return this->quit;
}

const bool State::getCanPressKey()
{
	return this->canPressKey;
}

// Functions
void State::endState()
{
	this->quit = true;
}

void State::pauseState()
{
	this->paused = true;
}

void State::unpauseState()
{
	this->paused = false;
}

void State::startKeyTimer()
{
	this->canPressKey = false;
}

void State::updateKeyTime(const float& dt)
{
	// Check if a key can be pressed
	if (!canPressKey)
	{
		// Update key time if it hasn't hit the max time yet
		if (this->keyTime >= 0)
		{
			this->keyTime -= 10.0f * dt;
			canPressKey = false;
		}
		else
		{
			this->keyTime = 5.0f;
			canPressKey = true;
		}
	}
}

void State::updateMousePositions()
{
	// Get all mouse positions
	this->mousePosScreen = sf::Mouse::getPosition();
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
}
