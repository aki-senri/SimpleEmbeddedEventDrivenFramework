#include "Timer.h"

Timer::Timer()
{
}

Timer::~Timer()
{
	Stop();
}

bool Timer::Stop()
{
	if (timerthread_.joinable())
	{
		timerthread_.join();
		return true;
	}

	return false;
}
