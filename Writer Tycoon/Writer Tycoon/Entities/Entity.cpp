#include "Entity.h"

Entity::Entity()
{
	this->shape.setSize(sf::Vector2f(50.0f, 50.0f));
	this->shape.setFillColor(sf::Color::White);
	this->movementSpeed = 100.0f;
}

Entity::~Entity()
{
}

void Entity::move(const float& dt, const float xDir, const float yDir)
{
	this->shape.move(xDir * this->movementSpeed * dt, yDir * this->movementSpeed * dt);
}

void Entity::update(const float& dt)
{
	
}

void Entity::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}
