#include "NickCommand.hpp"
#include "Server.hpp"

NickCommand::NickCommand(std::vector<std::string> params)
{
	_params = params;
}

std::vector<int> NickCommand::execute(Client* executor, NetworkState& network)
{
	std::vector<int> vec;
	if (!executor->_password_correct)
	{
		vec.push_back(0); // on fait une erreur ?
		return vec;
	}
	if (_params.empty())
	{
		vec.push_back(431); // ERR_NONICKNAMEGIVEN
		return vec;
	}
	if (_params[1].empty())
  {
  	vec.push_back(432); //ERR_ERRONEUSNICKNAME
    // Ca peut etre aussi des char interdits ... ou trop long 
    return vec; 
  }

	if (network.getClient(_params[1]))
	{
		vec.push_back(433); // ERR_NICKNAMEINUSE 
    return vec;
	}

	// std::cout << "New nickname : " << _params[1] << std::endl;
  executor->_nickname = _params[1];
	vec.push_back(0);
	return vec;
}

// ERR_NICKCOLLISION-> netword seulement
// ERR_UNAVAILRESOURCE  -> admin / root ...           
// ERR_RESTRICTED -> pour un statut de guest 
