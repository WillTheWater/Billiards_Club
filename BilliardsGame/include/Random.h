#pragma once

#include <random>
#include "Vec2.h"

namespace Random
{
	extern std::random_device rd;
	extern std::seed_seq ss;
	extern std::mt19937 mt;
	int getRandomIndex(int min, int max);

	int getRandomInt(int min, int max);

	float getRandomFloat(int min, int max);

	Vec2 getRandomVec2(int minX, int maxX, int minY, int maxY);
	
	Vec2 getRandomVec2(int maxX, int maxY);
};