#include "../stdafx.h"
#include "MovementComponent.h"

// Initializer Functions
void MovementComponent::initVariables()
{
	locked = false;
	idleBuffer = 30.0f;
	accelAmount = 40.0f;
	decelAmount = 40.0f;
}

// Constructor/Destructor
MovementComponent::MovementComponent(sf::Sprite& sprite, float coeffOfFriction, float maxSpeed)
	: sprite(sprite), maxSpeed(maxSpeed), coeffOfFriction(coeffOfFriction)
{
	// Initialize variables
	this->initVariables();
}

MovementComponent::~MovementComponent()
{
}

// Accessors
const float& MovementComponent::getMaxSpeed() const
{
	return this->maxSpeed;
}

const sf::Vector2f& MovementComponent::getVelocity() const
{
	return this->velocity;
}

const PLAYER_DIR& MovementComponent::getCurrentState() const
{
	return this->currentState;
}

const PLAYER_DIR& MovementComponent::getLastState() const
{
	return this->lastState;
}

// Modifiers
void MovementComponent::setDirectionX(float x)
{
	this->direction.x = x;
}

void MovementComponent::setDirectionY(float y)
{
	this->direction.y = y;
}

void MovementComponent::setVelocity(const float x, const float y)
{
	this->velocity.x = x;
	this->velocity.y = y;
}

// Functions
void MovementComponent::applyForce(sf::Vector2f force)
{
	this->acceleration += force;
}

void MovementComponent::updateMovementMap()
{
	// Check if the player is idle
	if ((this->velocity.x < idleBuffer && this->velocity.x > -idleBuffer) && (this->velocity.y < idleBuffer && this->velocity.y > -idleBuffer))
	{
		this->currentState = PLAYER_DIR::IDLE;
	}

	// Check if the player is moving down
	if (this->direction.y == 1.0f)
	{
		this->currentState = PLAYER_DIR::DOWN;
		lastState = PLAYER_DIR::DOWN;
	}

	// Check if the player is moving left
	if (this->direction.x == -1.0f)
	{
		this->currentState = PLAYER_DIR::LEFT;
		lastState = PLAYER_DIR::LEFT;
	}

	// Check if the player is moving right
	if (this->direction.x == 1.0f)
	{
		this->currentState = PLAYER_DIR::RIGHT;
		lastState = PLAYER_DIR::RIGHT;
	}

	// Check if the player is moving up
	if (this->direction.y == -1.0f)
	{
		this->currentState = PLAYER_DIR::UP;
		lastState = PLAYER_DIR::UP;
	}
}

void MovementComponent::move(float lerpAmount)
{
	// Retrieve target speed
	sf::Vector2f targetSpeed = VectorUtils::mult(VectorUtils::normalize(this->direction), this->maxSpeed);
	targetSpeed = VectorUtils::lerp(this->velocity, targetSpeed, lerpAmount);

	// Calculate acceleration rate
	float accelRate = (std::abs(std::hypot(targetSpeed.x, targetSpeed.y)) > 0.01f) ? this->accelAmount : this->decelAmount;

	// Calculate speed difference
	sf::Vector2f speedDiff =  targetSpeed - this->velocity;

	// Calculate force for player
	sf::Vector2f movement = VectorUtils::mult(speedDiff, accelRate);

	// Apply the force
	this->applyForce(movement);
}

void MovementComponent::update(const float& dt)
{
	// Check if the player is locked
	if (!locked)
	{
		// Move the entity
		this->move(0.5f);

		// Get the current position
		this->position = this->sprite.getPosition();

		// Set velocity and position
		this->velocity += this->acceleration * dt;
		this->position += this->velocity * dt;

		// Set sprite position
		this->sprite.setPosition(this->position);

		// Update movement map
		updateMovementMap();

		// Reset acceleration
		this->acceleration = sf::Vector2f(0.0f, 0.0f);
	}
}
