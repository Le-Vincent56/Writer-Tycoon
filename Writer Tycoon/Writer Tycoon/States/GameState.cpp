#include "GameState.h"

// Initializer Functions
void GameState::initTextures()
{
	// Load player sprite
	if (!this->textures["PLAYER_SHEET"].loadFromFile("Assets/Sprites/Player/player_sprite_sheet.png"))
	{
		throw "ERROR::GAME_STATE_::COULD_NOT_LOAD_PLAYER_SPRITE_SHEET_TEXTURE";
	}

	// Load button sprites
	if (!this->buttonIdleTexture.loadFromFile("Assets/Sprites/UI/button_long_idle.png"))
	{
		throw "ERROR::GAME_STATE::FAILED_TO_LOAD_BUTTON_LONG_IDLE_TEXTURE";
	}

	if (!this->buttonPressedTexture.loadFromFile("Assets/Sprites/UI/button_long_active.png"))
	{
		throw "ERROR::GAME_STATE::FAILED_TO_LOAD_BUTTON_LONG_ACTIVE_TEXTURE";
	}

	// Load popup frame sprite
	if (!this->popupFrameTexture.loadFromFile("Assets/Sprites/UI/popup_frame.png"))
	{
		throw "ERROR::GAME_STATE::FAILED_TO_LOAD_POPUP_FRAME_TEXTURE";
	}
}

void GameState::initFonts()
{
	// Attempt to load the font
	if (!this->font.loadFromFile("Fonts/monogram-extended.ttf"))
	{
		throw("ERROR::GAME_STATE::COULD_NOT_LOAD_FONT_MONOGRAM_EXTENDED");
	}
}

void GameState::initKeybinds()
{
	// Open the control scheme
	std::ifstream ifs("Config/gamestate_keybinds.ini");

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

void GameState::initPauseMenu()
{
	// Create pause menu
	this->pauseMenu = new PauseMenu(*this->window, this->font, this->buttonIdleTexture, this->buttonPressedTexture);

	// Button Params
	float windowCenterX = this->pauseMenu->getContainerCenterBelowText().x;
	float buttonWidth = 200;
	float buttonCenterX = windowCenterX - (buttonWidth / 2);

	float windowCenterY = this->pauseMenu->getContainerCenterBelowText().y;
	float buttonHeight = 75;
	float buttonCenterY = windowCenterY - (buttonHeight / 2);

	this->pauseMenu->addButton("RESUME_STATE", "RESUME", 
		buttonCenterX, windowCenterY + buttonCenterY, 
		buttonWidth, buttonHeight
	);

	this->pauseMenu->addButton("SETTINGS_STATE", "SETTINGS",
		buttonCenterX, windowCenterY + (buttonCenterY * 2.0),
		buttonWidth, buttonHeight
	);

	this->pauseMenu->addButton("EXIT_STATE", "MAIN MENU",
		buttonCenterX, windowCenterY + (buttonCenterY * 3.0),
		buttonWidth, buttonHeight
	);
}

void GameState::initPopups()
{
	float windowCenterX = this->window->getSize().x / 2.0f;
	float popupWidth = 1000;
	float popupCenterX = windowCenterX - (popupWidth / 2);

	float windowCenterY = this->window->getSize().y / 2.0f;
	float popupHeight = 1000;
	float popupCenterY = windowCenterY - (popupHeight / 2);

	this->popup = new Popup(popupCenterX, popupCenterY, popupWidth, popupHeight, 
		this->font, this->popupFrameTexture);

	// Add text
	sf::Text* text1 = new sf::Text("Text 1", this->font, 32);
	popup->addItem(text1, 500 - text1->getLocalBounds().width/2, 500 - text1->getCharacterSize()/2);
	std::cout << "Text 1 Bounds Width/Height: "
		<< text1->getLocalBounds().width << ", " << text1->getCharacterSize() << "\n";

	this->popup->setEnabled(false);
}

void GameState::initGUI()
{
	// Initialize pause menu
	this->initPauseMenu();

	// Initialize popup
	this->initPopups();
}

void GameState::initEntities()
{
	this->player = new Player(0, 0, this->textures["PLAYER_SHEET"]);
}

// Constructor/Destructor
GameState::GameState(sf::RenderWindow* window, 
	std::map<std::string, int>* supportedKeys, 
	std::stack<State*>* states)
	: State(window, supportedKeys, states)
{
	this->initTextures();
	this->initFonts();
	this->initKeybinds();
	this->initGUI();
	this->initEntities();
}

GameState::~GameState()
{
	delete this->pauseMenu;
	delete this->popup;
	delete this->player;
}

// Functions
void GameState::updateEvents(sf::Event& sfEvent)
{
	// Check if paused
	if (this->paused)
	{
		// Update pause menu events
		this->pauseMenu->updateEvents(sfEvent, this->mousePosView);
	}

	// Update popups
	this->popup->updateEvents(sfEvent, this->mousePosView);
}

void GameState::updateInput(const float& dt)
{
	// Pause the game
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))) && this->getCanPressKey())
	{
		// Start the key timer
		this->startKeyTimer();

		this->popup->setEnabled(!this->popup->getEnabled());

		/* //Toggle paused
		if (!this->paused)
		{
			this->pauseState();
		}
		else
		{
			this->unpauseState();
		}*/
	}
}

void GameState::updateGUI(const float& dt, const sf::Vector2f& mousePosView)
{
}

void GameState::updatePauseMenuButtons()
{
	// Resume state
	if (this->pauseMenu->isButtonPressed("RESUME_STATE"))
	{
		this->unpauseState();
	}

	// Settings state
	if (this->pauseMenu->isButtonPressed("SETTINGS_STATE"))
	{
		this->states->push(new SettingsState(this->window, this->supportedKeys, this->states));
	}

	// Exit state
	if (this->pauseMenu->isButtonPressed("EXIT_STATE"))
	{
		this->endState();
	}
}


void GameState::update(const float& dt)
{
	// Update mouse positions
	this->updateMousePositions();

	// Update GUI
	this->updateGUI(dt, this->mousePosView);

	// Update key time
	this->updateKeyTime(dt);

	// Update input
	this->updateInput(dt);

	// Check if paused
	if(!this->paused)
	{
		// Update player input
		this->player->updateInput(this->keybinds, dt);

		// Update player
		this->player->update(dt);
	}
	else
	{
		// Update the pause menu
		this->pauseMenu->update(dt, this->mousePosView);

		// Update buttons
		this->updatePauseMenuButtons();
	}

	// Update popups
	this->popup->update(dt, this->mousePosView);
}

void GameState::render(sf::RenderTarget* target)
{
	// If nothing bound to target, set it to this window
	if (!target)
		target = this->window;

	// Draw the player
	this->player->render(*target);

	// Draw the pause menu
	if (this->paused)
	{
		this->pauseMenu->render(*target);
	}

	// Draw popups
	this->popup->render(*target);
}