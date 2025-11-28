#include "TopicCommand.hpp"

TopicCommand::TopicCommand(std::vector<std::string> params)
{
	_params = params;
}

void TopicCommand::execute(Client* executor, Server& server)
{
	if (_params.size() < 2) {
		// ERR_NEEDMOREPARAMS
		return;
	}
	Channel* channel = server.getNetwork().getChannel(_params[0]);
	if (!channel) {
		// ERR_NOSUCHCHANNEL
		return;
	}
	if (channel->isClientInChannel(executor) == false) {
		// ERR_NOTONCHANNEL
		return;
	}
	if (_params.size() == 2)
	{
		if (channel->getTopic().empty()) {
			// RPL_NOTOPIC
		} else {
			// RPL_TOPIC
		}
		return;
	}
	std::string new_topic = _params[1];
	if (channel->getModes().is_topic_set_op_only && !channel->isClientOPChannel(executor)) {
		// ERR_CHANOPRIVSNEEDED
		return;
	}
	channel->setTopic(new_topic);
	// Notify all channel members about the topic change
	// example in RFC 
	// :WiZ!jto@tolsun.oulu.fi TOPIC #test :New topic
	// : ^servername 		   ^TOPIC ^channel ^new topic
}
