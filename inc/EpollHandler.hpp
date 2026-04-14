#ifndef EPOLLHANDLER_HPP
#define EPOLLHANDLER_HPP

#if defined(__linux__)

#include "EventHandler.hpp"
#include <vector>

const int MAX_EVENTS = 64;

class EpollHandler : public EventHandler {
private:
	std::vector<struct epoll_event> events; // vector to store events

public:
	EpollHandler();
	~EpollHandler();

	int add(int fd, enum EventType type);
	int modify(int fd, enum EventType type);
	int del(int fd);
	int wait();

	EventResult getEvent(int index) const;
};

#endif // __linux__

#endif // EPOLLHANDLER_HPP
