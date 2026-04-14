#ifndef SERVER_HPP
#define SERVER_HPP

#include <map>
#include <cstdio>
#include <csignal>
#include <netinet/in.h>

#include "Signals.hpp"
#include "ACommand.hpp"
#include "Client.hpp"
#include "Channel.hpp"
#include "EventHandler.hpp"

#ifdef __linux__
	#include "EpollHandler.hpp"
#elif defined(__APPLE__) || defined(__FreeBSD__)
	#include "KqueueHandler.hpp"
#else
	#error "Unsupported platform"
#endif

//= Debug options =//
#define PRINT_CORRECT_COMMANDS 0
#define PRINT_INCORRECT_COMMANDS 1

//= Intervals in seconds =//
#define FLUSH_CHANNEL_INTERVAL 5
#define PING_INTERVAL 5
#define PING_TIMEOUT 3

class ACommand;

class Server
{
private:
	typedef std::map<int, Client*> clientsType;			   //!< Type for clients
	typedef std::map<std::string, Channel *> channelsType; //!< Type for channels
	int _port;											   //!< Port number for the server
	std::string _password;								   //!< Password for the server
	clientsType clients;								   //!< Map of client socket to Client class
	int _server_socket;									   //!< Server socket file descriptor
	channelsType channels;								   //!< Map of channel name to Channel pointers
	EventHandler *event_loop;								   //!< Event loop for handling I/O events

public:
	Server(int port, std::string password);
	~Server();
	std::string &getPassword();
	int RunServer();
	int init_socket(void);
	void initClient(int client_fd, const std::string &ip_str, uint16_t port);
	
	// I/O
	void handle_events(int n);
	int read_client_fd(int fd);
	void verify_message_length(int fd);
	void print_line_error(int fd, std::string& line, size_t start, size_t len, size_t to_erase);
	int make_fd_nonblocking(int fd);

	// Clients managing
	void client_kicked(int fd);
	void new_client();
	void removeClient(int fd);
	void removeClient(Client *client);
	void client_quited(int fd);
	void remove_inactive_clients();
	void check_clients_ping();
	Client *getClient(const std::string &nickname);
	Channel *getChannel(const std::string &nickname);
	bool addChannel(const std::string &channel_name);
	bool removeChannel(const std::string &channel_name);
	void removeClientFromAllChannels(Client *client);

	void deleteUnusedChannels();
	// Parsing and execution of commands
	void is_authentification_complete(int fd);
	void interpret_msg(int fd);

	// Reply
	bool reply(Client *client, const std::string& message);
	bool replyChannel(Channel *channel, Client *sender, const std::string& message);
	bool broadcastChannel(Channel *channel, const std::string& message);
	bool broadcastChannelOnlyOP(Channel *channel, const std::string& message);
};

#endif // SERVER_HPP
