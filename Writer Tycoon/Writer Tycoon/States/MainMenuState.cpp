#include "MainMenuState.h"

// Initialize Functions
void MainMenuState::initFonts()
{
	// Attempt to load the font
	if (!this->font.loadFromFile("Fonts/EBGaramond-Regular.ttf"))
	{
		throw("ERROR: MainMenuState could not load font");
	}
}

void MainMenuState::initKeybinds()
{
	// Open the control scheme
	std::ifstream ifs("Config/mainmenustate_keybinds.ini");

	// Add keys to the control scheme through the text file
	if (ifs.is_open())
	{
		std::string bindKey = "";
		std::string controlKey = "";

		while (ifs >> bindKey >> controlKey)
		{
			this->keybinds[bindKey] = this->supportedKeys->at(controlKey);
		}
	}

	// Close the ilfe stream
	ifs.close();
}


void MainMenuState::initButtons()
{
	// Game state button
	this->buttons["GAME_STATE"] = new Button(100, 100, 150, 50,
		&this->font, "New Game", 24,
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

	// Exit state
	this->buttons["EXIT_STATE"] = new Button(100, 300, 150, 50,
		&this->font, "Quit", 24,
		sf::Color(100, 100, 100, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));
}

// Constructor/Destructor
MainMenuState::MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	: State(window, supportedKeys, states)
{
	// Initialize variables
	this->initFonts();
	this->initKeybinds();
	this->initButtons();

	// Set background
	this->background.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
	this->background.setFillColor(sf::Color::Magenta);
}

MainMenuState::~MainMenuState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}

// Functions
void MainMenuState::endState()
{
	std::cout << "Ending MainMenuState!" << "\n";
}

void MainMenuState::updateInput(const float& dt)
{
	// Check if quit
	this->checkForQuit();
}

void MainMenuState::updateButtons()
{
	// Update the buttons
	for (auto &it : this->buttons)
	{
		it.second->update(this->mousePosView);
	}

	// Start new game
	if (this->buttons["GAME_STATE"]->isPressed())
	{
		this->states->push(new GameState(this->window, this->supportedKeys, this->states));
	}

	// Quit the game
	if (this->buttons["EXIT_STATE"]->isPressed())
	{
		this->quit = true;
	}
}

void MainMenuState::update(const float& dt)
{
	// Update mouse positions
	this->updateMousePositions();

	// Update input
	this->updateInput(dt);

	// Update buttons
	this->updateButtons();
}

void MainMenuState::renderButtons(sf::RenderTarget* target)
{
	// Draw the buttons
	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}
}

void MainMenuState::render(sf::RenderTarget* target)
{
	// If nothing bound to target, set it to this window
	if (!target)
		target = this->window;

	// Draw the background
	target->draw(this->background);

	this->renderButtons(target);
}
