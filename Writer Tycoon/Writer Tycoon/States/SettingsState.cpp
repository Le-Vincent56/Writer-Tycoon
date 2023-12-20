#include "SettingsState.h"

// Initialize Functions
void SettingsState::initVariables()
{
}

void SettingsState::initBackground()
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

void SettingsState::initTextures()
{
	// Load button sprites
	if (!this->buttonIdle.loadFromFile("Assets/Sprites/UI/button_long.png"))
	{
		throw "ERROR::MAIN_MENU_STATE::FAILED_TO_LOAD_BUTTON_LONG_TEXTURE";
	}

	if (!this->buttonPressed.loadFromFile("Assets/Sprites/UI/button_long_pressed.png"))
	{
		throw "ERROR::MAIN_MENU_STATE::FAILED_TO_LOAD_BUTTON_LONG_PRESSED_TEXTURE";
	}
}

void SettingsState::initFonts()
{
	// Attempt to load the font
	if (!this->font.loadFromFile("Fonts/monogram-extended.ttf"))
	{
		throw("ERROR::MAIN_MENU_STATE::COULD_NOT_LOAD_FONT_MONOGRAM_EXTENDED");
	}
}

void SettingsState::initKeybinds()
{
	// Open the control scheme
	std::ifstream ifs("Config/settingsstate_keybinds.ini");

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


void SettingsState::initButtons()
{
	// Button Params
	float windowCenterX = this->window->getSize().x / 2;
	float buttonWidth = 200;
	float buttonCenterX = windowCenterX - (buttonWidth / 2);

	float windowCenterY = this->window->getSize().y / 2;
	float buttonHeight = 75;

	// Exit state
	this->buttons["EXIT_STATE"] = new Button(
		buttonCenterX, windowCenterY + (buttonHeight * 5.0),
		buttonWidth, buttonHeight,
		this->font, "QUIT", 32,
		sf::Color(0, 0, 0, 255), sf::Color(180, 180, 180, 255), sf::Color(150, 150, 150, 255),
		this->buttonIdle, this->buttonPressed
	);
}

// Constructor/Destructor
SettingsState::SettingsState(sf::RenderWindow* window, 
	std::map<std::string, int>* supportedKeys, 
	std::stack<State*>* states)
	: State(window, supportedKeys, states)
{
	// Initialize variables
	this->initVariables();
	this->initBackground();
	this->initTextures();
	this->initFonts();
	this->initKeybinds();
	this->initButtons();
}

SettingsState::~SettingsState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}

// Functions
void SettingsState::updateInput(const float& dt)
{
}

void SettingsState::updateButtons()
{
	// Update the buttons
	for (auto& it : this->buttons)
	{
		it.second->update(this->mousePosView);
	}

	// Quit the game
	if (this->buttons["EXIT_STATE"]->isPressed() && this->getCanPressButtons())
	{
		this->startButtonTimer();
		this->endState();
	}
}

void SettingsState::update(const float& dt)
{
	// Update mouse positions
	this->updateMousePositions();

	// Update button time
	this->updateButtonTime(dt);

	// Update input
	this->updateInput(dt);

	// Update buttons
	this->updateButtons();
}

void SettingsState::renderButtons(sf::RenderTarget& target)
{
	// Draw the buttons
	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}
}

void SettingsState::render(sf::RenderTarget* target)
{
	// If nothing bound to target, set it to this window
	if (!target)
		target = this->window;

	// Draw the background
	target->draw(this->background);

	this->renderButtons(*target);
}