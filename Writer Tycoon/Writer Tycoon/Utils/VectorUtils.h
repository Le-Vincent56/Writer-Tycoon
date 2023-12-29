#pragma once

#include "MathUtils.h"

class VectorUtils
{
public:
	static sf::Vector2f normalize(const sf::Vector2f& source);
	static sf::Vector2f mult(const sf::Vector2f& a, const sf::Vector2f& b);
	static sf::Vector2f mult(const sf::Vector2f& source, const float& scalar);
	static sf::Vector2f lerp(const sf::Vector2f& a, const sf::Vector2f& b, float t);
	static sf::Vector2f abs(const sf::Vector2f& source);
};

