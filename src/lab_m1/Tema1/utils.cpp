#include "utils.h"
#include <cmath>
#include <utils/math_utils.h>

float utils::getRandomNumber(
	float min,
	float max,
	float excludedInterval)
{
	float randomAngle;
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dist(min, max);

	randomAngle = dist(gen);

	while (randomAngle <= excludedInterval && randomAngle >= -excludedInterval) {
		randomAngle = dist(gen);
	}

	return randomAngle;
}


bool utils::isInBox(int mouseX, int mouseY, glm::vec3 boxCenter, float boxSide, float translateX, float translateY)
{
	if (mouseX - 30 > boxCenter.x - (boxSide / 2) + translateX &&
		mouseX - 30 < boxCenter.x + (boxSide / 2) + translateX &&
		mouseY > boxCenter.y - (boxSide / 2) + translateY &&
		mouseY < boxCenter.y + (boxSide / 2) + translateY) {
		return true;
	}

	return false;
}

