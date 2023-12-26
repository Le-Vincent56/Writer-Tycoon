#include "../../stdafx.h"
#include "Tile.h"

Tile::Tile()
{
	// Set default variables
	this->collision = false;
	this->type = TileType::DEFAULT;
}

// Constructor/Destructor
Tile::Tile(unsigned int gridX, unsigned int gridY, float gridSize, const sf::Texture& texture, 
	const sf::IntRect textureRect, const bool& collision, const short& type)
{
	// Set rectangle shape
	this->shape.setSize(sf::Vector2f(gridSize, gridSize));
	this->shape.setFillColor(sf::Color::White);
	this->shape.setPosition(static_cast<float>(gridX) * gridSize, static_cast<float>(gridY) * gridSize);
	this->shape.setOutlineThickness(1.0f);
	this->shape.setOutlineColor(sf::Color::Black);
	this->shape.setTexture(&texture);
	this->shape.setTextureRect(textureRect);

	// Set default variables
	this->collision = collision;
	this->type = type;
}

Tile::~Tile()
{
}

// Accessors
const sf::Vector2f& Tile::getPosition() const
{
	return this->shape.getPosition();
}

const bool& Tile::getCollision() const
{
	return this->collision;
}

const std::string Tile::toString() const
{
	std::stringstream ss;

	// Add data to the string
	ss << this->shape.getTextureRect().left << " " << this->shape.getTextureRect().top 
		<< " " << this->collision << " " << this->type;

	return ss.str();
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
