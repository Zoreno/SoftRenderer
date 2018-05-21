#include "MathUtil.h"

float Clamp(
	float a,
	float min,
	float max)
{
	if(a < min)
	{
		return min;
	}

	if(a > max)
	{
		return max;
	}

	return a;
}

float Clamp01(
	float a)
{
	return Clamp(a, 0.f, 1.f);
}

float Lerp(float a, float b, float t)
{
	return a + t * (b - a);
}
