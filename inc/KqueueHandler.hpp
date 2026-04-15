#ifndef KQUEUE_HPP
#define KQUEUE_HPP

// #if defined(__APPLE__) || defined(__FreeBSD__)

#include "EventHandler.hpp"
#include <vector>

const int MAX_EVENTS = 64;

class KqueueHandler : public EventHandler {
private:
	std::vector<struct kevent> events; // vector to store events
	std::vector<struct kevent> changes; // vector to store changes to be applied in the next kevent call

public:
	KqueueHandler();
	~KqueueHandler();

	int add(int fd, enum EventType type);
	int modify(int fd, enum EventType type);
	int del(int fd);
	int wait();

	EventResult getEvent(int index) const;
};

// #endif // __APPLE__ || __FreeBSD__

#endif // KQUEUE_HPP
