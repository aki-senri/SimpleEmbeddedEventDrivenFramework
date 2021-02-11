#pragma once

#include <queue>
#include <memory>
#include <mutex>
#include "EventQueue.h"

using namespace std;

class EventManager {
public :
	EventManager();
	EventManager(std::mutex *mutex);
	~EventManager();

	enum EventError {
		EventOK = 0,
		ErrorQueueFull,
		ErrorQueueEmpty,
		ErrorNotRun,
	};

	EventError Run();
	EventError EventEnqueue(unique_ptr<EventQueue> event);
	EventError Stop();
	void SetMutex(std::mutex* mutex);

private:
	std::queue<EventQueue> queue_table_;
	const int EventQueueSize = 32;
	std::mutex *mutex_;
	bool run_continue_ = false;

	EventError EventDequeue();

};

