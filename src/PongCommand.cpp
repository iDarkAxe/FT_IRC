#include "PongCommand.hpp"
#include "Server.hpp"

PongCommand::PongCommand(std::vector<std::string> params)
{
	_params = params;
}

void PongCommand::execute(Client* executor, NetworkState& network, Server& server)
{
	(void)network;

	(void)server;
	//checker le timestamp ici
  std::time_t now = std::time(NULL);
  executor->_localClient->timeout = now + 5;
  executor->_localClient->last_ping = now;
  //debug
  std::cout << format_time() << " Pong from client " << executor->_localClient->fd << " recieved" << std::endl; 
}

