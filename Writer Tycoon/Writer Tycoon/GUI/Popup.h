#pragma once

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <sstream>

#include "Button.h"
#include "Dropdown.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

class Popup
{
private:
	sf::RectangleShape shape;

	sf::Font& font;
	sf::Text text;
	sf::Texture& frameTexture;

	std::vector<sf::Text*> texts;
	std::vector<Button*> buttons;
	std::vector<Dropdown*> dropdowns;

	bool enabled;

public:
	// Constructor/Destructor
	Popup(float x, float y, float width, float height,
		sf::Font& font, sf::Texture& frameTexture);
	virtual ~Popup();

	// Accessors
	const bool getEnabled() const;

	// Modifiers
	const void addItem(sf::Text* text, float localX, float localY);
	const void addItem(Button* button, float localX, float localY);
	const void addItem(Dropdown* dropdown, float localX, float localY);
	const void setEnabled(const bool enabled);

	// Functions
	void updateEvents(sf::Event& sfEvent, const sf::Vector2f& mousePosView);
	void update(const float& dt, const sf::Vector2f& mousePosView);
	void render(sf::RenderTarget& target);
};

