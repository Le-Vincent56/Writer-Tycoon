#pragma once

enum TileType
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
		const sf::IntRect textureRect, const bool& collision = false, const short int& type = TileType::DEFAULT);
	virtual ~Tile();

	// Accessors
	const sf::Vector2f& getPosition() const;
	const bool& getCollision() const;
	const bool intersects(const sf::FloatRect bounds) const;
	const sf::FloatRect getGlobalBounds() const;
	const std::string toString() const;

	// Functions
	void update();
	void render(sf::RenderTarget& target);
};

