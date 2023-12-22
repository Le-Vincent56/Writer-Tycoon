#include "../stdafx.h"
#include "TileMap.h"

// Constructor/Destructor
TileMap::TileMap(float gridSize, unsigned int width, unsigned int height)
{
	// Set variables
	this->gridSizeF = gridSize;
	this->gridSizeU = static_cast<unsigned>(this->gridSizeF);
	this->maxSize.x = width;
	this->maxSize.y = height;
	this->layers = 2;

	// Resize the x vector and fill it with objects
	this->map.resize(this->maxSize.x, std::vector<std::vector<Tile*>>());
	for (size_t x = 0; x < this->maxSize.x; ++x)
	{
		for (size_t y = 0; y < this->maxSize.y; ++y)
		{
			// Resize the y vectors and fill them with objects
			this->map[x].resize(this->maxSize.y, std::vector<Tile*>());
			
			for (size_t z = 0; z < this->layers; ++z)
			{
				// Resize the z vectors and fill them with nullptr
				this->map[x][y].resize(this->layers, nullptr);
			}
		}
	}

	this->tileSheet.loadFromFile("Assets/Images/tilesheet1.png");
}

TileMap::~TileMap()
{
	for (size_t x = 0; x < this->maxSize.x; ++x)
	{
		for (size_t y = 0; y < this->maxSize.y; ++y)
		{
			for (size_t z = 0; z < this->layers; ++z)
			{
				delete this->map[x][y][z];
				this->map[x][y][z] = nullptr;
			}
		}
	}
}

// Accessors
const sf::Texture* TileMap::getTileSheet() const
{
	return &this->tileSheet;
}

// Functions
void TileMap::addTile(const sf::IntRect& textureRect, const unsigned int x, const unsigned int y,
	const unsigned int z)
{
	// Check if the given coordinates are within the grid bounds
	if (x < this->maxSize.x && x >= 0 
		&& y < maxSize.y && y >= 0
		&& z < this->layers && z >= 0)
	{
		// Check if the tile can be added into the space
		if (this->map[x][y][z] == nullptr)
		{
			this->map[x][y][z] = new Tile(x * this->gridSizeF, y * this->gridSizeF, 
				this->gridSizeF, this->tileSheet, textureRect);
		}
	}
}

void TileMap::removeTile(const unsigned int x, const unsigned int y, const unsigned int z)
{
	if (x < this->maxSize.x && x >= 0
		&& y < maxSize.y && y >= 0
		&& z < this->layers && z >= 0)
	{
		// Check if the tile can be added into the space
		if (this->map[x][y][z] != nullptr)
		{
			delete this->map[x][y][z];
			this->map[x][y][z] = nullptr;
		}
	}
}

void TileMap::update()
{
}

void TileMap::render(sf::RenderTarget& target)
{
	for (auto &x : this->map)
	{
		for (auto &y : x)
		{
			for (auto* z : y)
			{
				// Check if z is a nullptr
				if(z != nullptr)
					z->render(target);
			}
		}
	}
}
