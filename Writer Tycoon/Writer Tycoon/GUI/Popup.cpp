#include "../stdafx.h"
#include "Popup.h"

// Constructor/Destructor
Popup::Popup(float x, float y, float width, float height,
	sf::Font& font, sf::Texture& frameTexture)
	: font(font), frameTexture(frameTexture)
{
	// Set shape
	this->frameTexture = frameTexture;
	this->shape.setPosition(x, y);
	this->shape.setSize(sf::Vector2f(width, height));
	this->shape.setTexture(&this->frameTexture);
}

Popup::~Popup()
{
	if (!this->texts.empty())
	{
		for (size_t i = 0; i < this->texts.size(); ++i)
		{
			delete this->texts[i];
		}
	}

	if (!this->buttons.empty())
	{
		for (size_t i = 0; i < this->buttons.size(); ++i)
		{
			delete this->buttons[i];
		}
	}

	if (!this->dropdowns.empty())
	{
		for (size_t i = 0; i < this->dropdowns.size(); ++i)
		{
			delete this->dropdowns[i];
		}
	}
	
}

// Accessors
const bool Popup::getEnabled() const
{
	return this->enabled;
}

// Modifiers
const void Popup::addItem(sf::Text* text, float localX, float localY)
{
	// Check if given points are within the popup shape
	bool inBoundsX = localX >= 0 && localX <= (this->shape.getGlobalBounds().width - text->getLocalBounds().width);
	bool inBoundsY = localY >= 0 && localY <= (this->shape.getGlobalBounds().height - text->getCharacterSize());

	if (!(inBoundsX && inBoundsY))
	{
		std::cout << "Popup does not contain point: (" << localX << ", " << localY << ")\n";
		return;
	}

	// Transform the text to be put into the shape
	text->setPosition(this->shape.getPosition().x + localX,
		this->shape.getPosition().y + localY);

	this->texts.push_back(text);
}

const void Popup::addItem(Button* button, float localX, float localY)
{
	// Check if given points are within the popup shape
	if (!this->shape.getGlobalBounds().contains(sf::Vector2f(localX, localY)))
	{
		std::cout << "Popup does not contain point: (" << localX << ", " << localY << ")\n";
		return;
	}

	this->buttons.push_back(button);
}

const void Popup::addItem(Dropdown* dropdown, float localX, float localY)
{
	// Check if given points are within the popup shape
	if (!this->shape.getGlobalBounds().contains(sf::Vector2f(localX, localY)))
	{
		std::cout << "Popup does not contain point: (" << localX << ", " << localY << ")\n";
		return;
	}

	this->dropdowns.push_back(dropdown);
}

const void Popup::setEnabled(const bool enabled)
{
	this->enabled = enabled;
}

// Functions
void Popup::updateEvents(sf::Event& sfEvent, const sf::Vector2f& mousePosView)
{
	// Check if the popup is enabled
	if (!this->enabled)
		return;

	// Check if the buttons list has elements
	if (!this->buttons.empty())
	{
		// Update all button events
		for (size_t i = 0; i < this->buttons.size(); ++i)
		{
			this->buttons[i]->updateEvents(sfEvent, mousePosView);
		}
	}

	// Check if the dropdown list has elements
	if (!this->dropdowns.empty())
	{
		// Update all dropdown events
		for (size_t i = 0; i < this->dropdowns.size(); ++i)
		{
			this->dropdowns[i]->updateEvents(sfEvent, mousePosView);
		}
	}
}

void Popup::update(const float& dt, const sf::Vector2f& mousePosView)
{
	// Check if the popup is enabled
	if (!this->enabled)
		return;

	if (!this->buttons.empty())
	{
		// Update all button events
		for (size_t i = 0; i < this->buttons.size(); ++i)
		{
			this->buttons[i]->update(dt, mousePosView);
		}
	}

	// Check if the dropdown list has elements
	if (!this->dropdowns.empty())
	{
		// Update all dropdown events
		for (size_t i = 0; i < this->dropdowns.size(); ++i)
		{
			this->dropdowns[i]->update(dt, mousePosView);
		}
	}
}

void Popup::render(sf::RenderTarget& target)
{
	// Check if the popup is enabled
	if (!this->enabled)
		return;

	// Draw the shape
	target.draw(this->shape);

	// Draw text
	for (size_t i = 0; i < this->texts.size(); ++i)
	{
		target.draw(*this->texts[i]);
	}

	// Draw buttons
	for (size_t i = 0; i < this->buttons.size(); ++i)
	{
		this->buttons[i]->render(target);
	}

	// Draw dropdowns
	for (size_t i = 0; i < this->dropdowns.size(); ++i)
	{
		this->dropdowns[i]->render(target);
	}
}
