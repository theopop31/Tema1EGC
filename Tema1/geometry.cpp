#include "geometry.h"
#include <cmath>

void geometry::TriangleCenter(
	float& cx,
	float& cy,
	float baseLength,
	float x,
	float y)
{
	float side, demiperimeter, surface, radius;
	side = sqrt((baseLength / 2) * (baseLength / 2) + (2 * baseLength) * (2 * baseLength));
	demiperimeter = (baseLength + 2 * side) / 2;
	surface = surface = sqrt(demiperimeter * (demiperimeter - baseLength) * (demiperimeter - side) * (demiperimeter - side));
	radius = baseLength * side * side / (4 * surface);
	cx = x + baseLength / 2;
	cy = y + sqrt(radius * radius - (baseLength / 2) * (baseLength / 2));
}