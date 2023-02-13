#pragma once
#include <random>
#include "lab_m1/Tema1/Tema1.h"
#define PI 3.14159

namespace utils
{
	float getRandomNumber(float min, float max, float excludedInterval = 0);
	bool isInBox(int mouseX, int mouseY, glm::vec3 boxCenter, float boxSide, float translateX, float translateY);

}
