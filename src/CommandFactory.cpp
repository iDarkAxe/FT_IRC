#include "CommandFactory.hpp"
#include "InviteCommand.hpp"

CommandFactory::~CommandFactory() {}
CommandFactory::CommandFactory() {}

CommandFactory& CommandFactory::getInstance() {
	static CommandFactory instance;
	return instance;
}

command_type CommandFactory::findType(std::string const& command_name) {
    if (command_name == "INVITE") return INVITE;
    return UNKNOWN;
}

ACommand* CommandFactory::createCommand(const std::string& command, const std::vector<std::string> &params)
{
	command_type cmdType = CommandFactory::findType(command);
	switch (cmdType)
	{
		case INVITE:
			return new InviteCommand(params);
		// case "KICK":
		// 	return new KickCommand(params);
		// case "CHANGE_TOPIC":
		// 	return new ChangeTopicCommand(params);
		// case "MODE":
		// 	return new ModeCommand(params);
		// case "SET_NICK":
		// 	return new SetNickCommand(params);
		// case "SET_USERNAME":
		// 	return new SetUsernameCommand(params);
		// case "AUTHENTICATE":
		// 	return new AuthenticateCommand(params);
		// case "JOIN":
		// 	return new JoinCommand(params);
		// case "LEAVE":
		// 	return new LeaveCommand(params);
		// case "SEND_MESSAGE":
		// 	return new SendMessageCommand(params);
		// case "PRIVATE_MESSAGE":
		// 	return new PrivateMessageCommand(params);
		// case "LIST_CHANNELS":
		// 	return new ListChannelsCommand(params);
		// case "LIST_USERS":
		// 	return new ListUsersCommand(params);
		default:
			return 0;
	}
}
