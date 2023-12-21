#include "PauseMenu.h"

// Constructor/Destructor
PauseMenu::PauseMenu(sf::RenderWindow& window, sf::Font& font,
	sf::Texture& buttonIdleTexture, sf::Texture& buttonActiveTexture)
	: font(font), buttonIdleTexture(buttonIdleTexture), buttonActiveTexture(buttonActiveTexture)
{
	// Initialize background
	this->background.setSize(
		sf::Vector2f(
			static_cast<float>(window.getSize().x), 
			static_cast<float>(window.getSize().y)
		)
	);
	this->background.setFillColor(sf::Color(20, 20, 20, 100));

	// Initialize container
	this->container.setSize(
		sf::Vector2f(
			static_cast<float>(window.getSize().x) / 4.0f, 
			static_cast<float>(window.getSize().y)
		)
	);
	this->container.setFillColor(sf::Color(20, 20, 20, 200));
	this->container.setPosition(
		(static_cast<float>(window.getSize().x) / 2.0f) - (this->container.getSize().x / 2.0f),
		0.0f
	);

	// Initialize text
	this->menuText.setFont(font);
	this->menuText.setFillColor(sf::Color(255, 255, 255, 200));
	this->menuText.setCharacterSize(60);
	this->menuText.setString("PAUSED");
	this->menuText.setPosition(
		this->container.getPosition().x
			+ (this->container.getGlobalBounds().width / 2.0f)
			- (this->menuText.getGlobalBounds().width / 2.0f),
		this->container.getPosition().y + 30.0f
	);
}

PauseMenu::~PauseMenu()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}

// Accessors
std::map<std::string, Button*>& PauseMenu::getButtons()
{
	return this->buttons;
}

const sf::Vector2f& PauseMenu::getContainerCenterBelowText() const
{
	return sf::Vector2f(
		this->container.getPosition().x
			+ (this->container.getGlobalBounds().width / 2.0f),
		this->container.getPosition().y 
			+ (this->menuText.getGlobalBounds().height * 6.0f)
		);
}

const bool PauseMenu::isButtonPressed(const std::string key)
{
	return this->buttons[key]->isPressed();
}

// Functions
void PauseMenu::updateEvents(sf::Event& sfEvent, const sf::Vector2f& mousePosView)
{
	// Update button events
	for (auto& it : this->buttons)
	{
		it.second->updateEvents(sfEvent, mousePosView);
	}
}

void PauseMenu::addButton(const std::string key, const std::string text, 
	float x, float y, float width, float height)
{
	this->buttons[key] = new Button(x, y, width, height,
		this->font, text, 24,
		sf::Color(0, 0, 0, 255), sf::Color(180, 180, 180, 255), sf::Color(150, 150, 150, 255),
		this->buttonIdleTexture, this->buttonActiveTexture);
}

void PauseMenu::updateButtons(const float& dt, const sf::Vector2f& mousePosView)
{
	// Update the buttons
	for (auto &it : this->buttons)
	{
		it.second->update(dt, mousePosView);
	}
}

void PauseMenu::update(const float& dt, const sf::Vector2f& mousePosView)
{
	// Update buttons
	this->updateButtons(dt, mousePosView);
}

void PauseMenu::render(sf::RenderTarget& target)
{
	// Draw background and container
	target.draw(this->background);
	target.draw(this->container);

	// Draw buttons
	for (auto& i : this->buttons)
	{
		i.second->render(target);
	}

	// Draw menu text
	target.draw(this->menuText);
}