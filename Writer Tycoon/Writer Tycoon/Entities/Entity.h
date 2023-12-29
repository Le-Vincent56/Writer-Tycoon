#pragma once

#include "../Components/MovementComponent.h"
#include "../Components/AnimationComponent.h"
#include "../Components/HitboxComponent.h"

// Forward Declarations
class MovementComponent;
class AnimationComponent;
class HitboxComponent;

class Entity
{
private:
	void initVariables();

protected:
	sf::Sprite sprite;

	MovementComponent* movementComponent;
	AnimationComponent* animationComponent;
	HitboxComponent* hitboxComponent;

public:
	// Constructor/Destructor
	Entity();
	virtual ~Entity();

	// Accessors
	virtual const sf::Vector2f& getPosition() const;
	virtual const sf::Vector2u getGridPosition(const unsigned gridSize) const;
	virtual const sf::FloatRect getGlobalBounds() const;
	virtual const sf::FloatRect getNextPositionBounds(const float& dt) const;
	virtual const sf::Vector2f getVelocity() const;

	// Modifiers
	virtual void setPosition(const float x, const float y);

	// Component Functions
	void setTexture(sf::Texture& texture);
	virtual void setVelocity(const float x, const float y);
	void createMovementComponent(const float deceleration, const float maxSpeed);
	void createAnimationComponent(sf::Texture& textureSheet);
	void createHitboxComponent(sf::Sprite& sprite, 
		const float offsetX, const float offsetY, 
		float width, float height);

	// Functions
	virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderTarget& target) = 0;
};

