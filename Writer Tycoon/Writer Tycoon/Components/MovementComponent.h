#pragma once

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <vector>
#include <stack>
#include <map>

#include "../Utils/VectorUtils.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>

class MovementComponent
{
private:
	// Variables
	sf::Sprite& sprite;

	float accelAmount;
	float decelAmount;

	float maxSpeed;
	float coeffOfFriction;
	sf::Vector2f position;
	sf::Vector2f acceleration;
	sf::Vector2f direction;
	sf::Vector2f velocity;

	// Initializer Functions
	void initVariables();

public:
	// Constructor/Destructor
	MovementComponent(sf::Sprite& sprite, float coeffOfFriction, float maxSpeed);
	virtual ~MovementComponent();

	// Accessors
	const sf::Vector2f& getVelocity() const;
	const sf::Vector2f& getDirection() const;

	// Functions
	void applyForce(sf::Vector2f force);
	void setDirectionX(float x);
	void setDirectionY(float y);
	void move(float lerpAmount);
	void update(const float& dt);
};

