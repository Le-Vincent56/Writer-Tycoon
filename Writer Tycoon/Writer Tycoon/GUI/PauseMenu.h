#pragma once

#include "Button.h"

// Forward Declaration
class Button;

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
	~PauseMenu();

	// Accessor
	std::map<std::string, Button*>& getButtons();
	const sf::Vector2f& getContainerCenterBelowText() const;
	const bool isButtonPressed(const std::string key);

	// Functions
	void updateEvents(sf::Event& sfEvent, const sf::Vector2f& mousePosView);
	void addButton(const std::string key, const std::string text,
		float x, float y, float width, float height);
	void updateButtons(const float& dt, const sf::Vector2f& mousePosView);
	void update(const float& dt, const sf::Vector2f& mousePosView);
	void render(sf::RenderTarget& target);
};

