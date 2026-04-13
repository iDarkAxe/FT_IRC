#ifndef EVENTLOOP_HPP
#define EVENTLOOP_HPP

struct EventResult {
	int fd;
	bool can_read;
	bool can_write;
	bool is_error;
};

enum EventType {
	EVENT_TYPE_READ  = 0x01,
	EVENT_TYPE_WRITE = 0x02,
	EVENT_TYPE_ERROR = 0x04
};

EventType operator|(EventType a, EventType b);
EventType operator&(EventType a, EventType b);

#define EVENT_WAIT_TIMEOUT 100 // in milliseconds

class EventLoop {
protected:
	int event_socket; //!< File descriptor of the event loop

public:
	virtual ~EventLoop();

	virtual int add(int fd, enum EventType type) = 0;
	virtual int modify(int fd, enum EventType type) = 0;
	virtual int del(int fd) = 0;
	virtual int wait() = 0;

	virtual EventResult getEvent(int index) const = 0;
};

#endif // EVENTLOOP_HPP
