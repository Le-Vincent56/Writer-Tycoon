#include "../stdafx.h"
#include "VectorUtils.h"

sf::Vector2f VectorUtils::normalize(const sf::Vector2f& source)
{
	sf::Vector2f normalized = source;

	// Get the length of the vector
	float length = std::hypot(normalized.x, normalized.y);

	// Check if the length is not 0
	if (length != 0)
	{
		// Divide the vector by its length to normalize
		normalized /= length;
	}

	return normalized;
}

sf::Vector2f VectorUtils::mult(const sf::Vector2f& a, const sf::Vector2f& b)
{
	return sf::Vector2f(a.x * b.x, a.y * b.y);
}

sf::Vector2f VectorUtils::mult(const sf::Vector2f& source, const float& scalar)
{
	return sf::Vector2f(source.x * scalar, source.y * scalar);
}

sf::Vector2f VectorUtils::lerp(const sf::Vector2f& a, const sf::Vector2f& b, float t)
{
	float newX = MathUtils::lerp(a.x, b.x, t);
	float newY = MathUtils::lerp(a.y, b.y, t);
	return sf::Vector2f(newX, newY);
}

sf::Vector2f VectorUtils::abs(const sf::Vector2f& source)
{
	return sf::Vector2f(std::abs(source.x), std::abs(source.y));
}
