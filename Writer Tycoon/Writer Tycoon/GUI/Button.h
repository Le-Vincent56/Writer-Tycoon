#pragma once

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <sstream>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

enum button_states { 
	BTN_IDLE = 0,
	BTN_ACTIVE = 1,
	BTN_ACTIVE_FUNCTION = 2
};

class Button
{
private:
	// Variables
	short unsigned int id;

	float clickBufferMax;
	float clickBuffer;

	short unsigned int buttonState;

	sf::RectangleShape shape;

	sf::Font& font;
	sf::Text text;

	sf::Color textIdleColor;
	sf::Color textHoverColor;
	sf::Color textActiveColor;

	sf::Texture& buttonIdleTexture;
	sf::Color buttonIdleColor;
	sf::Color buttonHoverColor;
	sf::Texture& buttonActiveTexture;

	bool textureOverriden;
	bool hovering;

public:
	// Constructor/Destructor
	Button(float x, float y, float width, float height,
		sf::Font& font, std::string text, unsigned int textSize,
		sf::Color textIdleColor, sf::Color textHoverColor, sf::Color textActiveColor,
		sf::Texture& buttonIdleTexture, sf::Texture& buttonActiveTexture,
		short unsigned int id = 0);
	virtual ~Button();

	// Accessors
	const short unsigned int& getID() const;
	const bool isPressed();
	const std::string getText() const;
	const bool getClickBuffer();

	// Modifiers
	void setID(const short unsigned int id);
	void setText(const std::string text);
	void setButtonTexture(const sf::Texture& texture);
	void setTextureOverride(const bool isOverriding);

	// Functions
	void updateEvents(sf::Event& sfEvent, const sf::Vector2f& mousePosView);
	void updateClickBuffer(const float& dt);
	void update(const float& dt, const sf::Vector2f& mousePosView);
	void render(sf::RenderTarget& target);
};

