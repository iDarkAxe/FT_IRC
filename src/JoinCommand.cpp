#include "JoinCommand.hpp"
#include <sstream>

JoinCommand::JoinCommand(std::vector<std::string> params)
{
	_params = params;
}

// TODO: ERR_TOOMANYCHANNELS and ERR_UNAVAILRESOURCE and ERR_BADCHANMASK ??
// TODO: ban handling : ERR_BANNEDFROMCHAN

void JoinCommand::execute(Client* executor, NetworkState& network)
{
	if (_params.size() < 1) {
		// ERR_NEEDMOREPARAMS
		return;
	}
	(void)executor;
	(void)network;
	if (_params[0] == "0")
	{
		// Executor wants to leave all channels
		return;
	}
	std::vector<std::string> channel_names;
	std::vector<std::string> channel_keys;
	std::stringstream ss_1(_params[0]);
	std::string channel_name;
	std::string channel_key;
	char del = ',';
	while (getline(ss_1, channel_name, del))
		channel_names.push_back(channel_name);
	if (_params.size() > 2)
	{
		std::stringstream ss_2(_params[1]);
		while (getline(ss_2, channel_name, del))
			channel_keys.push_back(channel_key);
	}
	Channel* channel;
	for (size_t i = 0; i < channel_names.size(); ++i)
	{
		std::string chan_key;
		if (channel_keys.size() >= i)
			chan_key = channel_keys[i];
		else
			chan_key = "";
		channel = network.getChannel(channel_names[i]);
		if (!channel)
		{
			network.addChannel(channel_names[i]);
			channel = network.getChannel(channel_names[i]);
			channel->addClient(executor, true); // First user is operator
			continue;
		}
		// Channel exists
		if (channel->isClientInChannel(executor))
			continue; // Already in channel
		if (channel->getModes().is_invite_only)
		{
			// ERR_INVITEONLYCHAN
			continue;
		}
		if (channel->isKeySet(channel->getModes()))
		{
			if (!channel->isKeySame(chan_key))
			{
				// ERR_BADCHANNELKEY
				continue;
			}
			if (channel->getModes().is_limited && channel->getClients().size() >= channel->getUserLimit())
			{
				// ERR_CHANNELISFULL
				continue;
			}
			channel->addClient(executor);
			// RPL_TOPIC
			continue;
		}
		channel->addClient(executor);
		// RPL_TOPIC
	}
}
