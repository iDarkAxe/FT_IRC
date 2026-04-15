#if defined(__APPLE__) || defined(__FreeBSD__)

#include "KqueueHandler.hpp"
#include "utils.hpp"
#include <sys/event.h>
#include <cstdio>
#include <stdexcept>
#include <cstdlib>

KqueueHandler::KqueueHandler()
{
	this->event_socket = kqueue();
	if (this->event_socket < 0)
	{
		perror("kqueue");
		throw std::runtime_error("Failed to create kqueue instance");
	}
	this->events.resize(MAX_EVENTS);
}

KqueueHandler::~KqueueHandler()
{
	secure_close(this->event_socket);
}

int KqueueHandler::add(int fd, enum EventType type)
{
	struct kevent tmp_changes[2];
	int n = 0;

	if (type & EVENT_TYPE_READ)
	{
		EV_SET(&tmp_changes[n++], fd, EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, NULL);
	}

	if (type & EVENT_TYPE_WRITE)
		EV_SET(&tmp_changes[n++], fd, EVFILT_WRITE, EV_ADD | EV_ENABLE, 0, 0, NULL);

	if (n >= 1)
		changes.push_back(tmp_changes[0]);
	if (n == 2)
		changes.push_back(tmp_changes[1]);

	return EXIT_SUCCESS;
}

int KqueueHandler::modify(int fd, enum EventType type)
{
	struct kevent tmp_changes[2];
	int n = 0;

	EV_SET(&tmp_changes[n++], fd, EVFILT_READ,
		(type & EVENT_TYPE_READ) ? (EV_ADD | EV_ENABLE) : EV_DISABLE, 0, 0, NULL);
	EV_SET(&tmp_changes[n++], fd, EVFILT_WRITE,
		(type & EVENT_TYPE_WRITE) ? (EV_ADD | EV_ENABLE) : EV_DISABLE, 0, 0, NULL);
	
	changes.push_back(tmp_changes[0]);
	changes.push_back(tmp_changes[1]);
	return EXIT_SUCCESS;
}

int KqueueHandler::del(int fd)
{
	struct kevent tmp_changes[2];

	// EVFILT_READ et EVFILT_WRITE doivent être supprimés séparément
	EV_SET(&tmp_changes[0], fd, EVFILT_READ,  EV_DELETE, 0, 0, NULL);
	EV_SET(&tmp_changes[1], fd, EVFILT_WRITE, EV_DELETE, 0, 0, NULL);

	changes.push_back(tmp_changes[0]);
	changes.push_back(tmp_changes[1]);
	return EXIT_SUCCESS;
}

int KqueueHandler::wait()
{
	struct timespec timeout;
	timeout.tv_sec  = EVENT_WAIT_TIMEOUT / 1000;
	timeout.tv_nsec = (EVENT_WAIT_TIMEOUT % 1000) * 1000000L;

	int n = kevent(this->event_socket,
				   this->changes.data(), static_cast<int>(this->changes.size()),
				   this->events.data(), static_cast<int>(this->events.size()),
				   &timeout);
	if (n < 0)
	{
		perror("kevent wait");
		return -1;
	}
	changes.clear();
	return n;
}

EventResult KqueueHandler::getEvent(int index) const
{
	if (index < 0)
		throw std::out_of_range("Event index out of range");

	const struct kevent& ev = this->events.at(static_cast<size_t>(index));

	EventResult res;
	res.fd        = static_cast<int>(ev.ident);
	res.can_read  = (ev.filter == EVFILT_READ);
	res.can_write = (ev.filter == EVFILT_WRITE);
	res.is_error  = (ev.flags & EV_ERROR) != 0 || (ev.flags & EV_EOF) != 0;

	return res;
}

#endif // __APPLE__ || __FreeBSD__
