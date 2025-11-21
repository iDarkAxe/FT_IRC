#ifndef ACOMMAND_HPP
#define ACOMMAND_HPP

#include <iostream>
#include <vector>

enum command_type
{
	INVITE,
	KICK,
	CHANGE_TOPIC,
	MODE,
	SET_NICK,
	SET_USERNAME,
	AUTHENTICATE,
	JOIN,
	LEAVE,
	SEND_MESSAGE,
	PRIVATE_MESSAGE,
	LIST_CHANNELS,
	LIST_USERS,
	UNKNOWN,
};

enum param_type
{
	BOOL_PARAM,
	INT_PARAM,
	STRING_PARAM,
};

class ACommand
{
//= Variables =//
protected:
	std::vector<std::string> _params;

//= Methods =//
public:
	virtual ~ACommand() {};
	virtual void execute() = 0;
};

#endif
