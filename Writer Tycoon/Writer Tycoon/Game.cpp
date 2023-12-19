#include "Game.h"

// Static Functions



// Initialize Functions
void Game::initVariables()
{
	this->window = nullptr;
	this->fullscreen = false;
	this->dt = 0.0f;
}

void Game::initWindow() {
	// Open the config ini
	std::ifstream ifs("Config/window.ini");

	// Retrieve all video modes
	this->videoModes = sf::VideoMode::getFullscreenModes();

	// Set default settings in case of read failure
	std::string title = "None";
	sf::VideoMode window_bounds = sf::VideoMode::getDesktopMode();
	bool fullscreen = false;
	unsigned int framerate_limit = 120;
	bool vertical_sync_enabled = false;
	unsigned int antialiasing_level = 0;

	// Check if the file is open
	if (ifs.is_open())
	{
		// Read data
		std::getline(ifs, title);
		ifs >> window_bounds.width >> window_bounds.height;		// Load window size settings
		ifs >> fullscreen;										// Load fullscreen settings
		ifs >> framerate_limit;									// Load framerate limit settings
		ifs >> vertical_sync_enabled;						    // Load VSync settings
		ifs >> antialiasing_level;								// Load antialiasing settings
	}

	// Close the file
	ifs.close();

	// Assign settings
	this->fullscreen = fullscreen;
	this->windowSettings.antialiasingLevel = antialiasing_level;

	if(this->fullscreen)
		this->window = new sf::RenderWindow(window_bounds, title, sf::Style::Fullscreen, this->windowSettings);
	else
		this->window = new sf::RenderWindow(window_bounds, title, sf::Style::Titlebar | sf::Style::Close, this->windowSettings);

	this->window->setFramerateLimit(framerate_limit);
	this->window->setVerticalSyncEnabled(vertical_sync_enabled);
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
	this->states.push(new MainMenuState(this->window, &this->supportedKeys, &this->states));
}

// Constructor/Destructor
Game::Game()
{
	// Initialize the game
	this->initVariables();
	this->initWindow();
	this->initKeys();
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
