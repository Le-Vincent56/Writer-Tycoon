#include "../stdafx.h"
#include "Entity.h"

// Initializer Functions
void Entity::initVariables()
{
	this->movementComponent = nullptr;
	this->animationComponent = nullptr;
	this->hitboxComponent = nullptr;
}

// Constructor/Destructor
Entity::Entity()
{
	this->initVariables();
}

Entity::~Entity()
{
	delete this->movementComponent;
	this->movementComponent = nullptr;
	delete this->animationComponent;
	this->animationComponent = nullptr;
	delete this->hitboxComponent;
	this->hitboxComponent = nullptr;
}

// Accessors
const sf::Vector2f& Entity::getPosition() const
{
	// Check if the entity has a hitbox
	if (this->hitboxComponent)
	{
		// If so, return the hitbox's position
		return this->hitboxComponent->getPosition();
	}

	// Otherwise, return the sprite's position
	return this->sprite.getPosition();
}

const sf::Vector2u Entity::getGridPosition(const unsigned gridSize) const
{
	// Check if the entity has a hitbox
	if (this->hitboxComponent)
	{
		// If so, return the hitbox's position
		return sf::Vector2u(
			static_cast<unsigned int>(this->hitboxComponent->getPosition().x) / gridSize,
			static_cast<unsigned int>(this->hitboxComponent->getPosition().y) / gridSize
		);
	}

	// Otherwise, return the sprite's position
	return sf::Vector2u(
		static_cast<unsigned int>(this->sprite.getPosition().x) / gridSize,
		static_cast<unsigned int>(this->sprite.getPosition().y) / gridSize
	);
}

const sf::FloatRect Entity::getGlobalBounds() const
{
	// Check if the entity has a hitbox
	if (this->hitboxComponent)
	{
		// If so, return the hitbox's global bounds
		return this->hitboxComponent->getGlobalBounds();
	}

	// Otherwise, return the sprite's global bounds
	return this->sprite.getGlobalBounds();
}

const sf::FloatRect& Entity::getNextPositionBounds(const float& dt) const
{
	// Check if the entity has a hitbox and a movement component
	if (this->hitboxComponent && this->movementComponent)
	{
		// Return the next position of the hitbox using the current velocity
		return this->hitboxComponent->getNextPosition(this->movementComponent->getVelocity() * dt);
	}

	// Otherwise, return a default float rect
	return sf::FloatRect();
}

const sf::Vector2f& Entity::getVelocity() const
{
	// Check if the entity has a movement component
	if (this->movementComponent)
	{
		// If so, return the component's velocity
		return this->movementComponent->getVelocity();
	}

	// Otherwise, return a zero vector
	return sf::Vector2f(0, 0);
}

// Modifiers
void Entity::setPosition(const float x, const float y)
{
	// Check if the entity has a hitbox
	if (this->hitboxComponent)
	{
		// If so, set the position of the hitbox
		this->hitboxComponent->setPosition(x, y);
	}
	else
	{
		// Otherwise, set the position of the sprite
		this->sprite.setPosition(x, y);
	}
}

// Component Functions
void Entity::setTexture(sf::Texture& texture)
{
	// Set the texture for the sprite
	this->sprite.setTexture(texture);
}

void Entity::setVelocity(const float x, const float y)
{
	// Check if the entity has a movement component
	if (this->movementComponent)
	{
		// Set the velocity of the entity
		this->movementComponent->setVelocity(x, y);
	}
}

void Entity::createMovementComponent(const float coeffOfFriction, const float maxSpeed)
{
	this->movementComponent = new MovementComponent(this->sprite, coeffOfFriction, maxSpeed);
}

void Entity::createAnimationComponent(sf::Texture& textureSheet)
{
	this->animationComponent = new AnimationComponent(this->sprite, textureSheet);
}

void Entity::createHitboxComponent(sf::Sprite& sprite,
	const float offsetX, const float offsetY,
	float width, float height)
{
	this->hitboxComponent = new HitboxComponent(sprite, offsetX, offsetY, width, height);
}