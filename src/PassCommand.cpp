#include "PassCommand.hpp"
#include "Server.hpp"

PassCommand::PassCommand(std::vector<std::string> params)
{
	_params = params;
}

void PassCommand::execute(Client* executor, NetworkState& network)
{
	(void)network;
  if (executor->_password_correct)
    return; // si il a deja renseigne un mot de passe correct

	if (_params[0] == Server::getPassword())
	  executor->_password_correct = true;

	//apres 3 tentatives ratees on kick le client ?

	return;
}
