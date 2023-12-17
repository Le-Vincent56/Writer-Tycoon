#include "State.h"

State::State(sf::RenderWindow* window)
{
	// Assign the window
	this->window = window;

	// End variable
	quit = false;
}

State::~State()
{
}

const bool& State::getQuit() const
{
	return this->quit;
}

void State::checkForQuit()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		this->quit = true;
	}
}
