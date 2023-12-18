#include "MainMenuState.h"

// Initialize Functions
void MainMenuState::initVariables()
{
}

void MainMenuState::initBackground()
{
	// Set backgorund size to the window size
	this->background.setSize(
		sf::Vector2f(
			static_cast<float>(this->window->getSize().x), 
			static_cast<float>(this->window->getSize().y)
		)
	);

	// Attempt to load the background texture
	if (!this->backgroundTexture.loadFromFile("Assets/Images/main_menu_background.png"))
	{
		throw "ERROR::MAIN_MENU_STATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE";
	}

	// Set the background texture;
	this->background.setTexture(&this->backgroundTexture);
}

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
	float windowCenterX = this->window->getSize().x / 2;
	float buttonWidth = 150;
	float buttonCenterX = windowCenterX - (buttonWidth / 2);

	float windowQuarterY = this->window->getSize().y - (this->window->getSize().y / 3);
	float buttonHeight = 50;

	this->buttons["GAME_STATE"] = new Button(buttonCenterX, windowQuarterY + (buttonHeight * 0.5), buttonWidth, buttonHeight,
		&this->font, "New Game", 24,
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

	this->buttons["SETTINGS_STATE"] = new Button(buttonCenterX, windowQuarterY + (buttonHeight * 2), buttonWidth, buttonHeight,
		&this->font, "Settings", 24,
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

	// Exit state
	this->buttons["EXIT_STATE"] = new Button(buttonCenterX, windowQuarterY + (buttonHeight * 3.5), buttonWidth, 50,
		&this->font, "Quit", 24,
		sf::Color(100, 100, 100, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));
}

// Constructor/Destructor
MainMenuState::MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	: State(window, supportedKeys, states)
{
	// Initialize variables
	this->initVariables();
	this->initBackground();
	this->initFonts();
	this->initKeybinds();
	this->initButtons();
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
void MainMenuState::updateInput(const float& dt)
{

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
		this->endState();
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

	// Remove later
	sf::Text mouseText;
	mouseText.setPosition(this->mousePosView.x, this->mousePosView.y - 50);
	mouseText.setFont(this->font);
	mouseText.setCharacterSize(12);
	std::stringstream ss;
	ss << this->mousePosView.x << ", " << this->mousePosView.y;
	mouseText.setString(ss.str());

	target->draw(mouseText);
}
