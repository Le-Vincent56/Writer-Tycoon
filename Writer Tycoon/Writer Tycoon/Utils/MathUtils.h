#pragma once

#include <stdlib.h>

static class MathUtils
{
public:
	static float lerp(float a, float b, float t);

	template <typename T>
	static T clamp(const T& value, const T& lower, const T& upper);
};

inline float MathUtils::lerp(float a, float b, float t)
{
	return a * (1.0f - t) + (b * t);
}

template<typename T>
inline T MathUtils::clamp(const T& value, const T& lower, const T& upper)
{
	return std::max(lower, std::min(value, upper));
}
