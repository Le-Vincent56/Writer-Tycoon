#pragma once

class HitboxComponent
{
private:
	// Variables
	sf::Sprite& sprite;
	sf::RectangleShape hitbox;
	sf::FloatRect nextPosition;
	float offsetX;
	float offsetY;

public:
	// Constructor/Destructor
	HitboxComponent(sf::Sprite& sprite, 
		float offsetX, float offsetY, 
		float width, float height);
	~HitboxComponent();

	// Accessors
	const sf::Vector2f& getPosition() const;
	const sf::FloatRect getGlobalBounds() const;
	const sf::FloatRect& getNextPosition(const sf::Vector2f& velocity);

	// Modifiers
	void setPosition(const sf::Vector2f& position);
	void setPosition(const float x, const float y);

	// Functions
	bool intersects(const sf::FloatRect& rect);
	void update();
	void render(sf::RenderTarget& target);
};

