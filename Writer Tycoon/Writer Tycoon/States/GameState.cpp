#include "GameState.h"

// Initializer Functions
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

void GameState::initTextures()
{
	// Load player sprite
	if (!this->textures["PLAYER_SHEET"].loadFromFile("Assets/Sprites/Player/player_sprite_sheet.png"))
	{
		throw "ERROR::GAME_STATE_::COULD_NOT_LOAD_PLAYER_SPRITE_SHEET_TEXTURE";
	}
}

void GameState::initEntities()
{
	this->player = new Player(0, 0, this->textures["PLAYER_SHEET"]);
}

// Constructor/Destructor
GameState::GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	: State(window, supportedKeys, states)
{
	this->initKeybinds();
	this->initTextures();
	this->initEntities();
}

GameState::~GameState()
{
	delete this->player;
}

// Functions
void GameState::updateInput(const float& dt)
{
	this->player->updateInput(this->keybinds, dt);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))))
		this->endState();
}

void GameState::update(const float& dt)
{
	// Update mouse positions
	this->updateMousePositions();

	// Update input
	this->updateInput(dt);

	// Update player
	this->player->update(dt);
}

void GameState::render(sf::RenderTarget* target)
{
	// If nothing bound to target, set it to this window
	if (!target)
		target = this->window;

	this->player->render(*target);
}