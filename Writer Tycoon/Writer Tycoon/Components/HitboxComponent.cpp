#include "HitboxComponent.h"

// Constructor/Destructor
HitboxComponent::HitboxComponent(sf::Sprite& sprite, 
	float offsetX, float offsetY, 
	float width, float height)
	: sprite(sprite)
{
	// Save offsets
	this->offsetX = offsetX;
	this->offsetY = offsetY;

	// Set hitbox position and size
	this->hitbox.setPosition(this->sprite.getPosition().x + offsetX, 
		this->sprite.getPosition().y + offsetY);
	this->hitbox.setSize(sf::Vector2f(width, height));
	
	// Make it an outline
	this->hitbox.setFillColor(sf::Color::Transparent);
	this->hitbox.setOutlineThickness(1.0f);
	this->hitbox.setOutlineColor(sf::Color::Green);
}

HitboxComponent::~HitboxComponent()
{

}

// Functions
bool HitboxComponent::checkIntersect(const sf::FloatRect& rect)
{
	return this->hitbox.getGlobalBounds().intersects(rect);
}

void HitboxComponent::update()
{
	this->hitbox.setPosition(this->sprite.getPosition().x + this->offsetX,
		this->sprite.getPosition().y + this->offsetY);

}

void HitboxComponent::render(sf::RenderTarget& target)
{
	// Draw the hitbox
	target.draw(this->hitbox);
}
