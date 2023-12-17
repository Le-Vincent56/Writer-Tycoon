#include "Button.h"

// Constructor/Destructor
Button::Button(float x, float y, float width, float height,
	sf::Font* font, std::string text, unsigned int textSize,
	sf::Color idleColor, sf::Color hoverColor, sf::Color actveColor)
{
	// Set button state
	this->buttonState = BTN_IDLE;

	// Set position and size
	this->shape.setPosition(sf::Vector2f(x, y));
	this->shape.setSize(sf::Vector2f(width, height));

	// Set font and text
	this->font = font;
	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setFillColor(sf::Color::White);
	this->text.setCharacterSize(textSize);

	// Center the text
	this->text.setPosition(
		this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.0f) - this->text.getGlobalBounds().width / 2.0f,
		this->shape.getPosition().y + (this->shape.getGlobalBounds().height / 2.0f) - this->text.getGlobalBounds().height / 2.0f
	);

	// Set colors
	this->idleColor = idleColor;
	this->hoverColor = hoverColor;
	this->activeColor = activeColor;

	this->shape.setFillColor(this->idleColor);
}

Button::~Button()
{
}

// Accessors
const bool Button::isPressed() const
{
	return this->buttonState == BTN_ACTIVE;
}

// Functions
void Button::update(const sf::Vector2f mousePos)
{
	// Set the button to idle
	this->buttonState = BTN_IDLE;

	// Check if the mouse is hovering over the button
	if (this->shape.getGlobalBounds().contains(mousePos))
	{
		this->buttonState = BTN_HOVER;

		// Check if the button is pressed
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			this->buttonState = BTN_ACTIVE;
		}
	}

	// Set button color
	switch (this->buttonState)
	{
		case BTN_IDLE:
			this->shape.setFillColor(this->idleColor);
			break;

		case BTN_HOVER:
			this->shape.setFillColor(this->hoverColor);
			break;

		case BTN_ACTIVE:
			this->shape.setFillColor(this->activeColor);
			break;

		default:
			this->shape.setFillColor(sf::Color::Red);
			break;
	}
}

void Button::render(sf::RenderTarget* target)
{
	// Draw the shape and the text
	target->draw(this->shape);
	target->draw(this->text);
}
