#pragma once

#include <functional>
#include <thread>
#include <condition_variable>

class Timer
{
public:
	Timer::Timer();
	Timer::~Timer();

	template<class Function, class... Args>
	bool Start(unsigned int millisecond, bool repeat, Function function, Args... args)
	{
		if (timer_run_)
		{
			return false;
		}

		timer_run_ = true;
		timerthread_ = std::thread([this, millisecond, repeat, function, args...]()
		{
			std::mutex mutex;
			do
			{
				std::unique_lock<std::mutex> lock(mutex);
				if (cond_.wait_for(lock, std::chrono::milliseconds(millisecond), [this]() { return !timer_run_; }) == false)
				{
					function(args...);
				}
			} while (repeat && timer_run_);
		});

		return true;
	}

	template<class Function, class... Args>
	bool SyncStart(unsigned int millisecond, bool repeat, Function function, Args... args)
	{
		if (timer_run_)
		{
			return false;
		}

		timer_run_ = true;
		std::mutex mutex;
		do
		{
			std::unique_lock<std::mutex> lock(mutex);
			if (cond_.wait_for(lock, std::chrono::milliseconds(millisecond), [this]() { return !timer_run_; }) == false)
			{
				function(args...);
			}
		} while (repeat && timer_run_);

		return true;
	}

	bool Stop();

private:
	std::thread timerthread_;
	std::condition_variable cond_;
	bool timer_run_ = false;
};
