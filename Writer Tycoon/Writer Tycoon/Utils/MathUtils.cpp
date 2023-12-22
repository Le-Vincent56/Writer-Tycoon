#include "../stdafx.h"
#include "MathUtils.h"

float MathUtils::lerp(float a, float b, float t)
{
	return a * (1.0f - t) + (b * t);
}