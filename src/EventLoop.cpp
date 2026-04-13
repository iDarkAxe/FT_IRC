#include "EventLoop.hpp"

EventType operator|(EventType a, EventType b)
{
	return static_cast<EventType>(static_cast<int>(a) | static_cast<int>(b));
}

EventType operator&(EventType a, EventType b)
{
	return static_cast<EventType>(static_cast<int>(a) & static_cast<int>(b));
}

EventLoop::~EventLoop()
{
	// Base destructor, will be overridden by derived classes
}
