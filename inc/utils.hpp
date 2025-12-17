#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>

bool is_stdout_on_tty();
bool is_stderr_on_tty();
bool is_stdin_on_tty();
std::string format_time(void);
std::string format_date(void);
void secure_close(int &fd);
void epoll_ret(void);

#endif // UTILS_HPP
