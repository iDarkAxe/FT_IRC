#include <iostream>
#include <fstream>

#include "Debug.hpp"
#include "ACommand.hpp"
#include "CommandFactory.hpp"

int main(int argc, char** argv)
{
	std::string command_type;
	std::vector<std::string> params;
	command_type = "JOIN";
	params.push_back("#general");
	params.push_back("user1");
	ACommand *command = CommandFactory::createCommand(command_type, params);
	if (command)
	{
		command->execute();
		delete command;
	}
	else
	{
		Debug::print(ERROR, "Failed to create command.");
	}
	if (argc != 3)
	{
		Debug::print(ERROR, "Usage: " + std::string(argv[0]) + " port password");
		return 1;
	}
	return 0;
}
