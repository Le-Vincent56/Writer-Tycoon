#include "../stdafx.h"
#include "RectUtils.h"

sf::FloatRect RectUtils::getIntersect(const sf::FloatRect& rect1, const sf::FloatRect& rect2)
{
    float left = std::max(rect1.left, rect2.left);
    float top = std::max(rect1.top, rect2.top);
    float right = std::min(rect1.left + rect1.width, rect2.left + rect2.width);
    float bottom = std::min(rect1.top + rect1.height, rect2.top + rect2.height);

    // Check for non-overlapping rectangles
    if (left < right && top < bottom) {
        return sf::FloatRect(left, top, right - left, bottom - top);
    }
    else {
        // Return an empty rectangle if there is no intersection
        return sf::FloatRect();
    }
}
