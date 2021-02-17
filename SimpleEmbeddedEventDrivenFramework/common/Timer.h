#pragma once

#include <functional>
#include <thread>

template<class First, class... Rest>
class Timer
{
public:
	Timer::Timer(First&& first, Rest&&... rest, unsigned int millisecond)
	{
		if (std::is_function(first))
		{
			std::thread timerthread([f_, args_...]()
			{
				std::this_thread::sleep_for(std::chrono::milliseconds(millisecond));
				f_(args_...);
			});
		}
	}
};
