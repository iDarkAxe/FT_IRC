#include "PassCommand.hpp"
#include "Server.hpp"

PassCommand::PassCommand(std::vector<std::string> params)
{
	_params = params;
}

void PassCommand::execute(Client* executor, NetworkState& network)
{
	(void)network;
	if (_params.empty() || _params[1].empty())
		// ERR_NEEDMOREPARAMS
	if (executor->_registered)
	{
		// ERR_ALREADYREGISTRED
	}

  if (executor->_password_correct)
    return; // si il a deja renseigne un mot de passe correct

	if (_params[1] == Server::getPassword())
	{
		// std::cout << "Correct password" << std::endl;
	  executor->_password_correct = true;
	} else {
 // 464    ERR_PASSWDMISMATCH
 		// Server::kick(executor); besoin de l'instance de server ici .. 
	}

	return;
}
