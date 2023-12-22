#pragma once

class Tile
{
private:


protected:
	// Variables
	sf::RectangleShape shape;


public:
	// Constructor/Destructor
	Tile();
	Tile(float x, float y, float gridSize);
	virtual ~Tile();

	// Functions
	void update();
	void render(sf::RenderTarget& target);
};

