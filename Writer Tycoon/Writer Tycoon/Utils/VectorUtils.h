#pragma once

#include <SFML/Graphics.hpp>

static class VectorUtils
{
public:
	static sf::Vector2f normalize(sf::Vector2f source);
	static sf::Vector2f mult(sf::Vector2f vectorOne, sf::Vector2f vectorTwo);
	static sf::Vector2f mult(sf::Vector2f source, float scalar);
};

