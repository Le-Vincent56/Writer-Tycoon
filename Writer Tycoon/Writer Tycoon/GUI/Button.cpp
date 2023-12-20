#include "Button.h"

// Constructor/Destructor
Button::Button(float x, float y, float width, float height,
	sf::Font& font, std::string text, unsigned int textSize,
	sf::Color textIdleColor, sf::Color textHoverColor, sf::Color textActiveColor,
	sf::Texture& buttonIdleTexture, sf::Texture& buttonActiveTexture)
	: font(font), buttonIdleTexture(buttonIdleTexture), buttonActiveTexture(buttonActiveTexture)
{
	// Set button state
	this->buttonState = BTN_IDLE;

	// Set position and size
	this->shape.setPosition(sf::Vector2f(x, y));
	this->shape.setSize(sf::Vector2f(width, height));

	// Set textures
	this->buttonIdleTexture = buttonIdleTexture;
	this->buttonIdleColor = sf::Color(255, 255, 255, 255);
	this->buttonHoverColor = sf::Color(180, 180, 180, 255);;
	this->buttonActiveTexture = buttonActiveTexture;
	this->shape.setTexture(&this->buttonIdleTexture);

	// Set font and text
	this->font = font;
	this->text.setFont(this->font);
	this->text.setString(text);
	this->text.setFillColor(sf::Color::White);
	this->text.setCharacterSize(textSize);

	// Center the text
	this->text.setPosition(
		this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.0f) 
			- this->text.getGlobalBounds().width / 2.0f,
		this->shape.getPosition().y + (this->shape.getGlobalBounds().height / 2.0f) 
			- this->text.getGlobalBounds().height * 1.125
	);

	// Set colors
	this->textIdleColor = textIdleColor;
	this->textHoverColor = textHoverColor;
	this->textActiveColor = textActiveColor;
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
void Button::update(const sf::Vector2f& mousePosView)
{
	// Set the button to idle
	this->buttonState = BTN_IDLE;

	// Check if the mouse is hovering over the button
	if (this->shape.getGlobalBounds().contains(mousePosView))
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
			this->shape.setTexture(&this->buttonIdleTexture);
			this->text.setFillColor(this->textIdleColor);
			this->shape.setFillColor(this->buttonIdleColor);
			break;

		case BTN_HOVER:
			this->shape.setTexture(&this->buttonIdleTexture);
			this->text.setFillColor(this->textHoverColor);
			this->shape.setFillColor(this->buttonHoverColor);
			
			break;

		case BTN_ACTIVE:
			this->shape.setTexture(&this->buttonActiveTexture);
			this->text.setFillColor(this->textActiveColor);
			this->shape.setFillColor(this->buttonIdleColor);
			break;

		default:
			this->shape.setFillColor(sf::Color::Red);
			break;
	}
}

void Button::render(sf::RenderTarget& target)
{
	// Draw the shape and the text
	target.draw(this->shape);
	target.draw(this->text);
}
