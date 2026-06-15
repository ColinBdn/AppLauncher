#include "utils_math.h"

#include <cmath>

float distance(const Vec3& a, const Vec3& b)
{
	float dx = a.x - b.x, dy = a.y - b.y, dz = a.z - b.z;
	return std::sqrtf(dx * dx + dy * dy + dz * dz);
}

float distance(const Vec2& a, const Vec2& b)
{
	float dx = a.x - b.x, dy = a.y - b.y;
	return std::sqrtf(dx * dx + dy * dy);
}


float distanceSquared(const Vec3& a, const Vec3& b)
{
	float dx = a.x - b.x, dy = a.y - b.y, dz = a.z - b.z;
	return dx * dx + dy * dy + dz * dz;
}

float distanceSquared(const Vec2& a, const Vec2& b)
{
	float dx = a.x - b.x, dy = a.y - b.y;
	return dx * dx + dy * dy;
}