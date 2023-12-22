#pragma once

class HitboxComponent
{
private:
	// Variables
	sf::Sprite& sprite;
	sf::RectangleShape hitbox;
	float offsetX;
	float offsetY;

public:
	// Constructor/Destructor
	HitboxComponent(sf::Sprite& sprite, 
		float offsetX, float offsetY, 
		float width, float height);
	~HitboxComponent();

	// Functions
	bool checkIntersect(const sf::FloatRect& rect);

	void update();
	void render(sf::RenderTarget& target);
};

