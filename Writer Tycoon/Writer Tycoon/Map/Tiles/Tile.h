#pragma once

enum TileTypes
{
	DEFAULT = 0,
	FLOOR = 1
};

class Tile
{
private:


protected:
	// Variables
	sf::RectangleShape shape;
	bool collision;
	short int type;


public:
	// Constructor/Destructor
	Tile();
	Tile(unsigned int gridX, unsigned int gridY, float gridSize, const sf::Texture& texture, 
		const sf::IntRect textureRect, bool collision = false, short type = TileTypes::DEFAULT);
	virtual ~Tile();

	// Accessors
	const std::string toString() const;

	// Functions
	void update();
	void render(sf::RenderTarget& target);
};

