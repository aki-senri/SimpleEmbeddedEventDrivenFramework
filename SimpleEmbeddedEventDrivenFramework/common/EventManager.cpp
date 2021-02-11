#include "EventManager.h"
#include <mutex>
#include <thread>


EventManager::EventManager()
{
}

EventManager::EventManager(std::mutex *mutex)
{
	mutex_ = mutex;
}

EventManager::~EventManager()
{
}


EventManager::EventError EventManager::Run()
{
	run_continue_ = true;

	while (run_continue_)
	{
		if (queue_table_.size() > 0)
		{
			EventDequeue();
		}
		this_thread::sleep_for(chrono::milliseconds(1));
	}
	return EventOK;
}

EventManager::EventError EventManager::EventEnqueue(unique_ptr<EventQueue> event)
{
	EventError error = EventOK;

	if (queue_table_.size() < EventQueueSize)
	{

	}
	else
	{
		// Queue Table is full, log output
		error = EventError::ErrorQueueFull;
	}

	return error;
}

EventManager::EventError EventManager::Stop()
{
	if (run_continue_ == false)
	{
		return ErrorNotRun;
	}
	return EventOK;
}

void EventManager::SetMutex(std::mutex* mutex)
{
	mutex_ = mutex;
}

EventManager::EventError EventManager::EventDequeue()
{
	EventError error = EventOK;

	if (queue_table_.size() > 0)
	{
		queue_table_.front().ExecuteEvent();
		std::lock_guard<mutex> lock(*mutex_);
		queue_table_.pop();
	}

	return ErrorQueueEmpty;
}

