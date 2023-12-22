#include "../stdafx.h"
#include "State.h"

State::State(StateData* stateData)
{
	// Assign variables
	this->stateData = stateData;
	this->window = stateData->window;
	this->supportedKeys = stateData->supportedKeys;
	this->states = stateData->states;
	this->gridSize = stateData->gridSize;
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
	if (!this->canPressKey)
	{
		// Update key time if it hasn't hit the max time yet
		if (this->keyTime >= 0)
		{
			this->keyTime -= 10.0f * dt;
			this->canPressKey = false;
		}
		else
		{
			// Reset key time and whether the player can press
			// a key
			this->keyTime = 5.0f;
			this->canPressKey = true;
		}
	}
}

void State::updateMousePositions()
{
	// Get all mouse positions
	this->mousePosScreen = sf::Mouse::getPosition();
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
	this->mousePosGrid = sf::Vector2u(
		static_cast<unsigned int>(this->mousePosView.x) / static_cast<unsigned int>(this->gridSize),
		static_cast<unsigned int>(this->mousePosView.y) / static_cast<unsigned int>(this->gridSize)
	);
}
