#include "../stdafx.h"
#include "TextureSelector.h"

// Constructor/Destructor
TextureSelector::TextureSelector(float x, float y, 
	float width, float height, float gridSize, 
	const sf::Texture* textureSheet, sf::Font& font, std::string text,
	sf::Texture& buttonIdleTexture, sf::Texture& buttonActiveTexture)
{
	// Set inactive
	this->active = false;
	
	// Set gridSize
	this->gridSize = gridSize;

	// Set hidden
	this->hidden = false;

	float offset = 100.0f;

	// Set hide button
	this->hideButton = new Button(
		x, y, 50.0f, 50.0f,
		font, text, 24,
		sf::Color(0, 0, 0, 255), sf::Color(180, 180, 180, 255), sf::Color(150, 150, 150, 255),
		buttonIdleTexture, buttonActiveTexture
	);

	// Set bounds
	this->bounds.setSize(sf::Vector2f(width, height));
	this->bounds.setPosition(x + offset, y);
	this->bounds.setFillColor(sf::Color(50, 50, 50, 100));
	this->bounds.setOutlineThickness(1.0f);
	this->bounds.setOutlineColor(sf::Color(255, 255, 255, 200));

	// Set texture sheet
	this->sheet.setTexture(*textureSheet);
	this->sheet.setPosition(x + offset, y);

	// Clamp the texture into the bounds
	if (this->sheet.getGlobalBounds().width > this->bounds.getGlobalBounds().width)
	{
		this->sheet.setTextureRect(
			sf::IntRect(0, 0,
				this->bounds.getGlobalBounds().width, this->sheet.getGlobalBounds().height
			)
		);
	}

	if (this->sheet.getGlobalBounds().height > this->bounds.getGlobalBounds().height)
	{
		this->sheet.setTextureRect(
			sf::IntRect(0, 0,
				this->sheet.getGlobalBounds().width, this->bounds.getGlobalBounds().height
			)
		);
	}

	// Initialize selector
	this->selector.setPosition(x, y);
	this->selector.setSize(sf::Vector2f(this->gridSize, this->gridSize));
	this->selector.setFillColor(sf::Color::Transparent);
	this->selector.setOutlineThickness(1.0f);
	this->selector.setOutlineColor(sf::Color::Red);

	// Initialize texture rect
	this->textureRect.width = static_cast<int>(gridSize);
	this->textureRect.width = static_cast<int>(gridSize);
}

TextureSelector::~TextureSelector()
{
	delete this->hideButton;
	this->hideButton = nullptr;
}

// Accessors
const bool& TextureSelector::getActive() const
{
	return this->active;
}

const sf::IntRect& TextureSelector::getTextureRect() const
{
	return this->textureRect;
}

// Functions
void TextureSelector::updateEvents(sf::Event& sfEvent, const sf::Vector2i& mousePosWindow)
{
	// Update button events
	this->hideButton->updateEvents(sfEvent, mousePosWindow);
}

void TextureSelector::updateButtons()
{
	// Hide button
	if (this->hideButton->isPressed())
	{
		// Toggle hidden
		this->hidden = !hidden;
	}
}

void TextureSelector::update(const float& dt, const sf::Vector2i& mousePosWindow)
{
	// Update buttons
	this->updateButtons();

	// Update hide button
	this->hideButton->update(dt, mousePosWindow);

	// Check if hidden
	if (this->hidden)
	{
		return;
	}

	// Check if the mouse is within the bounds of the texture selector
	if (this->bounds.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosWindow)))
	{
		this->active = true;
	}
	else
	{
		this->active = false;
	}

	// Check if active
	if (this->active)
	{
		// Set the mouse position within the selector grid
		this->mousePosGrid.x = 
			((mousePosWindow.x - static_cast<int>(this->bounds.getPosition().x)) 
				/ static_cast<unsigned int>(this->gridSize)
			);

		this->mousePosGrid.y =
			((mousePosWindow.y - static_cast<int>(this->bounds.getPosition().y))
				/ static_cast<unsigned int>(this->gridSize)
			);

		this->selector.setPosition(
			this->bounds.getPosition().x + this->mousePosGrid.x * this->gridSize, 
			this->bounds.getPosition().y + this->mousePosGrid.y * this->gridSize
		);

		// Update texture rect
		this->textureRect.left = static_cast<int>(this->selector.getPosition().x - this->bounds.getPosition().x);
		this->textureRect.top = static_cast<int>(this->selector.getPosition().y - this->bounds.getPosition().y);
	}
}

void TextureSelector::render(sf::RenderTarget& target)
{
	// Check if hidden
	if (!this->hidden)
	{
		target.draw(this->bounds);
		target.draw(this->sheet);
		target.draw(this->selector);
	}

	// Render the hide button
	this->hideButton->render(target);
}