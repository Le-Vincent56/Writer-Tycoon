#include "../stdafx.h"
#include "TileMap.h"

// Constructor/Destructor
TileMap::TileMap()
{
	this->gridSizeF = 100.0f;
	this->gridSizeU = static_cast<unsigned>(this->gridSizeF);
	this->layers = 2;
	this->maxSize.x = 10;
	this->maxSize.y = 10;

	// Push x coordinate
	this->map.resize(this->maxSize.x);
	for (size_t x = 0; x < this->maxSize.x; ++x)
	{
		this->map.push_back(std::vector<std::vector<Tile>>());

		
		
		for (size_t y = 0; y < this->maxSize.y; ++y)
		{
			// Push y coordinate
			this->map[x].resize(this->maxSize.y);
			this->map[x].push_back(std::vector<Tile>());
			
			for (size_t z = 0; z < this->layers; ++z)
			{
				// Push z coordinates
				this->map[x][y].resize(this->layers);
				this->map[x][y].push_back(Tile(
					x * this->gridSizeF, 
					y * this->gridSizeF, 
					this->gridSizeF)
				);
			}
		}
	}
}

TileMap::~TileMap()
{
}

// Functions
void TileMap::update()
{
}

void TileMap::render(sf::RenderTarget& target)
{
	for (auto &x : this->map)
	{
		for (auto &y : x)
		{
			for (auto& z : y)
			{
				z.render(target);
			}
		}
	}
}
