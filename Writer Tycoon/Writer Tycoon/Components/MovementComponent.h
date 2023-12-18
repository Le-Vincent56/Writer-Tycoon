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

	float maxVelocity;
	float coeffOfFriction;
	sf::Vector2f position;
	sf::Vector2f acceleration;
	sf::Vector2f direction;
	sf::Vector2f velocity;

	// Initializer Functions

public:
	// Constructor/Destructor
	MovementComponent(sf::Sprite& sprite, float coeffOfFriction, float maxVelocity);
	virtual ~MovementComponent();

	// Accessors
	const sf::Vector2f& getVelocity() const;

	// Functions
	void applyForce(sf::Vector2f force);
	void applyFriction();
	void setDirection(sf::Vector2f direction);
	void update(const float& dt);
};

