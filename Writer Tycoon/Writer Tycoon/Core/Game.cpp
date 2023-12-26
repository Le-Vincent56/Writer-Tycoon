#include "../stdafx.h"
#include "Game.h"

// Static Functions



// Initialize Functions
void Game::initVariables()
{
	this->window = nullptr;
	this->fullscreen = false;
	this->dt = 0.0f;
	this->gridSize = 100.0f;
}

void Game::initGraphicsSettings()
{
	this->gSettings.loadFromFile("Config/graphics.ini");
}

void Game::initStateData()
{
	// Set all state data
	this->stateData.window = this->window;
	this->stateData.gSettings = &this->gSettings;
	this->stateData.supportedKeys = &this->supportedKeys;
	this->stateData.states = &this->states;
	this->stateData.gridSize = this->gridSize;
}

void Game::initWindow()
{
	// Initialize window based on fullscreen vs windowed
	if(this->gSettings.fullscreen)
		this->window = new sf::RenderWindow(
			this->gSettings.resolution,
			this->gSettings.title, 
			sf::Style::Fullscreen, 
			this->gSettings.contextSettings
		);
	else
		this->window = new sf::RenderWindow(
			this->gSettings.resolution, 
			this->gSettings.title, 
			sf::Style::Titlebar | sf::Style::Close, 
			this->gSettings.contextSettings);

	this->window->setFramerateLimit(this->gSettings.frameRateLimit);
	this->window->setVerticalSyncEnabled(this->gSettings.verticalSync);
}

void Game::initKeys()
{
	// Open the control scheme
	std::ifstream ifs("Config/supported_keys.ini");

	// Add keys to the control scheme through the text file
	if (ifs.is_open())
	{
		std::string key = "";
		int value = 0;

		while (ifs >> key >> value)
		{
			this->supportedKeys[key] = value;
		}
	}

	// Close the ilfe stream
	ifs.close();
}

void Game::initStates()
{
	// Set the game state
	this->states.push(new MainMenuState(&this->stateData));
}

// Constructor/Destructor
Game::Game()
{
	// Initialize the game
	this->initVariables();
	this->initGraphicsSettings();
	this->initWindow();
	this->initKeys();
	this->initStateData();
	this->initStates();
}

Game::~Game()
{
	// Delete the window
	delete this->window;
	this->window = nullptr;

	// Delete states
	while (!this->states.empty())
	{
		delete this->states.top();
		this->states.top() = nullptr;
		this->states.pop();
	}
}

// Functions 
void Game::endApplication()
{
}

void Game::updateDt()
{
	// Update the dt variable with the time it takes to update and render one frame
	this->dt = this->dtClock.restart().asSeconds();
}

void Game::updateSFMLEvents()
{
	while (window->pollEvent(sfEvent))
	{
		if (sfEvent.type == sf::Event::Closed) {
			this->window->close();
		}

		// Check if there are states
		if (!this->states.empty())
		{
			// Update events for the top state
			this->states.top()->updateEvents(this->sfEvent);
		}
		
	}
}

void Game::update()
{
	// Update SFML events
	this->updateSFMLEvents();

	// Check if there are states and if the window is in focus
	if (!this->states.empty() && this->window->hasFocus())
	{
		// Update the top state
		this->states.top()->update(this->dt);

		// Check if the state wants to quit
		if (this->states.top()->getQuit())
		{
			// End the state
			this->states.top()->endState();

			// Remove data
			delete this->states.top();
			this->states.top() = nullptr;
			this->states.pop();
		}
	}
	else // Application end - if there are no states
	{
		// End the application
		this->endApplication();
		this->window->close();
	}
}

void Game::render()
{
	// Clear the game items
	this->window->clear();

	// Render the top state
	if (!this->states.empty())
	{
		this->states.top()->render();
	}

	// Display game items
	this->window->display();
}

void Game::run()
{
	while (this->window->isOpen())
	{
		// Update deltaTime
		this->updateDt();

		// Update the game
		this->update();

		// Render the game
		this->render();
	}
}
