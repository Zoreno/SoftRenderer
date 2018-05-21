#include "Time.h"

#include <chrono>

unsigned long long GetTime()
{
	auto currentTime = std::chrono::system_clock::now();

	return std::chrono::duration_cast<std::chrono::milliseconds>(currentTime.time_since_epoch()).count();
}

unsigned long long GetTimeNano()
{
	auto currentTime = std::chrono::system_clock::now();

	return std::chrono::duration_cast<std::chrono::nanoseconds>(currentTime.time_since_epoch()).count();
}
