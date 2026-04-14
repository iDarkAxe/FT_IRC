#ifndef KQUEUE_HPP
#define KQUEUE_HPP

#if defined(__APPLE__) || defined(__FreeBSD__)

#include "EventLoop.hpp"
#include <vector>

const int MAX_EVENTS = 64;

class KqueueLoop : public EventLoop {
private:
	std::vector<struct kevent> events; // vector to store events

public:
	KqueueLoop();
	~KqueueLoop();

	int add(int fd, enum EventType type);
	int modify(int fd, enum EventType type);
	int del(int fd);
	int wait();

	EventResult getEvent(int index) const;
};

#endif // __APPLE__ || __FreeBSD__

#endif // KQUEUE_HPP
