#include "NickCommand.hpp"
#include "Server.hpp"

NickCommand::NickCommand(std::vector<std::string> params)
{
	_params = params;
}

void NickCommand::execute(Client* executor, NetworkState& network)
{
	if (!executor->_password_correct)
		return;
	if (_params.empty())
		// ERR_NONICKNAMEGIVEN 
	if (_params[1].empty())
  {
    // ERR_ERRONEUSNICKNAME
    // Ca peut etre aussi des char interdits ... ou trop long 
      return; 
  }

	if (network.getClient(_params[1]))
	{
  // ERR_NICKNAMEINUSE 
    return;
	}

	// std::cout << "New nickname : " << _params[1] << std::endl;
  executor->_nickname = _params[1];

	return;
}

// ERR_NICKCOLLISION-> netword seulement
// ERR_UNAVAILRESOURCE  -> admin / root ...           
// ERR_RESTRICTED -> pour un statut de guest 
