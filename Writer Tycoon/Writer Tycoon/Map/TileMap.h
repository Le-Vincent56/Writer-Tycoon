#pragma once

#include "Tiles/Tile.h"

class TileMap
{
private:
	// Variables
	float gridSizeF;
	unsigned int gridSizeU;
	sf::Vector2u maxSize;
	unsigned int layers;
	std::vector<std::vector<std::vector<Tile*>>> map;
	sf::Texture tileSheet;

public:
	// Constructor/Destructor
	TileMap(float gridSize, unsigned int width, unsigned int height);
	virtual ~TileMap();

	// Accessors
	const sf::Texture* getTileSheet() const;

	// Functions
	void addTile(const sf::IntRect& textureRect, const unsigned int x, const unsigned int y,
		const unsigned int z = 0);
	void removeTile(const unsigned int x, const unsigned int y, const unsigned int z = 0);
	void update();
	void render(sf::RenderTarget& target);
};
