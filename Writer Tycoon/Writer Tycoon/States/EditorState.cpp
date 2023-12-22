#include "../stdafx.h"
#include "EditorState.h"

// Initialize Functions
void EditorState::initVariables()
{
	// Set mouse state
	pressingLeft = false;
	pressingRight = false;

	this->textureRect = sf::IntRect(0, 0, 
		static_cast<int>(this->stateData->gridSize),
		static_cast<int>(this->stateData->gridSize)
	);
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
		throw "ERROR::EDITOR_STATE::FAILED_TO_LOAD_BUTTON_LONG_ACTIVE_TEXTURE";
	}

	if (!this->buttonSquareIdleTexture.loadFromFile("Assets/Sprites/UI/button_square_idle.png"))
	{
		throw "ERROR::EDITOR_STATE::FAILED_TO_LOAD_BUTTON_SQUARE_IDLE_TEXTURE";
	}

	if (!this->buttonSquareActiveTexture.loadFromFile("Assets/Sprites/UI/button_square_active.png"))
	{
		throw "ERROR::EDITOR_STATE::FAILED_TO_LOAD_BUTTON_SQUARE_ACTIVE_TEXTURE";
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

void EditorState::initText()
{
	this->cursorText.setFont(this->font);
	this->cursorText.setFillColor(sf::Color::White);
	this->cursorText.setCharacterSize(12);
	this->cursorText.setPosition(this->mousePosView.x, this->mousePosView.y);
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
	// Initialize selector rect
	this->selectorRect.setSize(sf::Vector2f(this->stateData->gridSize, this->stateData->gridSize));
	this->selectorRect.setFillColor(sf::Color(255, 255, 255, 150));
	this->selectorRect.setOutlineThickness(1.0f);
	this->selectorRect.setOutlineColor(sf::Color::Green);

	// Initialize the pause menu
	this->initPauseMenu();

	// Set selector rect texture
	this->selectorRect.setTexture(this->tileMap->getTileSheet());
	this->selectorRect.setTextureRect(this->textureRect);

	// Initialize the texture selector
	this->textureSelector = new TextureSelector(
		20.0f, 20.0f, 500.0f, 500.0f, this->stateData->gridSize, this->tileMap->getTileSheet(),
		this->font, "TS", this->buttonSquareIdleTexture, this->buttonSquareActiveTexture
	);
}

void EditorState::initTileMap()
{
	this->tileMap = new TileMap(this->stateData->gridSize, 10, 10);
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
	this->initText();
	this->initKeybinds();
	this->initTileMap();
	this->initGUI();
}

EditorState::~EditorState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
		it->second = nullptr;
	}

	delete this->pauseMenu;
	this->pauseMenu = nullptr;

	delete this->tileMap;
	this->tileMap = nullptr;
	
	delete this->textureSelector;
	this->textureSelector = nullptr;
}

// Functions
void EditorState::updateEvents(sf::Event& sfEvent)
{
	// Check if paused
	if (this->paused)
	{
		// Update pause menu events
		this->pauseMenu->updateEvents(sfEvent, this->mousePosView);
	}
	else
	{
		// Update texture selecotr events
		this->textureSelector->updateEvents(sfEvent, this->mousePosWindow);

		// Update button events
		for (auto& it : this->buttons)
		{
			it.second->updateEvents(sfEvent, this->mousePosView);
		}

		// Check for adding tiles
		if (sfEvent.type == sf::Event::MouseButtonPressed)
		{
			if (sfEvent.mouseButton.button == sf::Mouse::Left)
			{
				// Check if the mouse is outside the texture selector space
				if (!this->textureSelector->getActive())
				{
					// Set the other to be false
					if (pressingRight)
						pressingRight = false;

					// Detect holding down
					pressingLeft = true;
				}
				else
				{
					// Get the texture rect inside the texture selector
					this->textureRect = this->textureSelector->getTextureRect();
				}
			}
		}

		if (sfEvent.type == sf::Event::MouseButtonReleased)
		{
			if (sfEvent.mouseButton.button == sf::Mouse::Left)
			{
				// Stop holding
				pressingLeft = false;
			}
		}

		// Check for removing tiles
		if (sfEvent.type == sf::Event::MouseButtonPressed)
		{
			if (sfEvent.mouseButton.button == sf::Mouse::Right)
			{
				// Check if the mouse is outside the texture selecor space
				if (!this->textureSelector->getActive())
				{
					// Set the other to be false
					if (pressingLeft)
						pressingLeft = false;

					// Detect holding down
					pressingRight = true;
				}
			}
		}

		if (sfEvent.type == sf::Event::MouseButtonReleased)
		{
			if (sfEvent.mouseButton.button == sf::Mouse::Right)
			{
				// Stop holding
				pressingRight = false;
			}
		}
	}
}

void EditorState::updateEditorInput(const float& dt)
{
	// If the left mouse button is being pressed/held, add a tile at it's position
	if (pressingLeft)
	{
		this->tileMap->addTile(this->textureRect, this->mousePosGrid.x, this->mousePosGrid.y);
	}

	// If the right mouse button is being pressed/held, remove a tile at it's position
	if (pressingRight)
	{
		this->tileMap->removeTile(this->mousePosGrid.x, this->mousePosGrid.y);
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

void EditorState::updateGUI(const float& dt)
{
	// Update texture selector
	this->textureSelector->update(dt, this->mousePosWindow);

	// Check if cursor is outside the texture selector space
	if (!this->textureSelector->getActive())
	{
		// Update selector rect
		this->selectorRect.setPosition(
			this->mousePosGrid.x * this->stateData->gridSize,
			this->mousePosGrid.y * this->stateData->gridSize
		);
		this->selectorRect.setTextureRect(this->textureRect);
	}

	// Update buttons
	for (auto& it : this->buttons)
	{
		it.second->update(dt, this->mousePosView);
	}

	// Update mouse position and data
	this->cursorText.setPosition(this->mousePosView.x + 100, this->mousePosView.y - 50.0f);
	std::stringstream ss;
	ss << this->mousePosView.x << ", " << this->mousePosView.y << "\n"
		<< this->mousePosGrid.x << ", " << this->mousePosGrid.y << "\n"
		<< this->textureRect.left << " " << this->textureRect.top;
	this->cursorText.setString(ss.str());
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
	this->updateGUI(dt);

	// Update keytime
	this->updateKeyTime(dt);

	// Update input
	this->updateInput(dt);

	// Check if paused
	if (!this->paused)
	{
		// Update editor input
		this->updateEditorInput(dt);

		// Update GUI
		this->updateGUI(dt);
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

	// Check if the mouse is outisde the texture selector space
	if (!this->textureSelector->getActive())
	{
		// Draw the selector rect
		target.draw(this->selectorRect);
	}

	// Draw the texture selector
	this->textureSelector->render(target);

	// Draw the cursor text
	target.draw(this->cursorText);
}

void EditorState::render(sf::RenderTarget* target)
{
	// If nothing bound to target, set it to this window
	if (!target)
		target = this->window;

	// Draw map
	this->tileMap->render(*target);

	// Draw GUI
	this->renderGUI(*target);

	// Draw the pause menu
	if (this->paused)
	{
		this->pauseMenu->render(*target);
	}
}