#pragma once

#include "Button.h"

class TextureSelector
{
private:
	// Variables
	bool active;
	bool hidden;
	Button* hideButton;
	float gridSize;
	sf::RectangleShape bounds;
	sf::Sprite sheet;
	sf::RectangleShape selector;
	sf::Vector2u mousePosGrid;
	sf::IntRect textureRect;

public:
	// Constructor/Destructor
	TextureSelector(float x, float y, 
		float width, float height, float gridSize, 
		const sf::Texture* textureSheet, sf::Font& font, std::string text,
		sf::Texture& buttonIdleTexture, sf::Texture& buttonActiveTexture);
	~TextureSelector();

	// Accessors
	const bool& getActive() const;
	const sf::IntRect& getTextureRect() const;

	// Functions
	void updateEvents(sf::Event& sfEvent, const sf::Vector2i& mousePosWindow);
	void updateButtons();
	void update(const float& dt, const sf::Vector2i& mousePosWindow);
	void render(sf::RenderTarget& target);
};

