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

// Functions
void Entity::setPosition(const float x, const float y)
{
	// Set the position of the sprite
	this->sprite.setPosition(x, y);
}

void Entity::render(sf::RenderTarget& target)
{
	// Draw the sprite
	target.draw(this->sprite);

	// Check if there is a hitbox component
	if (this->hitboxComponent)
	{
		// Render the target
		this->hitboxComponent->render(target);
	}
}
