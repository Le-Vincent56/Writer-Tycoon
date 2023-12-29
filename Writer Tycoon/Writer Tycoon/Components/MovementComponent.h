#pragma once

#include "../Utils/VectorUtils.h"

enum PLAYER_DIR
{
	IDLE = 0,
	DOWN = 1,
	LEFT = 2,
	RIGHT = 3,
	UP = 4
};

class MovementComponent
{
private:
	// Variables
	sf::Sprite& sprite;

	bool locked;
	float idleBuffer;

	float accelAmount;
	float decelAmount;

	float maxSpeed;
	float coeffOfFriction;
	sf::Vector2f position;
	sf::Vector2f acceleration;
	sf::Vector2f direction;
	sf::Vector2f velocity;

	PLAYER_DIR currentState;
	PLAYER_DIR lastState;

	// Initializer Functions
	void initVariables();

public:
	// Constructor/Destructor
	MovementComponent(sf::Sprite& sprite, float coeffOfFriction, float maxSpeed);
	~MovementComponent();

	// Accessors
	const float& getMaxSpeed() const;
	const sf::Vector2f& getVelocity() const;
	const PLAYER_DIR& getCurrentState() const;
	const PLAYER_DIR& getLastState() const;

	// Modifiers
	void setDirectionX(float x);
	void setDirectionY(float y);
	void setVelocity(const float x, const float y);

	// Functions
	void applyForce(sf::Vector2f force);
	void updateMovementMap();
	void move(float lerpAmount);
	void update(const float& dt);
};

