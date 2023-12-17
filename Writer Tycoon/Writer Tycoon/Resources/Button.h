#pragma once

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <sstream>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

enum button_states { BTN_IDLE = 0, BTN_HOVER, BTN_ACTIVE };

class Button
{
private:
	// Variables
	short unsigned int buttonState;

	sf::RectangleShape shape;
	sf::Font* font;
	sf::Text text;

	sf::Color idleColor;
	sf::Color hoverColor;
	sf::Color activeColor;

public:
	// Constructor/Destructor
	Button(float x, float y, float width, float height, 
		sf::Font* font, std::string text, unsigned int textSize,
		sf::Color idleColor, sf::Color hoverColor, sf::Color actveColor);
	virtual ~Button();

	// Accessors
	const bool isPressed() const;

	// Functions
	void update(const sf::Vector2f mousePos);
	void render(sf::RenderTarget* target);
};
