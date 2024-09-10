#include "Random.h"

namespace Random
{
	std::random_device rd{};
	std::seed_seq ss{ rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd() };
	std::mt19937 mt{ ss };
	int getRandomIndex(int min, int max)
	{
		return static_cast<std::size_t>(std::uniform_int_distribution{ min, max }(mt));
	}
	int getRandomInt(int min, int max)
	{
		return std::uniform_int_distribution{ min, max }(mt);
	}
	float getRandomFloat(int min, int max)
	{
		return static_cast<float>(std::uniform_int_distribution{ min, max }(mt));
	}

	Vec2 getRandomVec2(int minX, int maxX, int minY, int maxY)
	{
		return Vec2{
			( getRandomFloat(minX, maxX) ),
			( getRandomFloat(minY, maxY) )
		};
	}

	Vec2 getRandomVec2(int maxX, int maxY)
	{
		return getRandomVec2(0, maxX, 0, maxY);
	}
};