#pragma once

#include <iostream>
#include <ctime>
#include <cstdlib>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>

class HitboxComponent
{
private:
	// Variables
	sf::Sprite& sprite;
	sf::RectangleShape hitbox;
	float offsetX;
	float offsetY;

public:
	// Constructor/Destructor
	HitboxComponent(sf::Sprite& sprite, 
		float offsetX, float offsetY, 
		float width, float height);
	virtual ~HitboxComponent();

	// Functions
	bool checkIntersect(const sf::FloatRect& rect);

	void update();
	void render(sf::RenderTarget& target);
};

