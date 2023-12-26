#include "../stdafx.h"
#include "EditorState.h"

// Initialize Functions
void EditorState::initView()
{
	// Set the view size to the current resolution
	this->view.setSize(
		sf::Vector2f(
			this->stateData->gSettings->resolution.width,
			this->stateData->gSettings->resolution.height)
	);

	// Set the view center to the center of the current resolution
	this->view.setCenter(
		this->stateData->gSettings->resolution.width / 2.0f,
		this->stateData->gSettings->resolution.height / 2.0f
	);
}


void EditorState::initVariables()
{
	// Set mouse state
	pressingLeft = false;
	pressingRight = false;

	// Set texture rect
	this->textureRect = sf::IntRect(0, 0, 
		static_cast<int>(this->stateData->gridSize),
		static_cast<int>(this->stateData->gridSize)
	);

	// Set tile variables
	this->collision = false;
	this->type = TileType::DEFAULT;

	// Set camera speed
	this->cameraSpeed = 100.0f;
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

	// Close the file stream
	ifs.close();

	sf::Keyboard::Key;
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

	this->pauseMenu->addButton("RESUME", "RESUME",
		buttonCenterX, windowCenterY + buttonCenterY,
		buttonWidth, buttonHeight
	);

	this->pauseMenu->addButton("SAVE", "SAVE",
		buttonCenterX, windowCenterY + (buttonCenterY * 2.0),
		buttonWidth, buttonHeight
	);

	this->pauseMenu->addButton("LOAD", "LOAD",
		buttonCenterX, windowCenterY + (buttonCenterY * 3.0),
		buttonWidth, buttonHeight
	);

	this->pauseMenu->addButton("SETTINGS", "SETTINGS",
		buttonCenterX, windowCenterY + (buttonCenterY * 4.0),
		buttonWidth, buttonHeight
	);

	this->pauseMenu->addButton("EXIT", "MAIN MENU",
		buttonCenterX, windowCenterY + (buttonCenterY * 5.0),
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
	
	// Initialize sidebar
	this->sidebar.setSize(sf::Vector2f(80.0f,
		static_cast<float>(this->stateData->gSettings->resolution.height)));
	this->sidebar.setFillColor(sf::Color(50, 50, 50, 100));
	this->sidebar.setOutlineThickness(1.0f);
	this->sidebar.setOutlineColor(sf::Color(200, 200, 200, 150));

	// Initialize the texture selector
	this->textureSelector = new TextureSelector(
		20.0f, 20.0f, 500.0f, 500.0f, this->stateData->gridSize, this->tileMap->getTileSheet(),
		this->font, "TS", this->buttonSquareIdleTexture, this->buttonSquareActiveTexture
	);
}

void EditorState::initTileMap()
{
	this->tileMap = new TileMap(this->stateData->gridSize, 10, 10, "Assets/Images/tilesheet1.png");
}

// Constructor/Destructor
EditorState::EditorState(StateData* stateData)
	: State(stateData)
{
	// Initialize variables
	this->initView();
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
		this->pauseMenu->updateEvents(sfEvent, this->mousePosWindow);
	}
	else
	{
		// Update texture selecotr events
		this->textureSelector->updateEvents(sfEvent, this->mousePosWindow);

		// Update button events
		for (auto& it : this->buttons)
		{
			it.second->updateEvents(sfEvent, this->mousePosWindow);
		}

		// Check for adding tiles
		if (sfEvent.type == sf::Event::MouseButtonPressed)
		{
			if (sfEvent.mouseButton.button == sf::Mouse::Left)
			{
				// Check if the mouse is outside the texture selector space
				if (!this->textureSelector->getActive() && 
					!this->sidebar.getGlobalBounds().contains(
					sf::Vector2f(this->mousePosWindow)))
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

		// Reset on release
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
				// Check if the mouse is outside the texture selector space
				if (!this->textureSelector->getActive() &&
					!this->sidebar.getGlobalBounds().contains(
						sf::Vector2f(this->mousePosWindow)))
				{
					// Set the other to be false
					if (pressingLeft)
						pressingLeft = false;

					// Detect holding down
					pressingRight = true;
				}
			}
		}

		// Reset on release
		if (sfEvent.type == sf::Event::MouseButtonReleased)
		{
			if (sfEvent.mouseButton.button == sf::Mouse::Right)
			{
				// Stop holding
				pressingRight = false;
			}
		}

		// Check for changing type
		if (sfEvent.type == sf::Event::MouseWheelScrolled)
		{
			if (sfEvent.mouseWheelScroll.delta > 0)
			{
				// TODO: Limit to max height
				this->type++;
			}
			else if (sfEvent.mouseWheelScroll.delta < 0)
			{
				// Check if greater than 0 - stay within the positive bounds of the
				// enum
				if (this->type > 0)
				{
					this->type--;
				}
			}
		}
	}
}

void EditorState::updateEditorInput(const float& dt)
{
	// If the left mouse button is being pressed/held, add a tile at it's position
	if (pressingLeft)
	{
		this->tileMap->addTile(this->textureRect, this->mousePosGrid.x, this->mousePosGrid.y, 0, this->collision, this->type);
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

	// Toggle collision
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("TOGGLE_COLLISION"))) && this->getCanPressKey())
	{
		// Toggle collision
		this->collision = !this->collision;
	}

	// Move view
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_CAMERA_UP"))))
	{
		this->view.move(0.0f, -this->cameraSpeed * dt);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_CAMERA_LEFT"))))
	{
		this->view.move(-this->cameraSpeed * dt, 0.0f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_CAMERA_DOWN"))))
	{
		this->view.move(0.0f, this->cameraSpeed * dt);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_CAMERA_RIGHT"))))
	{
		this->view.move(this->cameraSpeed * dt, 0.0f);
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
		it.second->update(dt, this->mousePosWindow);
	}

	// Update mouse position and data
	this->cursorText.setPosition(this->mousePosView.x + 100, this->mousePosView.y - 50.0f);
	std::stringstream ss;
	ss << this->mousePosView.x << ", " << this->mousePosView.y << "\n"
		<< this->mousePosGrid.x << ", " << this->mousePosGrid.y << "\n"
		<< this->textureRect.left << " " << this->textureRect.top << "\n"
		<< "Collision: " << this->collision << "\n"
		<< "Type: " << this->type << "\n";
	this->cursorText.setString(ss.str());
}

void EditorState::updatePauseMenuButtons()
{
	// Resume state
	if (this->pauseMenu->isButtonPressed("RESUME"))
	{
		this->unpauseState();
	}

	// Save
	if (this->pauseMenu->isButtonPressed("SAVE"))
	{
		this->tileMap->saveToFile("TestSave.wtmp");
	}

	// Load
	if (this->pauseMenu->isButtonPressed("LOAD"))
	{
		this->tileMap->loadFromFile("TestSave.wtmp");
	}

	// Settings state
	if (this->pauseMenu->isButtonPressed("SETTINGS"))
	{
		this->states->push(new SettingsState(this->stateData));
	}

	// Exit state
	if (this->pauseMenu->isButtonPressed("EXIT"))
	{
		this->endState();
	}
}

void EditorState::update(const float& dt)
{
	// Update mouse positions
	this->updateMousePositions(&this->view);

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
		this->pauseMenu->update(dt, this->mousePosWindow);

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
		// Set to the editor view
		target.setView(this->view);

		// Draw the selector rect
		target.draw(this->selectorRect);
	}

	// Draw the texture selector
	target.setView(this->window->getDefaultView());
	this->textureSelector->render(target);

	// Draw the side bar
	target.draw(this->sidebar);

	// Draw the cursor text
	target.setView(this->view);
	target.draw(this->cursorText);
}

void EditorState::render(sf::RenderTarget* target)
{
	// If nothing bound to target, set it to this window
	if (!target)
		target = this->window;

	// Set the editor view for tile map calculations
	target->setView(this->view);

	// Draw map
	this->tileMap->render(*target);

	// Revert to default view
	target->setView(this->window->getDefaultView());

	// Draw GUI
	this->renderGUI(*target);

	// Check if paused
	if (this->paused)
	{
		// Revert to default view
		target->setView(this->window->getDefaultView());

		// Render the pause menu
		this->pauseMenu->render(*target);
	}
}