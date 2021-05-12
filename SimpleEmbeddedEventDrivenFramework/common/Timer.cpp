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
	if (timer_run_)
	{
		timer_run_ = false;
		cond_.notify_one();

		if (timerthread_.joinable())
		{
			timerthread_.join();
		}

		return true;
	}

	return false;
}
