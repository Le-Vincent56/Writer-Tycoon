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
	if (!this->buttonIdle.loadFromFile("Assets/Sprites/UI/button_long_idle.png"))
	{
		throw "ERROR::EDITOR_STATE::FAILED_TO_LOAD_BUTTON_LONG_IDLE_TEXTURE";
	}

	if (!this->buttonPressed.loadFromFile("Assets/Sprites/UI/button_long_active.png"))
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


void EditorState::initGUI()
{
}

// Constructor/Destructor
EditorState::EditorState(sf::RenderWindow* window, 
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
}

void EditorState::updateInput(const float& dt)
{
	// Check to end the state
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))))
		this->endState();
}

void EditorState::updateGUI()
{
}

void EditorState::update(const float& dt)
{
	// Update mouse positions
	this->updateMousePositions();

	// Update input
	this->updateInput(dt);

	// Update buttons
	this->updateGUI();
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
}