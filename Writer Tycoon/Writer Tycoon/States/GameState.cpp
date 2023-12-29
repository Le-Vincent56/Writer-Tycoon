#include "../stdafx.h"
#include "GameState.h"

// Initializer Functions
void GameState::initView()
{
	// Set the view size to the current resolution
	this->view.setSize(
		sf::Vector2f(
			static_cast<float>(this->stateData->gSettings->resolution.width),
			static_cast<float>(this->stateData->gSettings->resolution.height))
	);

	// Set the view center to the center of the current resolution
	this->view.setCenter(
		static_cast<float>(this->stateData->gSettings->resolution.width) / 2.0f,
		static_cast<float>(this->stateData->gSettings->resolution.height) / 2.0f
	);
}

void GameState::initDeferredRender()
{
	// Create a render texture "canvas" that encapsulates the screen
	this->renderTexture.create(
		this->stateData->gSettings->resolution.width,
		this->stateData->gSettings->resolution.height
	);

	// Set the render sprite
	this->renderSprite.setTexture(this->renderTexture.getTexture());

	// Set the texture rect of the render sprite to the resolution of the screen
	this->renderSprite.setTextureRect(
		sf::IntRect(
			0,
			0,
			this->stateData->gSettings->resolution.width,
			this->stateData->gSettings->resolution.height
		)
	);
}

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
	float buttonWidth = 200.0f;
	float buttonCenterX = windowCenterX - (buttonWidth / 2.0f);

	float windowCenterY = this->pauseMenu->getContainerCenterBelowText().y;
	float buttonHeight = 75.0f;
	float buttonCenterY = windowCenterY - (buttonHeight / 2.0f);

	this->pauseMenu->addButton("RESUME_STATE", "RESUME", 
		buttonCenterX, windowCenterY + buttonCenterY, 
		buttonWidth, buttonHeight
	);

	this->pauseMenu->addButton("SETTINGS_STATE", "SETTINGS",
		buttonCenterX, windowCenterY + (buttonCenterY * 2.0f),
		buttonWidth, buttonHeight
	);

	this->pauseMenu->addButton("EXIT_STATE", "MAIN MENU",
		buttonCenterX, windowCenterY + (buttonCenterY * 3.0f),
		buttonWidth, buttonHeight
	);
}

void GameState::initPopups()
{
	float windowCenterX = this->window->getSize().x / 2.0f;
	float popupWidth = 1000;
	float popupCenterX = windowCenterX - (popupWidth / 2.0f);

	float windowCenterY = this->window->getSize().y / 2.0f;
	float popupHeight = 1000;
	float popupCenterY = windowCenterY - (popupHeight / 2.0f);

	this->popup = new Popup(popupCenterX, popupCenterY, popupWidth, popupHeight, 
		this->font, this->popupFrameTexture);

	// Add text
	popup->addItem(new sf::Text("Text 1", this->font, 32), 300, 300);

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

void GameState::initTileMap()
{
	this->tileMap = new TileMap(this->stateData->gridSize, 10, 10, "Assets/Sprites/Environment/Floor_Tilesheet_1.png");
	this->tileMap->loadFromFile("TestSave.wtmp");
}

// Constructor/Destructor
GameState::GameState(StateData* stateData)
	: State(stateData)
{
	this->initView();
	this->initDeferredRender();
	this->initTextures();
	this->initFonts();
	this->initKeybinds();
	this->initGUI();
	this->initEntities();
	this->initTileMap();
}

GameState::~GameState()
{
	delete this->pauseMenu;
	this->pauseMenu = nullptr;
	delete this->popup;
	this->popup = nullptr;
	delete this->player;
	this->player = nullptr;
	delete this->tileMap;
	this->tileMap = nullptr;
}

// Functions
void GameState::updateView(const float& dt)
{
	// Track the player by always keeping it at the center position
	this->view.setCenter(
		std::floor(this->player->getPosition().x), 
		std::floorf(this->player->getPosition().y)
	);
}

void GameState::updateEvents(sf::Event& sfEvent)
{
	// Check if paused
	if (this->paused)
	{
		// Update pause menu events
		this->pauseMenu->updateEvents(sfEvent, this->mousePosWindow);
	}
	else
	{
		// Update popups
		this->popup->updateEvents(sfEvent, this->mousePosWindow);
	}
}

void GameState::updateInput(const float& dt)
{
	// Pause the game
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))) && this->getCanPressKey())
	{
		// Start the key timer
		this->startKeyTimer();

		//this->popup->setEnabled(!this->popup->getEnabled());

		 //Toggle paused
		if (!this->paused)
		{
			this->pauseState();
		}
		else
		{
			this->unpauseState();
		}
	}
}

void GameState::updateGUI(const float& dt)
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
		this->states->push(new SettingsState(this->stateData));
	}

	// Exit state
	if (this->pauseMenu->isButtonPressed("EXIT_STATE"))
	{
		this->endState();
	}
}

void GameState::updateTileMap(const float& dt)
{
	// Update the tilemap and collisions
	this->tileMap->update();
	this->tileMap->updateCollision(dt, this->player);
}


void GameState::update(const float& dt)
{
	// Update mouse positions
	this->updateMousePositions(&this->view);

	// Update GUI
	this->updateGUI(dt);

	// Update key time
	this->updateKeyTime(dt);

	// Update input
	this->updateInput(dt);

	// Check if paused
	if(!this->paused)
	{
		// Update the view
		this->updateView(dt);

		// Update player input
		this->player->updateInput(this->keybinds, dt);

		// Update the tilemap
		this->updateTileMap(dt);

		// Update player
		this->player->update(dt);
	}
	else
	{
		// Update the pause menu
		this->pauseMenu->update(dt, this->mousePosWindow);

		// Update buttons
		this->updatePauseMenuButtons();
	}

	// Update popups
	this->popup->update(dt, this->mousePosWindow);
}

void GameState::render(sf::RenderTarget* target)
{
	// If nothing bound to target, set it to this window
	if (!target)
		target = this->window;

	// Clear the render canvas before display
	this->renderTexture.clear();

	// Render the tilemap
	this->renderTexture.setView(this->view);
	this->tileMap->render(this->renderTexture, this->player);

	// Draw the player
	this->player->render(this->renderTexture);

	// Draw the pause menu
	if (this->paused)
	{
		this->renderTexture.setView(this->window->getDefaultView());
		this->pauseMenu->render(this->renderTexture);
	}

	// Draw popups
	this->renderTexture.setView(this->window->getDefaultView());
	this->popup->render(this->renderTexture);

	// Draw the canvas
	this->renderTexture.display();
	this->renderSprite.setTexture(this->renderTexture.getTexture());
	target->draw(this->renderSprite);
}