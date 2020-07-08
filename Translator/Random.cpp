#include <chrono>

#include "Random.h"

string Random::GetTimeNanoSecondsString()
{
	const auto currentTime = std::chrono::duration_cast<std::chrono::nanoseconds>(
		std::chrono::high_resolution_clock::now().time_since_epoch());

	return std::to_string(currentTime.count());
}
