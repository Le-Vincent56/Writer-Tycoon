#include "Player.h"

// Initializer Functions
void Player::initVariables()
{
}

void Player::initComponents()
{
	
}

// Constructor/Destructor
Player::Player(float x, float y, sf::Texture& textureSheet)
{
	// Initialize
	this->initVariables();

	// Set the position
	this->setPosition(x, y);

	// Create components
	this->createMovementComponent(10.0f, 300.0f);
	this->createAnimationComponent(textureSheet);

	this->animationComponent->addAnimation("IDLE_DOWN", 1.0f, 0, 0, 5, 0, 16, 32);
	this->animationComponent->addAnimation("IDLE_LEFT", 1.0f, 0, 1, 5, 1, 16, 32);
	this->animationComponent->addAnimation("IDLE_RIGHT", 1.0f, 0, 2, 5, 2, 16, 32);
	this->animationComponent->addAnimation("IDLE_UP", 1.0f, 0, 3, 5, 3, 16, 32);
	
	this->animationComponent->addAnimation("RUN_DOWN", 1.0f, 0, 4, 5, 4, 16, 32);
	this->animationComponent->addAnimation("RUN_LEFT", 1.0f, 0, 5, 5, 5, 16, 32);
	this->animationComponent->addAnimation("RUN_RIGHT", 1.0f, 0, 6, 5, 6, 16, 32);
	this->animationComponent->addAnimation("RUN_UP", 1.0f, 0, 7, 5, 7, 16, 32);

	// Rescale the player
	this->sprite.setScale(2, 2);
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
}

void Player::update(const float& dt)
{
	// Check for movement component
	if (this->movementComponent)
	{
		// Update movement
		this->movementComponent->update(dt);
	}

	// Check for animation component
	if (this->animationComponent && this->movementComponent)
	{
		// Get movement statse
		PLAYER_DIR currentState = this->movementComponent->getCurrentState();
		PLAYER_DIR lastState = this->movementComponent->getLastState();

		if (currentState == PLAYER_DIR::IDLE)
		{
			switch (lastState)
			{
				case PLAYER_DIR::DOWN:
					this->animationComponent->play("IDLE_DOWN", dt);
					break;

				case PLAYER_DIR::LEFT:
					this->animationComponent->play("IDLE_LEFT", dt);
					break;

				case PLAYER_DIR::RIGHT:
					this->animationComponent->play("IDLE_RIGHT", dt);
					break;

				case PLAYER_DIR::UP:
					this->animationComponent->play("IDLE_UP", dt);
					break;
			}
		}
		else
		{
			if (currentState == PLAYER_DIR::DOWN)
			{
				this->animationComponent->play("RUN_DOWN", dt);
			}

			if (currentState == PLAYER_DIR::LEFT)
			{
				this->animationComponent->play("RUN_LEFT", dt);
			}

			if (currentState == PLAYER_DIR::RIGHT)
			{
				this->animationComponent->play("RUN_RIGHT", dt);
			}

			if (currentState == PLAYER_DIR::UP)
			{
				this->animationComponent->play("RUN_UP", dt);
			}
		}

	}
}
