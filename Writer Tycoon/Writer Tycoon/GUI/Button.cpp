#include "../stdafx.h"
#include "Button.h"

// Constructor/Destructor
Button::Button(float x, float y, float width, float height,
	sf::Font& font, std::string text, unsigned int textSize,
	sf::Color textIdleColor, sf::Color textHoverColor, sf::Color textActiveColor,
	sf::Texture& buttonIdleTexture, sf::Texture& buttonActiveTexture,
	short unsigned int id)
	: font(font), buttonIdleTexture(buttonIdleTexture), buttonActiveTexture(buttonActiveTexture),
	textureOverriden(false)
{
	// Set ID
	this->id = id;

	// Set click buffers
	clickBufferMax = 3.0f;
	clickBuffer = clickBufferMax;

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
			- (this->text.getLocalBounds().width / 2.0f),
		this->shape.getPosition().y + (this->shape.getGlobalBounds().height / 2.0f) 
			- (this->text.getCharacterSize() / 1.5f)
	);

	// Set colors
	this->textIdleColor = textIdleColor;
	this->textHoverColor = textHoverColor;
	this->textActiveColor = textActiveColor;

	// Set hovering
	hovering = false;
}

Button::~Button()
{
}

// Accessors
const short unsigned int& Button::getID() const
{
	return this->id;
}

const bool Button::isPressed()
{
	if (this->buttonState == BTN_ACTIVE_FUNCTION)
	{
		// Reset to idle
		this->buttonState = BTN_IDLE;

		return true;
	}

	return false;
}

const std::string Button::getText() const
{
	return this->text.getString();
}

const bool Button::getClickBuffer()
{
	if (this->clickBuffer <= 0)
	{
		this->clickBuffer = clickBufferMax;
		return true;
	}

	return false;
}

// Modifiers
void Button::setEnabled(const bool enabled)
{
	if (enabled)
	{
		this->buttonState = BTN_IDLE;
	}
	else
	{
		this->buttonState = BTN_DISABLED;
	}
}

void Button::setID(const short unsigned int id)
{
	this->id = id;
}

void Button::setText(const std::string text)
{
	this->text.setString(text);
}

void Button::setButtonTexture(const sf::Texture& texture)
{
	this->shape.setTexture(&texture);
}

void Button::setTextureOverride(const bool isOverriding)
{
	this->textureOverriden = isOverriding;
}

void Button::updateEvents(sf::Event& sfEvent, const sf::Vector2f& mousePosView)
{
	// Don't update events if the button is disabled
	if (this->buttonState == BTN_DISABLED)
	{
		return;
	}

	// Detect if the mouse is within bounds and if the button is disabled
	if (this->shape.getGlobalBounds().contains(mousePosView))
	{
		// When the button is pressed, set the active texture
		if (sfEvent.type == sf::Event::MouseButtonPressed)
		{
			if (sfEvent.mouseButton.button == sf::Mouse::Left)
			{
				this->buttonState = BTN_ACTIVE;
			}
		}
		else if (sfEvent.type == sf::Event::MouseButtonReleased)
		{
			if (sfEvent.mouseButton.button == sf::Mouse::Left)
			{
				// Check if the button can be clicked on release
				if (getClickBuffer())
				{
					// If so, activate
					this->buttonState = BTN_ACTIVE_FUNCTION;
				}
				else
				{
					// If not, set back to idle
					this->buttonState = BTN_IDLE;
				}
				
			}
		}
	}
	else
	{
		// If outside, set back to idle on release
		if (sfEvent.type == sf::Event::MouseButtonReleased)
		{
			if (sfEvent.mouseButton.button == sf::Mouse::Left && getClickBuffer())
			{
				this->buttonState = BTN_IDLE;
			}
		}
	}
}

void Button::updateClickBuffer(const float& dt)
{
	if (this->clickBuffer >= 0.0f)
	{
		this->clickBuffer -= 10.0 * dt;
	}
}

// Functions
void Button::update(const float& dt, const sf::Vector2f& mousePosView)
{
	// Check if the button is disabled
	if (this->buttonState == BTN_DISABLED)
	{
		this->shape.setTexture(&this->buttonIdleTexture);
		this->text.setFillColor(this->textIdleColor);
		this->shape.setFillColor(sf::Color(140, 140, 140, 255));
	}
	else
	{
		// Update click buffer
		this->updateClickBuffer(dt);

		// Check if the mouse is hovering over the button
		if (this->shape.getGlobalBounds().contains(mousePosView))
		{
			hovering = true;
		}
		else
		{
			hovering = false;
		}

		// Set button color
		switch (this->buttonState)
		{
		case BTN_IDLE:
			if (!textureOverriden)
			{
				this->shape.setTexture(&this->buttonIdleTexture);
			}
			this->text.setFillColor(this->textIdleColor);
			this->shape.setFillColor(this->buttonIdleColor);
			break;

		case BTN_ACTIVE:
			if (!textureOverriden)
			{
				this->shape.setTexture(&this->buttonActiveTexture);
			}
			this->text.setFillColor(this->textActiveColor);
			this->shape.setFillColor(this->buttonIdleColor);
			break;

		case BTN_ACTIVE_FUNCTION:
			if (!textureOverriden)
			{
				this->shape.setTexture(&this->buttonActiveTexture);
			}
			this->text.setFillColor(this->textActiveColor);
			this->shape.setFillColor(this->buttonIdleColor);
			break;

		default:
			this->shape.setFillColor(sf::Color::Red);
			break;
		}

		// Set hovering fill color
		if (hovering)
		{
			this->text.setFillColor(this->textHoverColor);
			this->shape.setFillColor(this->buttonHoverColor);
		}
	}
}

void Button::render(sf::RenderTarget& target)
{
	// Draw the shape and the text
	target.draw(this->shape);
	target.draw(this->text);
}
