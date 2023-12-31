#include "../stdafx.h"
#include "Dropdown.h"

// Constructor/Destructor
Dropdown::Dropdown(float x, float y, float width, float height,
	sf::Font& font, 
	sf::Texture& dropdownIdleTexture, sf::Texture& dropdownActiveTexture,
	std::string elementNames[], 
	unsigned int numOfElements, const unsigned int defaultIndex)
	: font(font), 
	dropdownIdleTexture(dropdownIdleTexture),
	dropdownActiveTexture(dropdownActiveTexture),
	showElements(false)
{
	// Set click buffers
	clickBufferMax = 3.0f;
	clickBuffer = clickBufferMax;

	// Set active element
	this->currentElement =
		new Button(
			x, y, width, height,
			this->font, elementNames[defaultIndex], 24,
			sf::Color(0, 0, 0, 255), sf::Color(180, 180, 180, 255), sf::Color(150, 150, 150, 255),
			this->dropdownIdleTexture, this->dropdownActiveTexture
		);

	// Push back buttons
	for (unsigned int i = 0; i < numOfElements; ++i)
	{
		this->elements.push_back(
			new Button(
				x, y + ((i + 1) * height), width, height,
				this->font, elementNames[i], 24,
				sf::Color(0, 0, 0, 255), sf::Color(180, 180, 180, 255), sf::Color(150, 150, 150, 255),
				this->dropdownIdleTexture, this->dropdownActiveTexture,
				static_cast<unsigned short int>(i)
			)
		);
	}

	// Set the last current element ID
	this->lastCurrentID = this->currentElement->getID();
}

Dropdown::~Dropdown()
{
	delete this->currentElement;
	this->currentElement = nullptr;

	for (size_t i = 0; i < this->elements.size(); ++i)
	{
		delete this->elements[i];
		this->elements[i] = nullptr;
	}
}

// Accessors
const unsigned short& Dropdown::getCurrentElementID() const
{
	return this->currentElement->getID();
}

const unsigned short& Dropdown::getLastCurrentElementID() const
{
	return this->lastCurrentID;
}

// Functions
void Dropdown::updateEvents(sf::Event& sfEvent, const sf::Vector2i& mousePosWindow)
{
	// Update the current element's events
	this->currentElement->updateEvents(sfEvent, mousePosWindow);

	// If showing elements, update their events
	if (this->showElements)
	{
		for (size_t i = 0; i < this->elements.size(); ++i)
		{
			this->elements[i]->updateEvents(sfEvent, mousePosWindow);
		}
	}
}

void Dropdown::update(const float& dt, const sf::Vector2i& mousePosWindow)
{
	// Update the active element
	this->currentElement->update(dt, mousePosWindow);

	// Check if the active element is pressed (want to toggle dropdown)
	if (this->currentElement->isPressed())
	{
		// Toggle showing the dropdown
		if (this->showElements)
		{
			// Stop overriding the current element texture
			currentElement->setTextureOverride(false);
			
			this->showElements = false;
		}
		else
		{
			// Override the current element texture
			currentElement->setTextureOverride(true);
			currentElement->setButtonTexture(this->dropdownActiveTexture);
			this->showElements = true;
		}
	}

	// Update drop down elements if all are shown
	if (this->showElements)
	{
		for (auto& i : this->elements)
		{
			i->update(dt, mousePosWindow);

			if (i->isPressed())
			{
				// Toggle the list and update the active element text
				this->showElements = false;
				this->currentElement->setText(i->getText());

				// Stop overriding the current element texture
				currentElement->setTextureOverride(false);

				// Update the last current element ID
				this->lastCurrentID = this->currentElement->getID();

				// Update the active ID of the current element
				this->currentElement->setID(i->getID());
			}
		}
	}
}

void Dropdown::render(sf::RenderTarget& target)
{
	// Draw active element
	this->currentElement->render(target);

	// Draw drop down elements if all are shown
	if (this->showElements)
	{
		for (auto& i : this->elements)
		{
			i->render(target);
		}
	}
}
