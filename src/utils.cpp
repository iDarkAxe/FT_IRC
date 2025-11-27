#include <utils.hpp>
#include <sys/stat.h>
#include <unistd.h>

static bool is_terminal(const char *path);

bool is_stdout_on_tty()
{
	return is_terminal("/dev/stdout");
}

bool is_stderr_on_tty()
{
	return is_terminal("/dev/stderr");
}

bool is_stdin_on_tty()
{
	return is_terminal("/dev/stdin");
}

/**
 * @brief Check if a given path is a terminal
 * 
 * @param[in] path path to check (e.g., "/dev/stdout") 
 * @return true true if the path is a terminal
 * @return false false if the path is not a terminal
 */
bool is_terminal(const char* path)
{
	struct stat st;
	if (stat(path, &st) == -1)
		return false;
	return S_ISCHR(st.st_mode);
}
