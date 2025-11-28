#include "PassCommand.hpp"
#include "LocalUser.hpp"
#include "Server.hpp"

PassCommand::PassCommand(std::vector<std::string> params)
{
	_params = params;
}

void PassCommand::execute(Client* executor, NetworkState& network, Server& server)
{
	(void)server;
	(void)network;

	if (_params.empty() || _params[1].empty())
	{
		//461 // ERR_NEEDMOREPARAMS
	}
	if (executor->_registered)
		//462 // ERR_ALREADYREGISTRED

  if (executor->_password_correct)
	{
		return;
	}

	if (_params[1] == Server::getPassword())
	{
		// std::cout << "Correct password" << std::endl;
	  executor->_password_correct = true;
	} else {
		server.reply(executor, "Invalid password");
		//464 //ERR_PASSWDMISMATCH
	}
	return;
}
