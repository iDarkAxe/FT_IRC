#ifndef DEBUG_TPP
#define DEBUG_TPP

#include "Debug.hpp"

/**
 * @brief Print a debug message with a specific level
 * 
 * @param[in] level debug level
 * @param[in] content content to print
 */
template<typename T>
void Debug::print(debug_level level, const T& content)
{
    switch (level)
    {
        case NOTHING:
            return;
        case INFO:
            *stream << "[INFO] ";
            break;
        case DEBUG:
            *stream << "[DEBUG] ";
            break;
        case ERROR:
            if (useColors)
                *errStream << "[" << RED << "ERROR" << RESET << "] ";
            else
                *errStream << "[ERROR] ";
            break;
        default:
            break;
    }
    
    if (level == ERROR)
        *errStream << content << std::endl;
    else
        *stream << content << std::endl;
}

/**
 * @brief Print a debug message with a specific level on standard output or err
 * 
 * @param[in] level debug level
 * @param[in] message message to print
 */
template<typename T>
void Debug::printSTD(debug_level level, const T& content)
{
	switch (level)
	{
		case NOTHING:
			return;
		case INFO:
			std::cout << "[INFO] ";
			break;
		case DEBUG:
			std::cout << "[DEBUG] ";
			break;
		case ERROR:
			if (useColors)
				std::cerr << "[" << RED << "ERROR" << RESET << "] ";
			else
				std::cerr << "[ERROR] ";
			break;
		default:
			break;
	}
	if (level == ERROR)
		std::cerr << content << std::endl;
	else
		std::cout << content << std::endl;
}

#endif // DEBUG_TPP
