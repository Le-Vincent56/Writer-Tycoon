#include "Entity.h"

// Initializer Functions
void Entity::initVariables()
{
	this->movementComponent = nullptr;
}

// Constructor/Destructor
Entity::Entity()
{
	this->initVariables();
}

Entity::~Entity()
{
	delete this->movementComponent;
}

// Component Functions
void Entity::setTexture(sf::Texture& texture)
{
	// Set the texture for the sprite
	this->sprite.setTexture(texture);
}

void Entity::createMovementComponent(const float coeffOfFriction, const float maxSpeed)
{
	this->movementComponent = new MovementComponent(this->sprite, coeffOfFriction, maxSpeed);
}

// Functions
void Entity::setPosition(const float x, const float y)
{
	// Set the position of the sprite
	this->sprite.setPosition(x, y);
}

void Entity::render(sf::RenderTarget* target)
{
	// Draw the sprite
	target->draw(this->sprite);
}
