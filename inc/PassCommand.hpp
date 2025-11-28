#ifndef PASSCOMMAND_HPP
#define PASSCOMMAND_HPP

#include "ACommand.hpp"

class PassCommand : public ACommand
{
//= Variables =//
protected:

//= Methods =//
public:
	PassCommand(std::vector<std::string> params);
	~PassCommand() {};
	std::vector<int> execute(Client* executor, NetworkState& network);
};

#endif
