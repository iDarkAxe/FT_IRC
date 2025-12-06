#include "KickCommand.hpp"
#include "Channel.hpp"
#include "Server.hpp"

KickCommand::KickCommand(std::vector<std::string> params)
{
	_params = params;
}

// _params[0] -> #a,#b,#c 
// _params[1] -> nick,nick,nick
// _params[2] -> msg si il y en a un 

void KickCommand::execute(Client* executor, Server& server)
{
	if (!executor->isRegistered())
		return;

	if (_params.size() < 2)
	{
		server.reply(executor, ERR_NEEDMOREPARAMS(executor->getNickname(), "KICK"));
		return;
	}

	std::vector<std::string> chans;
	std::vector<std::string> users;
	std::string kick_msg = "";
	int count = 0;;
	for (size_t i = 1; i < _params.size(); ++i) {
    if(_params[i][0] != '#')
    	break;
    chans.push_back(_params[i]);
    count++;
	}
	for (size_t i = count; i < _params.size(); ++i) {
		if (_params[i][0] == ':')
		{
			kick_msg = _params[i];
			break;
		}
		users.push_back(_params[i]);
	}
	for (size_t i = 0; i < users.size(); ++i) {
		Channel* chan = server.getChannel(chans[i]);
		if (!chan || chans[i].empty() || (chans[i][0] != '#' && chans[i][0] != '&'))
		{
			server.reply(executor, ERR_NOSUCHCHANNEL(executor->getNickname(), _params[i]));
			continue;
		}
		if (!chan->isClientInChannel(executor))
		{
			server.reply(executor, ERR_NOSUCHCHANNEL(executor->getNickname(), _params[i]));
			continue;
		}
		if (!chan->isClientOPChannel(executor))
		{
			server.reply(executor, ERR_CHANOPRIVSNEEDED(executor->getNickname(), _params[i]));
			continue;
		}
		Client* target = server.getClient(users[i]);
		if (!chan->isClientInChannel(target))
		{
			server.reply(executor, ERR_USERNOTINCHANNEL(executor->getNickname(), users[i], chans[i]));
		}
		// std::stringstream ss;
		// ss << ":" << executor->getNickname() << "!~" << executor->getUsername() << "@" << executor.getIp() 
		// 	<< " KICK " << chan->getName() << target->getNickname() << " :" << target->getNickname();
		// server.replyChannel(chan, ss.str());
	}
	return;
}

// KICK #a,#b John,Mark :Raison du kick
//REPLY On chan :theNick!~theUser@46.231.218.157 KICK #Theonlychan otherNick :otherNick
