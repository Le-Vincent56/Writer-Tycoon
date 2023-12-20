#pragma once

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <vector>
#include <stack>
#include <map>

#include "Button.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>

class PauseMenu
{
private:
	sf::Font& font;
	sf::Texture& buttonIdleTexture;
	sf::Texture& buttonActiveTexture;

	sf::Text menuText;
	sf::RectangleShape background;
	sf::RectangleShape container;

	std::map<std::string, Button*> buttons;

public:
	// Constructor/Destructor
	PauseMenu(sf::RenderWindow& window, sf::Font& font,
		sf::Texture& buttonIdleTexture, sf::Texture& buttonActiveTexture);
	virtual ~PauseMenu();

	// Accessor
	std::map<std::string, Button*>& getButtons();
	const sf::Vector2f& getContainerCenterBelowText() const;
	const bool isButtonPressed(const std::string key);

	// Functions
	void addButton(const std::string key, const std::string text,
		float x, float y, float width, float height);
	void updateButtons(const sf::Vector2f& mousePosView);
	void update(const sf::Vector2f& mousePosView);
	void render(sf::RenderTarget& target);
};

