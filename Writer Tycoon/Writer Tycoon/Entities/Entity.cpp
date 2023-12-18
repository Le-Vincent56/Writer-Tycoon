#include "Entity.h"

// Initializer Functions
void Entity::initVariables()
{
	this->texture = nullptr;
	this->sprite = nullptr;
	this->movementSpeed = 100.0f;
}

// Constructor/Destructor
Entity::Entity()
{
	this->initVariables();
}

Entity::~Entity()
{
	delete this->sprite;
}

// Component Functions
void Entity::createSprite(sf::Texture* texture)
{
	// Set the texture for the sprite
	this->texture = texture;
	this->sprite->setTexture(*this->texture);
}

// Functions
void Entity::move(const float& dt, const float xDir, const float yDir)
{
	// Check if a sprite exists
	if (this->sprite)
	{
		// Move the sprite
		this->sprite->move(xDir * this->movementSpeed * dt, yDir * this->movementSpeed * dt);
	}
}

void Entity::update(const float& dt)
{
	
}

void Entity::render(sf::RenderTarget* target)
{
	// Check if the sprite exists
	if (this->sprite)
	{
		// Draw the sprite
		target->draw(*this->sprite);
	}
}
