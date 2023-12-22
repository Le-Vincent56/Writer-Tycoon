#pragma once

#include "Tiles/Tile.h"

class TileMap
{
private:
	// Variables
	float gridSizeF;
	unsigned int gridSizeU;
	unsigned int layers;
	sf::Vector2u maxSize;
	std::vector<std::vector<std::vector<Tile>>> map;

public:
	// Constructor/Destructor
	TileMap();
	virtual ~TileMap();

	// Functions
	void update();
	void render(sf::RenderTarget& target);
};

