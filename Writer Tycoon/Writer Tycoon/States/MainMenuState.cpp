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

void MainMenuState::initTextures()
{
	// Load button sprites
	if (!this->buttonIdle.loadFromFile("Assets/Sprites/UI/button_long_idle.png"))
	{
		throw "ERROR::MAIN_MENU_STATE::FAILED_TO_LOAD_BUTTON_LONG_IDLE_TEXTURE";
	}

	if (!this->buttonPressed.loadFromFile("Assets/Sprites/UI/button_long_active.png"))
	{
		throw "ERROR::MAIN_MENU_STATE::FAILED_TO_LOAD_BUTTON_LONG_ACTIVE_TEXTURE";
	}
}

void MainMenuState::initFonts()
{
	// Attempt to load the font
	if (!this->font.loadFromFile("Fonts/monogram-extended.ttf"))
	{
		throw("ERROR::MAIN_MENU_STATE::COULD_NOT_LOAD_FONT_MONOGRAM_EXTENDED");
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


void MainMenuState::initGUI()
{
	// Button Params
	float windowCenterX = this->window->getSize().x / 2;
	float buttonWidth = 200;
	float buttonCenterX = windowCenterX - (buttonWidth / 2);

	float windowCenterY = this->window->getSize().y / 2;
	float buttonHeight = 75;

	// Game State
	this->buttons["GAME_STATE"] = new Button(
		buttonCenterX, windowCenterY + (buttonHeight * 0.5), 
		buttonWidth, buttonHeight,
		this->font, "NEW GAME", 28,
		sf::Color(0, 0, 0, 255), sf::Color(180, 180, 180, 255), sf::Color(150, 150, 150, 255),
		this->buttonIdle, this->buttonPressed
	);

	// Settings State
	this->buttons["SETTINGS_STATE"] = new Button(
		buttonCenterX, windowCenterY + (buttonHeight * 2.0), 
		buttonWidth, buttonHeight,
		this->font, "SETTINGS", 28,
		sf::Color(0, 0, 0, 255), sf::Color(180, 180, 180, 255), sf::Color(150, 150, 150, 255),
		this->buttonIdle, this->buttonPressed
	);

	// Editor State
	this->buttons["EDITOR_STATE"] = new Button(
		buttonCenterX, windowCenterY + (buttonHeight * 3.5), 
		buttonWidth, buttonHeight,
		this->font, "EDITOR", 28,
		sf::Color(0, 0, 0, 255), sf::Color(180, 180, 180, 255), sf::Color(150, 150, 150, 255),
		this->buttonIdle, this->buttonPressed
	);

	// Exit state
	this->buttons["EXIT_STATE"] = new Button(
		buttonCenterX, windowCenterY + (buttonHeight * 5.0), 
		buttonWidth, buttonHeight,
		this->font, "QUIT", 28,
		sf::Color(0, 0, 0, 255), sf::Color(180, 180, 180, 255), sf::Color(150, 150, 150, 255),
		this->buttonIdle, this->buttonPressed
	);
}

// Constructor/Destructor
MainMenuState::MainMenuState(sf::RenderWindow* window, 
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
	this->initGUI();
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
void MainMenuState::updateEvents(sf::Event& sfEvent)
{
	// Update button events
	for (auto& it : this->buttons)
	{
		it.second->updateEvents(sfEvent, this->mousePosView);
	}
}

void MainMenuState::updateInput(const float& dt)
{

}

void MainMenuState::updateGUI(const float& dt)
{
	// Update the buttons
	for (auto &it : this->buttons)
	{
		it.second->update(dt, this->mousePosView);
	}

	// Start new game
	if (this->buttons["GAME_STATE"]->isPressed())
	{
		this->states->push(new GameState(this->window, this->supportedKeys, this->states));
	}

	// Open Settings
	if (this->buttons["SETTINGS_STATE"]->isPressed())
	{
		this->states->push(new SettingsState(this->window, this->supportedKeys, this->states));
	}

	// Open Editor
	if (this->buttons["EDITOR_STATE"]->isPressed())
	{
		this->states->push(new EditorState(this->window, this->supportedKeys, this->states));
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
	this->updateGUI(dt);
}

void MainMenuState::renderGUI(sf::RenderTarget& target)
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

	this->renderGUI(*target);

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
