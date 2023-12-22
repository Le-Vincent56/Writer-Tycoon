#pragma once

#include "Button.h"

// Forward Declarations
class Button;

class Dropdown
{
private:
	// Variables
	float clickBufferMax;
	float clickBuffer;

	sf::Font& font;
	sf::Texture& dropdownIdleTexture;
	sf::Texture& dropdownActiveTexture;

	Button* currentElement;
	std::vector<Button*> elements;

	short unsigned int lastCurrentID;
	bool showElements;

public:
	// Constructor/Destructor
	Dropdown(float x, float y, float width, float height,
		sf::Font& font,
		sf::Texture& dropdownIdleTexture, sf::Texture& dropdownActiveTexture,
		std::string elementNames[],
		unsigned int numOfElements, const unsigned int defaultIndex = 0);
	virtual ~Dropdown();

	// Accesors
	const unsigned short& getCurrentElementID() const;
	const unsigned short& getLastCurrentElementID() const;

	// Functions
	void updateEvents(sf::Event& sfEvent, const sf::Vector2f& mousePosView);
	void update(const float& dt, const sf::Vector2f& mousePosView);
	void render(sf::RenderTarget& target);
};

