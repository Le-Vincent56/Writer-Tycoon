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
