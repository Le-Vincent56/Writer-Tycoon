#include "Game.h"

// Static Functions

// Initialize Functions
void Game::initWindow() {
	// Open the config ini
	std::ifstream ifs("Config/window.ini");

	// Set default settings in case of read failure
	std::string title = "None";
	sf::VideoMode window_bounds(800, 600);
	unsigned int framerate_limit = 120;
	bool vertical_sync_enabled = false;

	// Check if the file is open
	if (ifs.is_open())
	{
		// Read data
		std::getline(ifs, title);
		ifs >> window_bounds.width >> window_bounds.height;		// Load Window size
		ifs >> framerate_limit;									// Load framerate limit
		ifs >> vertical_sync_enabled;						    // Load VSync
	}

	// Close the file
	ifs.close();

	// Assign settings
	this->window = new sf::RenderWindow(window_bounds, title);
	this->window->setFramerateLimit(framerate_limit);
	this->window->setVerticalSyncEnabled(vertical_sync_enabled);
}

void Game::initStates()
{
	this->states.push(new GameState(this->window));
}

// Constructor/Destructor
Game::Game()
{
	// Initialize the game
	this->initWindow();
	this->initStates();
}

Game::~Game()
{
	// Delete the window
	delete this->window;

	// Delete states
	while (!this->states.empty())
	{
		delete this->states.top();
		this->states.pop();
	}
}

// Functions 
void Game::endApplication()
{
	std::cout << "Ending application!";
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
	}
}

void Game::update()
{
	// Update SFML events
	this->updateSFMLEvents();

	// Update the top state
	if (!this->states.empty())
	{
		this->states.top()->update(this->dt);

		// Check if the state wants to quit
		if (this->states.top()->getQuit())
		{
			// End the state
			this->states.top()->endState();

			// Remove data
			delete this->states.top();
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
