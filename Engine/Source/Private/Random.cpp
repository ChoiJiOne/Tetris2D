#include "Random.h"

#include <chrono>
#include <random>

int32_t GenerateRandomInt(int32_t MinValue, int32_t MaxValue)
{
	std::random_device RandomDevice;
	std::mt19937 Generator(RandomDevice());
	std::uniform_int_distribution<int32_t> Distribution(std::min<int32_t>(MinValue, MaxValue), std::max<int32_t>(MinValue, MaxValue));

	return Distribution(Generator);
}

float GenerateRandomFloat(float MinValue, float MaxValue)
{
	std::random_device RandomDevice;
	std::mt19937 Generator(RandomDevice());
	std::uniform_real_distribution<float> Distribution(std::min<float>(MinValue, MaxValue), std::max<float>(MinValue, MaxValue));

	return Distribution(Generator);
}
