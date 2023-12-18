#pragma once

#include "../Components/MovementComponent.h"

class Entity
{
private:
	void initVariables();

protected:
	sf::Sprite sprite;

	MovementComponent* movementComponent;

public:
	// Constructor/Destructor
	Entity();
	virtual ~Entity();

	// Component Functions
	void setTexture(sf::Texture& texture);
	void createMovementComponent(const float deceleration, const float maxVelocity);

	// Functions
	virtual void setPosition(const float x, const float y);

	virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderTarget* target);
};

