#include "MovementComponent.h"

// Initializer Functions
void MovementComponent::initVariables()
{
	accelAmount = 20.0f;
	decelAmount = 20.0f;
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
const sf::Vector2f& MovementComponent::getVelocity() const
{
	return this->velocity;
}

const sf::Vector2f& MovementComponent::getDirection() const
{
	return this->direction;
}

// Functions
void MovementComponent::applyForce(sf::Vector2f force)
{
	this->acceleration += force;
}

void MovementComponent::setDirectionX(float x)
{
	this->direction.x = x;
}

void MovementComponent::setDirectionY(float y)
{
	this->direction.y = y;
}

void MovementComponent::move(float lerpAmount)
{
	// Retrieve target speed
	sf::Vector2f targetSpeed = VectorUtils::mult(this->direction, this->maxSpeed);
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
	// Move the entity
	this->move(0.5f);

	// Get the current position
	this->position = this->sprite.getPosition();

	// Set velocity and position
	this->velocity += acceleration * dt;
	this->position += this->velocity * dt;

	// Set sprite position
	this->sprite.setPosition(this->position);

	// Reset acceleration
	this->acceleration = sf::Vector2f(0.0f, 0.0f);
}
