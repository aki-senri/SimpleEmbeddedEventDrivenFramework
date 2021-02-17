#pragma once

#include <functional>
#include <thread>

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
			do
			{
				std::this_thread::sleep_for(std::chrono::milliseconds(millisecond));		// TODO:Sleepのラッパー処理を呼び出すように変更が必要
				if (timer_run_)
				{
					function(args...);
				}
			} while (repeat && timer_run_);
		});

		return true;
	}

	bool Stop();

private:
	std::thread timerthread_;
	bool timer_run_ = false;
};
