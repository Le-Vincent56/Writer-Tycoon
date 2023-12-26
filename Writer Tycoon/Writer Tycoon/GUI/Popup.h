#pragma once

#include "Button.h"
#include "Dropdown.h"

// Forward Declaration
class Button;
class Dropdown;

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
	~Popup();

	// Accessors
	const bool getEnabled() const;

	// Modifiers
	const void addItem(sf::Text* text, float localX, float localY);
	const void addItem(Button* button, float localX, float localY);
	const void addItem(Dropdown* dropdown, float localX, float localY);
	const void setEnabled(const bool enabled);

	// Functions
	void updateEvents(sf::Event& sfEvent, const sf::Vector2i& mousePosWindow);
	void update(const float& dt, const sf::Vector2i& mousePosWindow);
	void render(sf::RenderTarget& target);
};

