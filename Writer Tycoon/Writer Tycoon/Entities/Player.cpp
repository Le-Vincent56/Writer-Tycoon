#include "Player.h"

// Initializer Functions
void Player::initVariables()
{
}

void Player::initComponents()
{
	this->createMovementComponent(10.0f, 200.0f);
}

// Constructor/Destructor
Player::Player(float x, float y, sf::Texture& texture)
{
	// Initialize
	this->initVariables();
	this->initComponents();

	// Create the sprite
	this->setTexture(texture);

	// Set the position
	this->setPosition(x, y);
}

Player::~Player()
{
}

// Functions
void Player::updateInput(std::map<std::string, int> keybinds, const float& dt)
{
	// Check vertical movement
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_UP"))) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_DOWN"))))
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_UP"))))
		{
			this->movementComponent->setDirectionY(-1.0f);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_DOWN"))))
		{
			this->movementComponent->setDirectionY(1.0f);
		}
	}
	else 
	{
		this->movementComponent->setDirectionY(0.0f);
	}

	// Check horizontal movement
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_LEFT"))) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_RIGHT"))))
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_LEFT"))))
		{
			this->movementComponent->setDirectionX(-1.0f);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_RIGHT"))))
		{
			this->movementComponent->setDirectionX(1.0f);
		}
	}
	else
	{
		this->movementComponent->setDirectionX(0.0f);
	}

	std::cout << "Direction: " << "(" << this->movementComponent->getDirection().x << ", " << this->movementComponent->getDirection().x << ")" << "\n";
}

void Player::update(const float& dt)
{
	// Check for movement component
	if (this->movementComponent)
	{
		// Update movement
		this->movementComponent->update(dt);
	}
}
