#pragma once


class EventQueue {
public:
	virtual bool ExecuteEvent() = 0;
	unsigned short GetEventId();

protected:
	unsigned short event_id_ = 0;
};
