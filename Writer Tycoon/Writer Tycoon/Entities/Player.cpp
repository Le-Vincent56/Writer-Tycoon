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
	bool keyPressed = false;

	// Update player input
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_UP"))))
	{
		this->movementComponent->applyForce(sf::Vector2f(0.0f, -50.0f));
		this->movementComponent->setDirection(sf::Vector2f(0.0f, -1.0f));
		keyPressed = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_LEFT"))))
	{
		this->movementComponent->applyForce(sf::Vector2f(-50.0f, 0.0f));
		this->movementComponent->setDirection(sf::Vector2f(-1.0f, 0.0f));
		keyPressed = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_DOWN"))))
	{
		this->movementComponent->applyForce(sf::Vector2f(0.0f, 50.0f));
		this->movementComponent->setDirection(sf::Vector2f(0.0f, 1.0f));
		keyPressed = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_RIGHT"))))
	{
		this->movementComponent->applyForce(sf::Vector2f(50.0f, 0.0f));
		this->movementComponent->setDirection(sf::Vector2f(1.0f, 0.0f));
		keyPressed = true;
	}
	
	// If no key is pressed, set no direction
	if (!keyPressed)
	{
		this->movementComponent->setDirection(sf::Vector2f(0.0f, 0.0f));
	}
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
