#if defined(__linux__)

#include "EpollHandler.hpp"
#include "utils.hpp"
#include <sys/epoll.h>
#include <cstdio>
#include <stdexcept>
#include <cstdlib>

EpollHandler::EpollHandler()
{
	this->event_socket = epoll_create(MAX_EVENTS);
	if (this->event_socket < 0)
	{
		perror("epoll_create");
		throw std::runtime_error("Failed to create epoll instance");
	}
	this->events.resize(MAX_EVENTS);
}

EpollHandler::~EpollHandler()
{
	secure_close(this->event_socket);
}

int EpollHandler::add(int fd, enum EventType type)
{
	epoll_event ev;
	ev.events = 0;
	if (type & EVENT_TYPE_READ)
		ev.events |= EPOLLIN;
	if (type & EVENT_TYPE_WRITE)
		ev.events |= EPOLLOUT;
	ev.events |= EPOLLRDHUP; // always want to be notified when client closed connection
	ev.data.fd = fd;
	if (epoll_ctl(this->event_socket, EPOLL_CTL_ADD, fd, &ev) < 0)
	{
		perror("epoll_ctl add client");
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

int EpollHandler::modify(int fd, enum EventType type)
{
	epoll_event ev;
	ev.events = 0;
	if (type & EVENT_TYPE_READ)
		ev.events |= EPOLLIN;
	if (type & EVENT_TYPE_WRITE)
		ev.events |= EPOLLOUT;
	ev.events |= EPOLLRDHUP; // always want to be notified when client closed connection
	ev.data.fd = fd;
	if (epoll_ctl(this->event_socket, EPOLL_CTL_MOD, fd, &ev) < 0)
	{
		perror("epoll_ctl modify client");
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}
int EpollHandler::del(int fd)
{
	if (epoll_ctl(this->event_socket, EPOLL_CTL_DEL, fd, NULL) < 0)
	{
		perror("epoll_ctl del client");
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}
int EpollHandler::wait()
{
	int n = epoll_wait(this->event_socket, this->events.data(), static_cast<int>(this->events.size()), EVENT_WAIT_TIMEOUT);
	if (n < 0)
	{
		perror("epoll_wait");
		return -1;
	}
	return n;
}
EventResult EpollHandler::getEvent(int index) const
{
	if (index < 0)
		throw std::out_of_range("Event index out of range");

	const struct epoll_event& ev = this->events.at(static_cast<size_t>(index));
	EventResult res; // Initialisation par défaut

	res.fd = ev.data.fd;
	res.can_read = (ev.events & EPOLLIN) != 0;
	res.can_write = (ev.events & EPOLLOUT) != 0;
	res.is_error = (ev.events & (EPOLLRDHUP | EPOLLERR | EPOLLHUP)) != 0;

	return res;
}

#endif // __linux__
