#include "InviteCommand.hpp"


InviteCommand::InviteCommand(std::vector<std::string> params)
{
	_params = params;
}

void InviteCommand::execute()
{
	std::cout << "Executing INVITE command with parameters:" << std::endl;
	for (size_t i = 0; i < _params.size(); ++i)
	{
		std::cout << "Param " << i << ": " << _params[i] << std::endl;
	}
	// Implementation of the invite command execution
}
