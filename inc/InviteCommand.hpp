#ifndef INVITECOMMAND_HPP
#define INVITECOMMAND_HPP

#include "ACommand.hpp"

class InviteCommand : public ACommand
{
//= Variables =//
protected:

//= Methods =//
public:
	InviteCommand(std::vector<std::string> params);
	~InviteCommand() {}
	std::vector<int> execute(Client* executor, NetworkState& network);
};

#endif  // INVITECOMMAND_HPP
