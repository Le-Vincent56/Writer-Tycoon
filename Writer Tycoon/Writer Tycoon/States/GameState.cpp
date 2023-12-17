#include "GameState.h"

GameState::GameState(sf::RenderWindow* window)
	: State(window)
{

}

GameState::~GameState()
{

}

void GameState::updateKeybinds(const float& dt)
{
	// Check if quit
	this->checkForQuit();
}

void GameState::endState()
{
	std::cout << "Ending GameState!" << "\n";
}

void GameState::update(const float& dt)
{
	// Update keybinds
	this->updateKeybinds(dt);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		std::cout << "A" << "\n";
	}
}

void GameState::render(sf::RenderTarget* target)
{
}
