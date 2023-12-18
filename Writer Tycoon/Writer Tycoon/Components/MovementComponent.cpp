#include "MovementComponent.h"

// Constructor/Destructor
MovementComponent::MovementComponent(sf::Sprite& sprite, float coeffOfFriction, float maxVelocity)
	: sprite(sprite), maxVelocity(maxVelocity), coeffOfFriction(coeffOfFriction)
{
}

MovementComponent::~MovementComponent()
{
}

// Accessors
const sf::Vector2f& MovementComponent::getVelocity() const
{
	return this->velocity;
}

// Functions
void MovementComponent::applyForce(sf::Vector2f force)
{
	this->acceleration += force;
}

void MovementComponent::applyFriction()
{
	// Declare friction vector
	sf::Vector2f friction = sf::Vector2f(-velocity.x, -velocity.y);

	// Normalize the vector
	friction = VectorUtils::normalize(friction);

	// Multiply by the coefficient of friction
	friction = VectorUtils::mult(friction, coeffOfFriction);

	// Apply the force
	applyForce(friction);
}

void MovementComponent::setDirection(sf::Vector2f direction)
{
	this->direction = direction;
	std::cout << "Direction: " << "(" << this->direction.x << ", " << this->direction.y << ")" << "\n";
}

void MovementComponent::update(const float& dt)
{
	// Apply friction
	this->applyFriction();

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
