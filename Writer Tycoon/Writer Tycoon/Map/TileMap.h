#pragma once

#include "Tiles/Tile.h"
#include "../Utils/RectUtils.h"
#include "../Entities/Entity.h"

// Forward Declarations
class Tile;
class Entity;

class TileMap
{
private:
	// Variables
	float gridSizeF;
	int gridSizeI;
	sf::Vector2i maxSizeGrid;
	sf::Vector2f maxSizeWorld;
	int layers;
	std::vector<std::vector<std::vector<Tile*>>> map;
	std::string textureFilePath;
	sf::Texture tileSheet;
	sf::RectangleShape collisionBox;
	int fromX;
	int toX;
	int fromY;
	int toY;
	int layer;

	// Functions
	void clear();

public:
	// Constructor/Destructor
	TileMap(float gridSize, int width, int height, std::string textureFilePath);
	~TileMap();

	// Accessors
	const sf::Texture* getTileSheet() const;

	// Functions
	void saveToFile(const std::string fileName);
	void loadFromFile(const std::string fileName);
	void addTile(const sf::IntRect& textureRect, const int x, const int y,
		const int z, const bool& collision, const short int& type);
	void removeTile(const int x, const int y, const int z = 0);
	void cullTiles(Entity* entity);
	void updateCollision(const float& dt, Entity* entity);
	void update();
	void render(sf::RenderTarget& target, Entity* entity = nullptr);
};

