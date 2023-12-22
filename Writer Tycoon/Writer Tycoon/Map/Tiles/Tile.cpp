#include "../../stdafx.h"
#include "Tile.h"

Tile::Tile()
{
}

// Constructor/Destructor
Tile::Tile(float x, float y, float gridSize)
{
	this->shape.setPosition(x, y);
	this->shape.setSize(sf::Vector2f(gridSize, gridSize));
	this->shape.setFillColor(sf::Color::Green);
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
