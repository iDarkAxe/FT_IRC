#include <iostream>
#include <fstream>

#include "Debug.hpp"

int main(int argc, char** argv)
{
	if (argc != 3)
	{
		Debug::print(ERROR, "Usage: " + std::string(argv[0]) + " port password");
		return 1;
	}
	return 0;
}
