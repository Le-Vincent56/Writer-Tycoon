#include "../stdafx.h"
#include "EditorState.h"

// Initialize Functions
void EditorState::initVariables()
{
}

void EditorState::initBackground()
{
}

void EditorState::initTextures()
{
	// Load button sprites
	if (!this->buttonIdleTexture.loadFromFile("Assets/Sprites/UI/button_long_idle.png"))
	{
		throw "ERROR::EDITOR_STATE::FAILED_TO_LOAD_BUTTON_LONG_IDLE_TEXTURE";
	}

	if (!this->buttonPressedTexture.loadFromFile("Assets/Sprites/UI/button_long_active.png"))
	{
		throw "ERROR::EDITOR_STATE::FAILED_TO_LOAD_BUTTON_LONG_active_TEXTURE";
	}
}

void EditorState::initFonts()
{
	// Attempt to load the font
	if (!this->font.loadFromFile("Fonts/monogram-extended.ttf"))
	{
		throw("ERROR::EDITOR_STATE::COULD_NOT_LOAD_FONT_MONOGRAM_EXTENDED");
	}
}

void EditorState::initKeybinds()
{
	// Open the control scheme
	std::ifstream ifs("Config/editorstate_keybinds.ini");

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

void EditorState::initPauseMenu()
{
	// Create pause menu
	this->pauseMenu = new PauseMenu(*this->window, this->font, 
		this->buttonIdleTexture, this->buttonPressedTexture);

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


void EditorState::initGUI()
{
	// Initialize the pause menu
	this->initPauseMenu();
}

// Constructor/Destructor
EditorState::EditorState(StateData* stateData)
	: State(stateData)
{
	// Initialize variables
	this->initVariables();
	this->initBackground();
	this->initTextures();
	this->initFonts();
	this->initKeybinds();
	this->initGUI();
}

EditorState::~EditorState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}

// Functions
void EditorState::updateEvents(sf::Event& sfEvent)
{
	// Update button events
	for (auto& it : this->buttons)
	{
		it.second->updateEvents(sfEvent, this->mousePosView);
	}

	// Check if paused
	if (this->paused)
	{
		// Update pause menu events
		this->pauseMenu->updateEvents(sfEvent, this->mousePosView);
	}
}

void EditorState::updateInput(const float& dt)
{
	// Pause the game
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))) && this->getCanPressKey())
	{
		// Start the key timer
		this->startKeyTimer();

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

void EditorState::updateGUI()
{
}

void EditorState::updatePauseMenuButtons()
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

void EditorState::update(const float& dt)
{
	// Update mouse positions
	this->updateMousePositions();

	// Update buttons
	this->updateGUI();

	// Update keytime
	this->updateKeyTime(dt);

	// Update input
	this->updateInput(dt);

	// Check if paused
	if (!this->paused)
	{
		
	}
	else
	{
		// Update the pause menu
		this->pauseMenu->update(dt, this->mousePosView);

		// Update buttons
		this->updatePauseMenuButtons();
	}
}

void EditorState::renderGUI(sf::RenderTarget& target)
{
	// Draw the buttons
	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}
}

void EditorState::render(sf::RenderTarget* target)
{
	// If nothing bound to target, set it to this window
	if (!target)
		target = this->window;

	// Draw buttons
	this->renderGUI(*target);

	// Draw map
	this->map.render(*target);

	// Draw the pause menu
	if (this->paused)
	{
		this->pauseMenu->render(*target);
	}
}