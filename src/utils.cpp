#include "utils.hpp"
#include "Debug.hpp"
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <iomanip>
#include <sstream>
#include <ctime>
#include <cerrno>

static bool is_terminal(int fd);

bool is_stdout_on_tty()
{
	return is_terminal(1);
}

bool is_stderr_on_tty()
{
	return is_terminal(2);
}

bool is_stdin_on_tty()
{
	return is_terminal(0);
}

/**
 * @brief Check if a given path is a terminal
 *
 * @param[in] fd file descriptor to check
 * @return true true if the path is a terminal
 * @return false false if the path is not a terminal
 */
bool is_terminal(int fd)
{
	struct stat st;
	if (fstat(fd, &st) == -1)
		return false;
	return S_ISCHR(st.st_mode);
}

std::string format_date(void)
{
    const size_t sizeStr = 32;
	char buffer[sizeStr] = {0};
	std::time_t time = std::time(NULL);

	if (std::strftime(buffer, sizeStr, "%A %B %d %Y", std::gmtime(&time)) == 0)
		return "Error on std::strftime";
	return (buffer);
}

std::string format_time(void)
{
    const size_t sizeStr = 32;
	char buffer[sizeStr] = {0};
	std::time_t time = std::time(NULL);

	if (std::strftime(buffer, sizeStr, "%X +00:00", std::gmtime(&time)) == 0)
		return "Error on std::strftime";
	return (buffer);
}

std::string format_date_time(void)
{
	const size_t sizeStr = 64;
	char buffer[sizeStr] = {0};
	std::time_t time = std::time(NULL);

	if (std::strftime(buffer, sizeStr, "%A %B %d %Y -- %X +00:00", std::gmtime(&time)) == 0)
		return "Error on std::strftime";
	return (buffer);
}

void secure_close(int& fd)
{
	if (fd == -1)
		return;
	close(fd);
	fd = -1;
}

void epoll_ret(void)
{
	if (errno == EINTR) 
	{
		Debug::print(INFO, "epoll_wait interrupted by signal, closing...");
		return;
	}
	perror("epoll_wait");
}
