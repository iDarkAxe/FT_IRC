#ifndef EPOLLLOOP_HPP
#define EPOLLLOOP_HPP

#if defined(__linux__)

#include "EventLoop.hpp"
#include <vector>

const int MAX_EVENTS = 64;

class EpollLoop : public EventLoop {
private:
	std::vector<struct epoll_event> events; // vector to store events

public:
	EpollLoop();
	~EpollLoop();

	int add(int fd, enum EventType type);
	int modify(int fd, enum EventType type);
	int del(int fd);
	int wait();

	EventResult getEvent(int index) const;
};

#endif // __linux__

#endif // EPOLLLOOP_HPP
