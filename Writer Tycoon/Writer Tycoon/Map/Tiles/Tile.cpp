#include "../../stdafx.h"
#include "Tile.h"

Tile::Tile()
{
}

// Constructor/Destructor
Tile::Tile(float x, float y, float gridSize, const sf::Texture& texture, const sf::IntRect textureRect)
{
	this->shape.setPosition(x, y);
	this->shape.setSize(sf::Vector2f(gridSize, gridSize));
	this->shape.setFillColor(sf::Color::White);
	this->shape.setOutlineThickness(1.0f);
	this->shape.setOutlineColor(sf::Color::Black);
	this->shape.setTexture(&texture);
	this->shape.setTextureRect(textureRect);
}

Tile::~Tile()
{
}

// Functions
void Tile::update()
{
}

void Tile::render(sf::RenderTarget& target)
{
	// Draw the tile
	target.draw(this->shape);
}
