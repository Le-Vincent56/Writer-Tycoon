#include "VectorUtils.h"

sf::Vector2f VectorUtils::normalize(sf::Vector2f source)
{
	float length = std::hypot(source.x, source.y);
	if (length != 0) source /= length;
	return source;
}

sf::Vector2f VectorUtils::mult(sf::Vector2f vectorOne, sf::Vector2f vectorTwo)
{
	return sf::Vector2f(vectorOne.x * vectorTwo.x, vectorOne.y * vectorTwo.y);
}

sf::Vector2f VectorUtils::mult(sf::Vector2f source, float scalar)
{
	return sf::Vector2f(source.x * scalar, source.y * scalar);
}
