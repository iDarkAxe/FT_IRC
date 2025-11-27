#include "UserCommand.hpp"
#include "Server.hpp"

UserCommand::UserCommand(std::vector<std::string> params)
{
	_params = params;
}

void UserCommand::execute(Client* executor, NetworkState& network)
{
	(void)network;
	
	if (!executor->_password_correct)
		return;
	if (executor->_registered)
	{
    // ERR_ALREADYREGISTRED
		return;
	}

	if (_params.size() < 5) // on veut 0 et * quand meme ?
	{
		// ERR_NEEDMOREPARAMS
		return;
	}

	// std::cout << "New username : " << _params[1] << std::endl;
  executor->_username = _params[1];
  executor->_realname = _params[4];

	return;
}

