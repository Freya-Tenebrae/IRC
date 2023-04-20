/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaginot <cmaginot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 18:15:54 by cmaginot          #+#    #+#             */
/*   Updated: 2023/03/22 16:26:06 by cmaginot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INCL/User.hpp"
#include "../../INCL/Reply.hpp"
#include "../../INCL/Command.hpp"

// int Server::check_number_user_with_specific_mod(char mod)
// {
// 	int i = 0;

// 	for (std::vector<User *>::iterator it = _usr_list.begin(); it != _usr_list.end(); it++)
// 		if ((*it)->check_if_mode_is_used(mod) == true)
// 			i++;
// 	return (i);
// }

// bool Server::is_nickname_valid(std::string nickname)
// {
// 	std::string autorise_special_char = "0123456789`|^_-{}[]\\"; // valid char exept for begin
// 	if (nickname.compare("") == 0)
// 		return (false);
// 	for (std::string::iterator it = nickname.begin(); it != nickname.end(); it++)
// 	{
// 		if (!((*it >= 'a' && *it <= 'z') || (*it >= 'A' && *it <= 'Z') || \
// 			(autorise_special_char.find(*it) != std::string::npos && it != nickname.begin())))
// 			return (false);
// 	}
// 	return (true);
// }

// bool Server::is_nickname_free(std::string nickname)
// {
// 	for (std::vector<User *>::iterator it = _usr_list.begin(); it != _usr_list.end(); it++)
// 	{
// 		if ((*it)->get_nickname() == nickname)
// 			return (false);
// 	}
// 	return (true);
// }

// bool token_is_valid(std::string token)
// {
// 	(void)token;
// 	return (true);
// }

// std::vector<Reply>	Server::cap(User *user, std::vector<std::string> args)
// {
// 	std::vector<Reply> reply;
// 	(void)user;
// 	(void)args;

// 	return (reply);
// }
// /*
// Command: CAP
// Parameters: <subcommand> [:<capabilities>]

// The CAP command is used for capability negotiation between a server and a client.

// The CAP message may be sent from the server to the client.

// For the exact semantics of the CAP command and subcommands, please see the
// Capability Negotiation specification.
// (https://ircv3.net/specs/extensions/capability-negotiation.html)
// */

// std::vector<Reply>	Server::authenticate(User *user, std::vector<std::string> args)
// {
// 	std::vector<Reply> reply;
// 	(void)user;
// 	(void)args;
	
// 	return (reply);
// }
// /*
// Command: AUTHENTICATE

// The AUTHENTICATE command is used for SASL authentication between a server and 
// a client. The client must support and successfully negotiate the "sasl" client
// capability (as listed below in the SASL specifications) before using this command.

// The AUTHENTICATE message may be sent from the server to the client.

// For the exact semantics of the AUTHENTICATE command and negotiating support for
// the "sasl" client capability, please see the IRCv3.1 and IRCv3.2 SASL Authentication
// specifications.
// */

// std::vector<Reply>	Server::pass(User *user, std::vector<std::string> args)
// {
// 	std::vector<Reply>	reply;
// 	int 				password = 0;

// 	if (user->get_status() == USR_STAT_BAN)
// 		reply.push_back(ERR_YOUREBANNEDCREEP);
// 	else if (args.empty() == true || args[password].compare("") == 0)
// 	{
// 		reply.push_back(ERR_NEEDMOREPARAMS);
// 		reply[0].add_arg("PASS", "command");
// 	}
// 	else if (user->get_connected() == true)
// 		reply.push_back(ERR_ALREADYREGISTERED);
// 	else if (args[password].compare(this->_password))
// 		reply.push_back(ERR_PASSWDMISMATCH);
// 	else
// 	{
// 		user->set_connected();
// 		reply.push_back(NO_REPLY);
// 	}
// 	reply[0].add_user(user);
// 	reply[0].prep_to_send(1);
// 	return(reply);
// }
// /*
// Command: PASS
// Parameters: <password>

// The PASS command is used to set a ‘connection password’. If set, the password 
// must be set before any attempt to register the connection is made. This requires 
// that clients send a PASS command before sending the NICK / USER combination.

// The password supplied must match the one defined in the server configuration. 
// It is possible to send multiple PASS commands before registering but only the 
// last one sent is used for verification and it may not be changed once the client 
// has been registered.

// If the password supplied does not match the password expected by the server, 
// then the server SHOULD send ERR_PASSWDMISMATCH (464) and MAY then close the 
// connection with ERROR. Servers MUST send at least one of these two messages.

// Servers may also consider requiring SASL authentication upon connection as an 
// alternative to this, when more information or an alternate form of identity 
// verification is desired.

// Numeric replies:

// ERR_NEEDMOREPARAMS (461)
// ERR_ALREADYREGISTERED (462)
// ERR_PASSWDMISMATCH (464)
// */

// std::vector<Reply>	Server::nick(User *user, std::vector<std::string> args)
// {
// 	std::vector<Reply>	reply;
// 	int					nickname = 0;

// 	if (user->get_status() == USR_STAT_BAN)
// 		reply.push_back(ERR_YOUREBANNEDCREEP);
// 	else if (user->get_connected() == false)
// 		reply.push_back(ERR_NOTREGISTERED);
// 	else if (args.empty() == true || args[nickname].compare("") == 0)
// 		reply.push_back(ERR_NONICKNAMEGIVEN);
// 	else if (is_nickname_valid(args[nickname]) == false)
// 	{
// 		reply.push_back(ERR_ERRONEUSNICKNAME);
// 		reply[0].add_arg(args[0], "nick");
// 	}
// 	else if (args[nickname] == user->get_nickname())
// 		reply.push_back(ERR_ERROSAMENICKNAME);
// 	else if (is_nickname_free(args[nickname]) == false)
// 	{
// 		reply.push_back(ERR_NICKNAMEINUSE);
// 		reply[0].add_arg(args[0], "nick");
// 	}
// 	else
// 	{
// 		user->set_nickname(args[nickname]);
// 		reply.push_back(RPL_NICKSET);
// 		reply[0].add_arg(user->get_nickname(), "client");
// 	}
// 	reply[0].add_user(user);
// 	reply[0].prep_to_send(1); // or 0 ?
// 	return(reply);
// }
// /*
// Command: NICK
// Parameters: <nickname>

// The NICK command is used to give the client a nickname or change the previous one.

// If the server receives a NICK command from a client where the desired nickname 
// is already in use on the network, it should issue an ERR_NICKNAMEINUSE numeric 
// and ignore the NICK command.

// If the server does not accept the new nickname supplied by the client as valid 
// (for instance, due to containing invalid characters), it should issue an 
// ERR_ERRONEUSNICKNAME numeric and ignore the NICK command.

// If the server does not receive the <nickname> parameter with the NICK command, 
// it should issue an ERR_NONICKNAMEGIVEN numeric and ignore the NICK command.

// The NICK message may be sent from the server to clients to acknowledge their NICK 
// command was successful, and to inform other clients about the change of nickname. 
// In these cases, the <source> of the message will be the old 
// nickname [ [ "!" user ] "@" host ] of the user who is changing their nickname.

// Numeric Replies:

// ERR_NONICKNAMEGIVEN (431)
// ERR_ERRONEUSNICKNAME (432)
// ERR_NICKNAMEINUSE (433)
// ERR_NICKCOLLISION (436)
// */

// /*
// ERR_NICKCOLLISION (436) don't know what it is
// check return when sucess
// */

// std::vector<Reply>	Server::user(User *user, std::vector<std::string> args)
// {
// 	std::vector<Reply>	reply, reply_motd;
// 	std::vector<std::string> to_motd;
// 	std::string			realname_str = "";
// 	int 				username = 0;
// 	int					realname = 3;
// 	(void)args;

// 	if (user->get_status() == USR_STAT_BAN)
// 		reply.push_back(ERR_YOUREBANNEDCREEP);
// 	else if (user->get_connected() == false)
// 		reply.push_back(ERR_NOTREGISTERED);
// 	else if (args.empty() == true || args[username].compare("") == 0 || args.size() < 3)
// 		reply.push_back(ERR_NEEDMOREPARAMS);
// 	else if (user->get_status() == USR_STAT_REGISTERED)
// 		reply.push_back(ERR_ALREADYREGISTERED);
// 	else
// 	{
// 		for (size_t i = realname; i < args.size(); i++)
// 			realname_str.append(args[i]);
// 		realname_str.erase(realname_str.begin());
// 		// if (username_is_conform())
// 		user->set_username(args[username]);
// 		// else
// 		// 	user->set_username(user.get_nickname());
// 		// if (realname_is_conform())
// 		user->set_realname(realname_str);
// 		// else
// 		// 	user->set_realname(user.get_nickname());
// 		user->set_status(USR_STAT_REGISTERED);
// 		reply.push_back(RPL_WELCOME);
// 		reply[0].add_arg("", "networkname");
// 		reply[0].add_arg(user->get_nickname(), "nick");
// 		reply[0].add_arg(user->get_username(), "user");
// 		reply[0].add_arg(user->get_hostaddr(), "host");
// 		reply.push_back(RPL_YOURHOST);
// 		reply[1].add_arg(get_name(), "servername");
// 		reply[1].add_arg(get_version(), "version");
// 		reply.push_back(RPL_CREATED);
// 		reply[2].add_arg("", "datetime");
// 		reply.push_back(RPL_MYINFO);
// 		reply[3].add_arg(get_name(), "servername");
// 		reply[3].add_arg(get_version(), "version");
// 		reply[3].add_arg("", "available user modes");
// 		reply[3].add_arg("", "available channel modes");
// 		// do something with [<channel modes with a parameter>]
// 		reply.push_back(RPL_LUSERCLIENT);
// 		reply[4].add_arg(convert_int_to_string(_usr_list.size()), "u"); // number of user connected
// 		reply[4].add_arg(convert_int_to_string(check_number_user_with_specific_mod('i')), "i"); // number of invisible user
// 		reply[4].add_arg("1", "s"); // number of server = 1
// 		reply.push_back(RPL_LUSEROP);
// 		reply[5].add_arg(convert_int_to_string(check_number_user_with_specific_mod('o')), "ops"); // number of operators connected
// 		reply.push_back(RPL_LUSERUNKNOWN);
// 		reply[6].add_arg(convert_int_to_string(_usr_list.size()), "connections"); // number of connections = user ??
// 		reply.push_back(RPL_LUSERCHANNELS);
// 		reply[7].add_arg("", "channels"); // number of channel
// 		reply.push_back(RPL_LUSERME);
// 		reply[8].add_arg(convert_int_to_string(_usr_list.size()), "c"); // number of clients = user ??
// 		reply[8].add_arg("1", "s"); // number of server = 1
// 	}
// 	reply_motd = motd(user, to_motd);
// 	reply.insert(reply.end(), reply_motd.begin(), reply_motd.end());
// 	for (std::vector<Reply>::iterator it = reply.begin(); it != reply.end(); it++)
// 	{
// 		it->add_user(user);
// 		it->prep_to_send(1);
// 	}
// 	return (reply);
// }
// /*
// Command: USER
// Parameters: <username> 0 * <realname>

// The USER command is used at the beginning of a connection to specify the
// username and realname of a new user->

// It must be noted that <realname> must be the last parameter because it may
// contain SPACE (' ', 0x20) characters, and should be prefixed with a 
// colon (:) if required.

// Servers MAY use the Ident Protocol to look up the ‘real username’ of clients.
// If username lookups are enabled and a client does not have an Identity Server
// enabled, the username provided by the client SHOULD be prefixed by a tilde 
// ('~', 0x7E) to show that this value is user-set.

// The maximum length of <username> may be specified by the USERLEN RPL_ISUPPORT
// parameter. If this length is advertised, the username MUST be silently truncated
// to the given length before being used. The minimum length of <username> is 1, ie.
// it MUST NOT be empty. If it is empty, the server SHOULD reject the command with
// ERR_NEEDMOREPARAMS (even if an empty parameter is provided); otherwise it MUST
// use a default value instead.

// The second and third parameters of this command SHOULD be sent as one zero 
// ('0', 0x30) and one asterisk character ('*', 0x2A) by the client, as the meaning
// of these two parameters varies between different versions of the IRC protocol.

// Clients SHOULD use the nickname as a fallback value for <username> and <realname>
// when they don’t have a meaningful value to use.

// If a client tries to send the USER command after they have already completed
// registration with the server, the ERR_ALREADYREGISTERED reply should be sent
// and the attempt should fail.

// If the client sends a USER command after the server has successfully received
// a username using the Ident Protocol, the <username> parameter from this command
// should be ignored in favour of the one received from the identity server.

// Numeric Replies:

// ERR_NEEDMOREPARAMS (461)
// ERR_ALREADYREGISTERED (462)
// */

// std::vector<Reply>	Server::ping(User *user, std::vector<std::string> args)
// {
// 	std::vector<Reply>	reply;
// 	int 				token = 0;

// 	if (user->get_status() == USR_STAT_BAN)
// 		reply.push_back(ERR_YOUREBANNEDCREEP);
// 	else if (user->get_connected() == false)
// 		reply.push_back(ERR_NOTREGISTERED);
// 	else if (args.empty() == true || args[token].compare("") == 0)	// NEED TO SEE HOW TO IDENTIFY THE NICKNAME IN ARGS
// 		reply.push_back(ERR_NEEDMOREPARAMS);
// 	else if (token_is_valid(args[token]) == false)
// 		reply.push_back(ERR_NOORIGIN);
// 	else
// 	{
// 		reply.push_back(RPL_PONG);
// 		reply[0].add_arg(user->get_nickname(), "");
// 		return (reply);
// 	}
// 	reply[0].add_user(user);
// 	reply[0].add_arg("PING", "");
// 	return (reply);
// }
// /*
// Command: PING
// Parameters: <token>

// The PING command is sent by either clients or servers to check the other side
// of the connection is still connected and/or to check for connection latency,
// at the application layer.

// The <token> may be any non-empty string.
// str
// When receiving a PING message, clients or servers must reply to it with a PONG
// message with the same <token> value. This allows either to match PONG with the
// PING they reply to, for example to compute latency.

// Clients should not send PING during connection registration, though servers may
// accept it. Servers may send PING during connection registration and clients must
// reply to them.

// Older versions of the protocol gave specific semantics to the <token> and allowed
// an extra parameter; but these features are not consistently implemented and should
// not be relied on. Instead, the <token> should be treated as an opaque value by
// the receiver.

// Numeric Replies:

// ERR_NEEDMOREPARAMS (461)
// ERR_NOORIGIN (409)
// Deprecated Numeric Reply:

// ERR_NOSUCHSERVER (402)
// */

// std::vector<Reply>	Server::pong(User *user, std::vector<std::string> args)
// {
// 	std::vector<Reply>	reply;
// 	int 				token = 0;

// 	if (user->get_status() == USR_STAT_BAN)
// 		reply.push_back(ERR_YOUREBANNEDCREEP);
// 	else if (user->get_connected() == false)
// 		reply.push_back(ERR_NOTREGISTERED);
// 	else if (args.empty() == true || args[token].compare("") == 0)	// NEED TO SEE HOW TO IDENTIFY THE NICKNAME IN ARGS
// 		reply.push_back(ERR_NEEDMOREPARAMS);
// 	else if (token_is_valid(args[token]) == false)
// 		reply.push_back(ERR_NOORIGIN);
// 	else if (true == false) // check if token is the same
// 		reply.push_back(ERR_TOKENMISMATCH);
// 	else
// 	{
// 		reply.push_back(NO_REPLY);
// 		return (reply);
// 	}
// 	reply[0].add_user(user);
// 	reply[0].add_arg("PING", "");
// 	return (reply);
// }
// /*
// Command: PONG
// Parameters: [<server>] <token>

// The PONG command is used as a reply to PING commands, by both clients and servers.
// The <token> should be the same as the one in the PING message that triggered this PONG.

// Servers MUST send a <server> parameter, and clients SHOULD ignore it. It exists for
// historical reasons, and indicates the name of the server sending the PONG.
// Clients MUST NOT send a <server> parameter.

// Numeric Replies:

// None
// */

// std::vector<Reply>	Server::oper(User *user, std::vector<std::string> args)
// {
// 	std::vector<Reply> reply;
// 	if (*(args.begin()) == "" && (*(args.end()) == "" || args.size() == 0))
// 		reply.push_back(ERR_NEEDMOREPARAMS);
// 	else if (user->get_connected()) {
// 		if (args[1].compare(this->_password))		//temporary, need a adequate comparing value for password
// 			reply.push_back(ERR_PASSWDMISMATCH);
// 		else if (!args[0].compare(user->get_hostname()))	//temporary, need a adequate comparing value for hostname
// 			reply.push_back(ERR_NOOPERHOST);
// 		else
// 			reply.push_back(RPL_YOUREOPER);
// 	}
// 	return (reply);
// }
// /*
// Command: OPER
// Parameters: <name> <password>

// The OPER command is used by a normal user to obtain IRC operator privileges. Both
// parameters are required for the command to be successful.

// If the client does not send the correct password for the given name, the server
// replies with an ERR_PASSWDMISMATCH message and the request is not successful.

// If the client is not connecting from a valid host for the given name, the server
// replies with an ERR_NOOPERHOST message and the request is not successful.

// If the supplied name and password are both correct, and the user is connecting from
// a valid host, the RPL_YOUREOPER message is sent to the user-> The user will also
// receive a MODE message indicating their new user modes, and other messages may be sent.

// The <name> specified by this command is separate to the accounts specified by SASL
// authentication, and is generally stored in the IRCd configuration.

// Numeric Replies:

// ERR_NEEDMOREPARAMS (461)
// ERR_PASSWDMISMATCH (464)
// ERR_NOOPERHOST (491)
// RPL_YOUREOPER (381)
// */

// std::vector<Reply>	Server::quit(User *user, std::vector<std::string> args)
// {
// 	std::vector<Reply> reply;
// 	(void)user;
// 	(void)args;
	
// 	return (reply);
// }
// /*
// Command: QUIT
// Parameters: [<reason>]

// The QUIT command is used to terminate a client’s connection to the server.
// The server acknowledges this by replying with an ERROR message and closing the
// connection to the client.

// This message may also be sent from the server to a client to show that a client
// has exited from the network. This is typically only dispatched to clients that
// share a channel with the exiting user-> When the QUIT message is sent to clients,
// <source> represents the client that has exited the network.

// When connections are terminated by a client-sent QUIT command, servers SHOULD
// prepend <reason> with the ASCII string "Quit: " when sending QUIT messages to
// other clients, to represent that this user terminated the connection themselves.
// This applies even if <reason> is empty, in which case the reason sent to other
// clients SHOULD be just this "Quit: " string. However, clients SHOULD NOT change
// behaviour based on the prefix of QUIT message reasons, as this is not required
// behaviour from servers.

// When a netsplit (the disconnecting of two servers) occurs, a QUIT message is
// generated for each client that has exited the network, distributed in the same
// way as ordinary QUIT messages. The <reason> on these QUIT messages SHOULD be
// composed of the names of the two servers involved, separated by a SPACE (' ', 0x20).
// The first name is that of the server which is still connected and the second name
// is that of the server which has become disconnected. If servers wish to hide or
// obscure the names of the servers involved, the <reason> on these messages MAY also
// be the literal ASCII string "*.net *.split" (i.e. the two server names are replaced
// with "*.net" and "*.split"). Software that implements the IRCv3 batch Extension
// should also look at the netsplit and netjoin batch types.

// If a client connection is closed without the client issuing a QUIT command to the
// server, the server MUST distribute a QUIT message to other clients informing them
// of this, distributed in the same was an ordinary QUIT message. Servers MUST fill
// <reason> with a message reflecting the nature of the event which caused it to happen.
// For instance, "Ping timeout: 120 seconds", "Excess Flood", and "Too many connections
// from this IP" are examples of relevant reasons for closing or for a connection with
// a client to have been closed.

// Numeric Replies:

// None
// */

// std::vector<Reply>	Server::error(User *user, std::vector<std::string> args)
// {
// 	std::vector<Reply> reply;
// 	(void)user;
// 	(void)args;
	
// 	return (reply);
// }
// /*
// Command: ERROR
// Parameters: <reason>

// This message is sent from a server to a client to report a fatal error, before
// terminating the client’s connection.

// This MUST only be used to report fatal errors. Regular errors should use the appropriate
// numerics or the IRCv3 standard replies framework.

// Numeric Replies:

// None
// Command Example:
// */

// std::vector<Reply> Server::join(User *user, std::vector<std::string> args)
// {
// 	std::vector<Reply> reply;
// 	(void)user;
// 	(void)args;
	
// 	return (reply);
// }
// /*
// Command: JOIN
// Parameters: <channel>{,<channel>} [<key>{,<key>}]
// Alt Params: 0

// The JOIN command indicates that the client wants to join the given channel(s),
// each channel using the given key for it. The server receiving the command checks
// whether or not the client can join the given channel, and processes the request.
// Servers MUST process the parameters of this command as lists on incoming commands
// from clients, with the first <key> being used for the first <channel>, the
// second <key> being used for the second <channel>, etc.

// While a client is joined to a channel, they receive all relevant information
// about that channel including the JOIN, PART, KICK, and MODE messages affecting
// the channel. They receive all PRIVMSG and NOTICE messages sent to the channel,
// and they also receive QUIT messages from other clients joined to the same channel
// (to let them know those users have left the channel and the network).
// This allows them to keep track of other channel members and channel modes.

// If a client’s JOIN command to the server is successful, the server MUST send,
// in this order:

// A JOIN message with the client as the message <source> and the channel they have
// joined as the first parameter of the message.
// The channel’s topic (with RPL_TOPIC (332) and optionally RPL_TOPICWHOTIME (333)),
// and no message if the channel does not have a topic.
// A list of users currently joined to the channel (with one or more RPL_NAMREPLY (353)
// numerics followed by a single RPL_ENDOFNAMES (366) numeric). These RPL_NAMREPLY
// messages sent by the server MUST include the requesting client that has just joined
// the channel.
// The key, client limit , ban - exception, invite-only - exception, and other
// (depending on server software) channel modes affect whether or not a given client
// may join a channel. More information on each of these modes and how they affect
// the JOIN command is available in their respective sections.

// Servers MAY restrict the number of channels a client may be joined to at one time.
// This limit SHOULD be defined in the CHANLIMIT RPL_ISUPPORT parameter. If the
// client cannot join this channel because they would be over their limit, they
// will receive an ERR_TOOMANYCHANNELS (405) reply and the command will fail.

// Note that this command also accepts the special argument of ("0", 0x30) instead
// of any of the usual parameters, which requests that the sending client leave all
// channels they are currently connected to. The server will process this command as
// though the client had sent a PART command for each channel they are a member of.

// This message may be sent from a server to a client to notify the client that someone
// has joined a channel. In this case, the message <source> will be the client who is
// joining, and <channel> will be the channel which that client has joined. Servers
// SHOULD NOT send multiple channels in this message to clients, and SHOULD distribute
// these multiple-channel JOIN messages as a series of messages with a single channel
// name on each.

// Numeric Replies:

// ERR_NEEDMOREPARAMS (461)
// ERR_NOSUCHCHANNEL (403)
// ERR_TOOMANYCHANNELS (405)
// ERR_BADCHANNELKEY (475)
// ERR_BANNEDFROMCHAN (474)
// ERR_CHANNELISFULL (471)
// ERR_INVITEONLYCHAN (473)
// ERR_BADCHANMASK (476)
// RPL_TOPIC (332)
// RPL_TOPICWHOTIME (333)
// RPL_NAMREPLY (353)
// RPL_ENDOFNAMES (366)

// Command Examples:

//   JOIN #foobar                    ; join channel #foobar.

//   JOIN &foo fubar                 ; join channel &foo using key "fubar".

//   JOIN #foo,&bar fubar            ; join channel #foo using key "fubar"
// 								  and &bar using no key.

//   JOIN #foo,#bar fubar,foobar     ; join channel #foo using key "fubar".
// 								  and channel #bar using key "foobar".

//   JOIN #foo,#bar                  ; join channels #foo and #bar.

// Message Examples:

//   :WiZ JOIN #Twilight_zone        ; WiZ is joining the channel
// 								  #Twilight_zone

//   :dan-!d@localhost JOIN #test    ; dan- is joining the channel #test
// */

// std::vector<Reply>	Server::part(User *user, std::vector<std::string> args)
// {
// 	std::vector<Reply> reply;
// 	(void)user;
// 	(void)args;
	
// 	return (reply);
// }
// /*
// Command: PART
// Parameters: <channel>{,<channel>} [<reason>]

// The PART command removes the client from the given channel(s).
// On sending a successful PART command, the user will receive a PART message from
// the server for each channel they have been removed from. <reason> is the reason
// that the client has left the channel(s).

// For each channel in the parameter of this command, if the channel exists and the
// client is not joined to it, they will receive an ERR_NOTONCHANNEL (442) reply and
// that channel will be ignored. If the channel does not exist, the client will
// receive an ERR_NOSUCHCHANNEL (403) reply and that channel will be ignored.

// This message may be sent from a server to a client to notify the client that
// someone has been removed from a channel. In this case, the message <source> will
// be the client who is being removed, and <channel> will be the channel which that
// client has been removed from. Servers SHOULD NOT send multiple channels in this
// message to clients, and SHOULD distribute these multiple-channel PART messages as
// a series of messages with a single channel name on each. If a PART message is
// distributed in this way, <reason> (if it exists) should be on each of these messages.

// Numeric Replies:

// ERR_NEEDMOREPARAMS (461)
// ERR_NOSUCHCHANNEL (403)
// ERR_NOTONCHANNEL (442)
// Command Examples:

//   PART #twilight_zone             ; leave channel "#twilight_zone"

//   PART #oz-ops,&group5            ; leave both channels "&group5" and
// 								  "#oz-ops".
// Message Examples:

//   :dan-!d@localhost PART #test    ; dan- is leaving the channel #test
// */

// std::vector<Reply>	Server::topic(User *user, std::vector<std::string> args)
// {
// 	std::vector<Reply> reply;
// 	(void)user;
// 	(void)args;
	
// 	return (reply);
// }
// /*
// Command: TOPIC
// Parameters: <channel> [<topic>]

// The TOPIC command is used to change or view the topic of the given channel.
// If <topic> is not given, either RPL_TOPIC or RPL_NOTOPIC is returned specifying
// the current channel topic or lack of one. If <topic> is an empty string, the topic
// for the channel will be cleared.

// If the client sending this command is not joined to the given channel, and tries to
// view its’ topic, the server MAY return the ERR_NOTONCHANNEL (442) numeric and have
// the command fail.

// If RPL_TOPIC is returned to the client sending this command, RPL_TOPICWHOTIME SHOULD
// also be sent to that client.

// If the protected topic mode is set on a channel, then clients MUST have appropriate
// channel permissions to modify the topic of that channel. If a client does not have
// appropriate channel permissions and tries to change the topic, the
// ERR_CHANOPRIVSNEEDED (482) numeric is returned and the command will fail.

// If the topic of a channel is changed or cleared, every client in that channel
// (including the author of the topic change) will receive a TOPIC command with the new
// topic as argument (or an empty argument if the topic was cleared) alerting them to how
// the topic has changed.

// Clients joining the channel in the future will receive a RPL_TOPIC numeric (or lack
// thereof) accordingly.

// Numeric Replies:

// ERR_NEEDMOREPARAMS (461)
// ERR_NOSUCHCHANNEL (403)
// ERR_NOTONCHANNEL (442)
// ERR_CHANOPRIVSNEEDED (482)
// RPL_NOTOPIC (331)
// RPL_TOPIC (332)
// RPL_TOPICWHOTIME (333)
// Command Examples:

//   TOPIC #test :New topic          ; Setting the topic on "#test" to
// 								  "New topic".

//   TOPIC #test :                   ; Clearing the topic on "#test"

//   TOPIC #test                     ; Checking the topic for "#test"
// */

// std::vector<Reply>	Server::names(User *user, std::vector<std::string> args)
// {
// 	std::vector<Reply> reply;
// 	(void)user;
// 	(void)args;
	
// 	return (reply);
// }
// /*
// Command: NAMES
// Parameters: <channel>{,<channel>}

// The NAMES command is used to view the nicknames joined to a channel and their channel membership prefixes. The param of this command is a list of channel names, delimited by a comma (",", 0x2C) character.

// The channel names are evaluated one-by-one. For each channel that exists and they are able to see the users in, the server returns one of more RPL_NAMREPLY numerics containing the users joined to the channel and a single RPL_ENDOFNAMES numeric. If the channel name is invalid or the channel does not exist, one RPL_ENDOFNAMES numeric containing the given channel name should be returned. If the given channel has the secret channel mode set and the user is not joined to that channel, one RPL_ENDOFNAMES numeric is returned. Users with the invisible user mode set are not shown in channel responses unless the requesting client is also joined to that channel.

// Servers MAY allow more than one target channel. They can advertise the maximum the number of target users per NAMES command via the TARGMAX RPL_ISUPPORT parameter.

// Numeric Replies:

// RPL_NAMREPLY (353)
// RPL_ENDOFNAMES (366)
// */

// std::vector<Reply> Server::list(User *user, std::vector<std::string> args)
// {
// 	std::vector<Reply> reply;
// 	(void)user;
// 	(void)args;
	
// 	return (reply);
// }
// /*
// Command: LIST
// Parameters: [<channel>{,<channel>}] [<elistcond>{,<elistcond>}]

// The LIST command is used to get a list of channels along with some information
// about each channel. Both parameters to this command are optional as they have
// different syntaxes.

// The first possible parameter to this command is a list of channel names, delimited
// by a comma (",", 0x2C) character. If this parameter is given, the information for
// only the given channels is returned. If this parameter is not given, the information
// about all visible channels (those not hidden by the secret channel mode rules) is
// returned.

// The second possible parameter to this command is a list of conditions as defined in
// the ELIST RPL_ISUPPORT parameter, delimited by a comma (",", 0x2C) character.
// Clients MUST NOT submit an ELIST condition unless the server has explicitly defined
// support for that condition with the ELIST token. If this parameter is supplied, the
// server filters the returned list of channels with the given conditions as specified
// in the ELIST documentation.

// In response to a successful LIST command, the server MAY send one RPL_LISTSTART
// numeric, MUST send back zero or more RPL_LIST numerics, and MUST send back one
// RPL_LISTEND numeric.

// Numeric Replies:

// RPL_LISTSTART (321)
// RPL_LIST (322)
// RPL_LISTEND (323)
// Command Examples:

//   LIST                            ; Command to list all channels

//   LIST #twilight_zone,#42         ; Command to list the channels
// 								  "#twilight_zone" and "#42".

//   LIST >3                         ; Command to list all channels with
// 								  more than three users.

//   LIST C>60                       ; Command to list all channels with
// 								  created at least 60 minutes ago

//   LIST T<60                       ; Command to list all channels with
// 								  a topic changed within the last 60 minutes
// */

// std::vector<Reply>	Server::invite(User *user, std::vector<std::string> args)
// {
// 	std::vector<Reply>	reply;
// 	(void)user;
// 	(void)args;
	
// 	return (reply);
// }
// /*
// Command: INVITE
// Parameters: <nickname> <channel>

// The INVITE command is used to invite a user to a channel. The parameter
// <nickname> is the nickname of the person to be invited to the target channel <channel>.

// The target channel SHOULD exist (at least one user is on it). Otherwise,
// the server SHOULD reject the command with the ERR_NOSUCHCHANNEL numeric.

// Only members of the channel are allowed to invite other users. Otherwise,
// the server MUST reject the command with the ERR_NOTONCHANNEL numeric.

// Servers MAY reject the command with the ERR_CHANOPRIVSNEEDED numeric.
// In particular, they SHOULD reject it when the channel has invite-only mode set,
// and the user is not a channel operator.

// If the user is already on the target channel, the server MUST reject the command
// with the ERR_USERONCHANNEL numeric.

// When the invite is successful, the server MUST send a RPL_INVITING numeric to the
// command issuer, and an INVITE message, with the issuer as <source>, to the target
// user-> Other channel members SHOULD NOT be notified.

// Numeric Replies:

// RPL_INVITING (341)
// ERR_NEEDMOREPARAMS (461)
// ERR_NOSUCHCHANNEL (403)
// ERR_NOTONCHANNEL (442)
// ERR_CHANOPRIVSNEEDED (482)
// ERR_USERONCHANNEL (443)
// Command Examples:

//   INVITE Wiz #foo_bar    ; Invite Wiz to #foo_bar
// Message Examples:

//   :dan-!d@localhost INVITE Wiz #test    ; dan- has invited Wiz
// 										to the channel #test
// */

// std::vector<Reply>	Server::kick(User *user, std::vector<std::string> args)
// {
// 	std::vector<Reply> reply;
// 	(void)user;
// 	(void)args;
	
// 	return (reply);
// }
// /*
// Command: KICK
// Parameters: <channel> <user> *( "," <user> ) [<comment>]

// The KICK command can be used to request the forced removal of a user from a channel.
// It causes the <user> to be removed from the <channel> by force. If no comment
// is given, the server SHOULD use a default message instead.

// The server MUST NOT send KICK messages with multiple users to clients. This is
// necessary to maintain backward compatibility with existing client software.

// Servers MAY limit the number of target users per KICK command via the TARGMAX
// parameter of RPL_ISUPPORT, and silently drop targets if the number of targets
// exceeds the limit.

// Numeric Replies:

// ERR_NEEDMOREPARAMS (461)
// ERR_NOSUCHCHANNEL (403)
// ERR_CHANOPRIVSNEEDED (482)
// ERR_USERNOTINCHANNEL (441)
// ERR_NOTONCHANNEL (442)
// Deprecated Numeric Reply:

// ERR_BADCHANMASK (476)
// Examples:

//    KICK #Finnish Matthew           ; Command to kick Matthew from
// 								   #Finnish

//    KICK &Melbourne Matthew         ; Command to kick Matthew from
// 								   &Melbourne

//    KICK #Finnish John :Speaking English
// 								   ; Command to kick John from #Finnish
// 								   using "Speaking English" as the
// 								   reason (comment).

//    :WiZ!jto@tolsun.oulu.fi KICK #Finnish John
// 								   ; KICK message on channel #Finnish
// 								   from WiZ to remove John from channel
// */

// std::vector<Reply>	Server::motd(User *user, std::vector<std::string> args)
// {
// 	std::vector<Reply>	reply;
// 	int 				target = 0;
// 	int					i = 0;

// 	if (user->get_status() == USR_STAT_BAN)
// 		reply.push_back(ERR_YOUREBANNEDCREEP);
// 	else if (user->get_connected() == false)
// 		reply.push_back(ERR_NOTREGISTERED);
// 	else if (args.empty() != true && args[target].compare("") != 0 && _name.compare(args[target]) != 0)
// 		reply.push_back(ERR_NOSUCHSERVER);
// 	else
// 	{
// 		if (_modt.empty() == true)
// 			reply.push_back(ERR_NOMOTD);
// 		else
// 		{
// 			reply.push_back(RPL_MOTDSTART);
// 			reply[0].add_arg(get_name(), "server");
// 			for (std::vector<std::string>::iterator it = _modt.begin(); it != _modt.end(); it++)
// 			{
// 				++i;
// 				reply.push_back(RPL_MOTD);
// 				reply[i].add_arg(*it, "line of the motd");
// 			}
// 			reply.push_back(RPL_ENDOFMOTD);
// 		}
// 	}
// 	return (reply);
// }
// /*
// Command: MOTD
// Parameters: [<target>]

// The MOTD command is used to get the “Message of the Day” of the given server.
// If <target> is not given, the MOTD of the server the client is connected to
// should be returned.

// If <target> is a server, the MOTD for that server is requested. If <target> is
// given and a matching server cannot be found, the server will respond with the
// ERR_NOSUCHSERVER numeric and the command will fail.

// If the MOTD can be found, one RPL_MOTDSTART numeric is returned, followed by one
// or more RPL_MOTD numeric, then one RPL_ENDOFMOTD numeric.

// If the MOTD does not exist or could not be found, the ERR_NOMOTD numeric is returned.

// Numeric Replies:

// ERR_NOSUCHSERVER (402)
// ERR_NOMOTD (422)
// RPL_MOTDSTART (375)
// RPL_MOTD (372)
// RPL_ENDOFMOTD (376)
// */

// std::vector<Reply>	Server::version(User *user, std::vector<std::string> args)
// {
// 	std::vector<Reply>	reply;
// 	int 				target = 0;

// 	if (args.empty() != true && args[target].compare("") != 0 && _name.compare(args[target]) != 0)
// 		reply.push_back(ERR_NOSUCHSERVER);
// 	else {
// 		if (this->_name.compare(args[target])) {
// 			reply.push_back(RPL_VERSION);
// 			reply.push_back(RPL_ISUPPORT);		//to see how to match the target's version
// 		}
// 		else if (user->get_username().compare(args[target]))	// to see with a correct client name
// 			reply.push_back(RPL_ISUPPORT);
// 	}
// 	return (reply);
// }
// /*
// Command: VERSION
// Parameters: [<target>]

// The VERSION command is used to query the version of the software and the 
// RPL_ISUPPORT parameters of the given server. If <target> is not given, the 
// information for the server the client is connected to should be returned.

// If <target> is a server, the information for that server is requested. If 
// <target> is a client, the information for the server that client is connected 
// to is requested. If <target> is given and a matching server cannot be found, 
// the server will respond with the ERR_NOSUCHSERVER numeric and the command will fail.

// Wildcards are allowed in the <target> parameter.

// Upon receiving a VERSION command, the given server SHOULD respond with one 
// RPL_VERSION reply and one or more RPL_ISUPPORT replies.

// Numeric Replies:

// ERR_NOSUCHSERVER (402)
// RPL_ISUPPORT (005)
// RPL_VERSION (351)
// */

// std::vector<Reply>	Server::admin(User *user, std::vector<std::string> args)
// {
// 	std::vector<Reply> reply;
	
// 	if (args.empty() == true) {
// 		if (user->get_connected()) {
// 			reply.push_back(RPL_ADMINME);
// 			reply.push_back(RPL_ADMINLOC1);
// 			reply.push_back(RPL_ADMINLOC2);
// 			reply.push_back(RPL_ADMINEMAIL);
// 		}
// 	}
// 	else
// 		reply.push_back(ERR_NOSUCHSERVER);
// 	return (reply);
// }
// /*
// Command: ADMIN
// Parameters: [<target>]

// The ADMIN command is used to find the name of the administrator
// of the given server. If <target> is not given, the information
// for the server the client is connected to should be returned.

// If <target> is a server, the information for that server is requested.
// If <target> is a client, the information for the server that client is
// connected to is requested. If <target> is given and a matching server
// cannot be found, the server will respond with the ERR_NOSUCHSERVER
// numeric and the command will fail.

// Wildcards are allowed in the <target> parameter.

// Upon receiving an ADMIN command, the given server SHOULD respond with
// the RPL_ADMINME, RPL_ADMINLOC1, RPL_ADMINLOC2, and RPL_ADMINEMAIL replies.

// Numeric Replies:

// ERR_NOSUCHSERVER (402)
// RPL_ADMINME (256)
// RPL_ADMINLOC1 (257)
// RPL_ADMINLOC2 (258)
// RPL_ADMINEMAIL (259)
// */

// std::vector<Reply>	Server::connect(User *user, std::vector<std::string> args) // do not use, no connection between server in subject
// {
// 	std::vector<Reply> reply;
// 	(void)user;
// 	(void)args;
	
// 	return (reply);
// 	// do nothing is command connect is called (not required in subject)
// }
// /*
// Command: CONNECT
// Parameters: <target server> [<port> [<remote server>]]

// The CONNECT command forces a server to try to establish a new connection
// to another server. CONNECT is a privileged command and is available only
// to IRC Operators. If a remote server is given, the connection is attempted
// by that remote server to <target server> using <port>.

// Numeric Replies:

// ERR_NOSUCHSERVER (402)
// ERR_NEEDMOREPARAMS (461)
// ERR_NOPRIVILEGES (481)
// ERR_NOPRIVS (723)
// */

// std::vector<Reply>	Server::lusers(User *user, std::vector<std::string> args)
// {
// 	std::vector<Reply> reply;

// 	std::vector<User *>::iterator		it = this->_usr_list.begin();
// 	// Ici pb avec std c98, fix svp
// 	(void)user;
// 	if (args.empty() == true) {
// 		reply.push_back(RPL_LUSERCLIENT);
// 		while (it != this->_usr_list.end())
// 			std::cout << (*it)->get_username() << std::endl;		// put the list of username of the usrs to compare
// 		reply.push_back(RPL_LUSERME);
// 	}
// 	else
// 		reply.push_back(RPL_LUSERUNKNOWN);
// 	return (reply);
// }
// /*
// Command: LUSERS
// Parameters: None

// Returns statistics about local and global users, as numeric replies.

// Servers MUST reply with RPL_LUSERCLIENT and RPL_LUSERME, and SHOULD
// also include all those defined below.

// Clients SHOULD NOT try to parse the free-form text in the trailing
// parameter, and rely on specific parameters instead.

// RPL_LUSERCLIENT (251)
// RPL_LUSEROP (252)
// RPL_LUSERUNKNOWN (253)
// RPL_LUSERCHANNELS (254)
// RPL_LUSERME (255)
// RPL_LOCALUSERS (265)
// RPL_GLOBALUSERS (266)
// */

// std::vector<Reply>	Server::time(User *user, std::vector<std::string> args)
// {
// 	std::vector<Reply> reply;
// 	int					target = 0;
// 	(void)user;

// 	if (args.empty() == true || args[target].compare(this->_name))
// 		reply.push_back(RPL_TIME);
// 	else
// 		reply.push_back(ERR_NOSUCHSERVER);
// 	return (reply);
// }
// /*
// Command: TIME
// Parameters: [<server>]

// The TIME command is used to query local time from the specified server.
// If the server parameter is not given, the server handling the command
// must reply to the query.

// Numeric Replies:

// ERR_NOSUCHSERVER (402)
// RPL_TIME (391)

// */

// std::vector<Reply>	Server::stats(User *user, std::vector<std::string> args)
// {
// 	std::vector<Reply> reply;
// 	(void)user;
// 	(void)args;

// 	return (reply);
// }
// /*
// Command: STATS
// Parameters: <query> [<server>]

// The STATS command is used to query statistics of a certain server.
// The specific queries supported by this command depend on the server
// that replies, although the server must be able to supply information
// as described by the queries below (or similar).

// A query may be given by any single letter which is only checked by the
// destination server and is otherwise passed on by intermediate servers,
// ignored and unaltered.

// The following queries are those found in current IRC implementations and
// provide a large portion of the setup and runtime information for that server.
// All servers should be able to supply a valid reply to a STATS query which is
// consistent with the reply formats currently used and the purpose of the query.

// The currently supported queries are:

// c - returns a list of servers which the server may connect to or allow connections from;
// h - returns a list of servers which are either forced to be treated as leaves or
// 		allowed to act as hubs;
// i - returns a list of hosts which the server allows a client to connect from;
// k - returns a list of banned username/hostname combinations for that server;
// l - returns a list of the server’s connections, showing how long each connection has
// 		been established and the traffic over that connection in bytes and messages for
// 		each direction;
// m - returns a list of commands supported by the server and the usage count for each if
// 		the usage count is non zero;
// o - returns a list of hosts from which normal clients may become operators;
// u - returns a string showing how long the server has been up.
// y - show Y (Class) lines from server’s configuration file;

// Need to give this a good look-over. It's probably quite incorrect.

// Numeric Replies:

// ERR_NOSUCHSERVER (402)
// ERR_NEEDMOREPARAMS (461)
// ERR_NOPRIVILEGES (481)
// ERR_NOPRIVS (723)
// RPL_STATSCLINE (213)
// RPL_STATSHLINE (244)
// RPL_STATSILINE (215)
// RPL_STATSKLINE (216)
// RPL_STATSLLINE (241)
// RPL_STATSOLINE (243)
// RPL_STATSLINKINFO (211)
// RPL_STATSUPTIME (242)
// RPL_STATSCOMMANDS (212)
// RPL_ENDOFSTATS (219)
// */

// std::vector<Reply>	Server::help(User *user, std::vector<std::string> args)
// {
// 	std::vector<Reply> reply;

// 	if (user->get_connected() == true) {
// 		if (args.size() == 0) {
// 			reply.push_back(RPL_HELPSTART);
// 			reply.push_back(RPL_ENDOFHELP);
// 		}
// 		else if (args.size() == 1) {
// 			reply.push_back(RPL_HELPSTART);
// 			while (user->get_status())			// temporary :  while help text is shown, need client/user treatment for it ?
// 				reply.push_back(RPL_HELPTXT);
// 			reply.push_back(RPL_ENDOFHELP);
// 		}
// 		else
// 			reply.push_back(ERR_HELPNOTFOUND);
// 	}
// 	return (reply);
// }
// /*
// Command: HELP
// Parameters: [<subject>]

// The HELP command is used to return documentation about the IRC server and the IRC
// commands it implements.

// When receiving a HELP command, servers MUST either: reply with a single
// ERR_HELPNOTFOUND (524) message; or reply with a single RPL_HELPSTART (704)
// message, then arbitrarily many RPL_HELPTXT (705) messages, then a single
// RPL_ENDOFHELP (706). Servers MAY return the RPL_HELPTXT (705) form for unknown
// subjects, especially if their reply would not fit in a single line.

// The RPL_HELPSTART (704) message SHOULD be some sort of title and the first
// RPL_HELPTXT (705) message SHOULD be empty. This is what most servers do today.

// Servers MAY define any <subject> they want. Servers typically have documentation
// for most of the IRC commands they support.

// Clients SHOULD gracefully handle older servers that reply to HELP with a set of
// NOTICE messages. On these servers, the client may try sending the HELPOP command
// (with the same syntax specified here), which may return the numeric-based reply.

// Clients SHOULD also gracefully handle servers that reply to HELP with a set of
// 290/291/292/293/294/295 numerics.

// Numerics:

// ERR_HELPNOTFOUND (524)
// RPL_HELPSTART (704)
// RPL_HELPTXT (705)
// RPL_ENDOFHELP (706)
// */

// std::vector<Reply>	Server::info(User *user, std::vector<std::string> args)
// {
// 	(void)user;
// 	std::vector<Reply> reply;

// 	if (args.size() == 0) {
// 		reply.push_back(RPL_INFO);
// 		reply.push_back(RPL_ENDOFINFO);
// 	}
// 	return (reply);
// }
// /*
// Command: INFO
// Parameters: None
// The INFO command is used to return information which describes the server.
// This information usually includes the software name/version and its authors.
// Some other info that may be returned includes the patch level and compile date
// of the server, the copyright on the server software, and whatever miscellaneous
// information the server authors consider relevant.

// Upon receiving an INFO command, the server will respond with zero or more RPL_INFO
// replies, followed by one RPL_ENDOFINFO numeric.

// Numeric Replies:

// RPL_INFO (371)
// RPL_ENDOFINFO (374)
// */

// std::vector<Reply>	Server::mode(User *user, std::vector<std::string> args)
// {
// 	std::vector<Reply> reply;
// 	int target = 0;
// 	int modestring = 1;
// 	(void)args;

// 	if (user->get_status() == USR_STAT_BAN)
// 		reply.push_back(ERR_YOUREBANNEDCREEP);
// 	else if (user->get_connected() == false)
// 		reply.push_back(ERR_NOTREGISTERED);
// 	else if (args.empty() == true || args[target].compare("") == 0)
// 		reply.push_back(ERR_NEEDMOREPARAMS);
// 	else
// 	{
// 		for (int i = 0; i < args.size() - 1; i + 2)
// 		{
// 			if (args[i + target][0] == '#' || args[i + target][0] == '&')
// 			{
// 				// for channel
// 			}
// 			else
// 			{
// 				// for user
// 			}
// 		}
// 	}
// 	for (std::vector<Reply>::iterator it = reply.begin(); it != reply.end(); it++)
// 	{
// 		it->add_user(user);
// 		it->prep_to_send(1);
// 	}
// 	return (reply);
// }

// /*
// Command: MODE
// Parameters: <target> [<modestring> [<mode arguments>...]]

// The MODE command is used to set or remove options (or modes) from a given target.

// User mode
// If <target> is a nickname that does not exist on the network, the ERR_NOSUCHNICK (401)
// numeric is returned. If <target> is a different nick than the user who sent the command,
// the ERR_USERSDONTMATCH (502) numeric is returned.

// If <modestring> is not given, the RPL_UMODEIS (221) numeric is sent back containing the
// current modes of the target user->

// If <modestring> is given, the supplied modes will be applied, and a MODE message will be
// sent to the user containing the changed modes. If one or more modes sent are not
// implemented on the server, the server MUST apply the modes that are implemented, and
// then send the ERR_UMODEUNKNOWNFLAG (501) in reply along with the MODE message.

// Channel mode
// If <target> is a channel that does not exist on the network, the ERR_NOSUCHCHANNEL (403)
// numeric is returned.

// If <modestring> is not given, the RPL_CHANNELMODEIS (324) numeric is returned. Servers
// MAY choose to hide sensitive information such as channel keys when sending the current
// modes. Servers MAY also return the RPL_CREATIONTIME (329) numeric following RPL_CHANNELMODEIS.

// If <modestring> is given, the user sending the command MUST have appropriate channel
// privileges on the target channel to change the modes given. If a user does not have
// appropriate privileges to change modes on the target channel, the server MUST NOT process
// the message, and ERR_CHANOPRIVSNEEDED (482) numeric is returned. If the user has permission
// to change modes on the target, the supplied modes will be applied based on the type of the
// mode (see below). For type A, B, and C modes, arguments will be sequentially obtained from
// <mode arguments>. If a type B or C mode does not have a parameter when being set, the server
// MUST ignore that mode. If a type A mode has been sent without an argument, the contents of
// the list MUST be sent to the user, unless it contains sensitive information the user is not
// allowed to access. When the server is done processing the modes, a MODE command is sent to all
// members of the channel containing the mode changes. Servers MAY choose to hide sensitive
// information when sending the mode changes.

// <modestring> starts with a plus ('+', 0x2B) or minus ('-', 0x2D) character, and is made up of
// the following characters:

// '+': Adds the following mode(s).
// '-': Removes the following mode(s).
// 'a-zA-Z': Mode letters, indicating which modes are to be added/removed.
// The ABNF representation for <modestring> is:

//   modestring  =  1*( modeset )
//   modeset     =  plusminus *( modechar )
//   plusminus   =  %x2B / %x2D
//                    ; + or -
//   modechar    =  ALPHA
// There are four categories of channel modes, defined as follows:

// Type A: Modes that add or remove an address to or from a list. These modes MUST always have a
// parameter when sent from the server to a client. A client MAY issue this type of mode without
// an argument to obtain the current contents of the list. The numerics used to retrieve contents
// of Type A modes depends on the specific mode. Also see the EXTBAN parameter.
// Type B: Modes that change a setting on a channel. These modes MUST always have a parameter.
// Type C: Modes that change a setting on a channel. These modes MUST have a parameter when being
// set, and MUST NOT have a parameter when being unset.
// Type D: Modes that change a setting on a channel. These modes MUST NOT have a parameter.
// Channel mode letters, along with their types, are defined in the CHANMODES parameter. User mode
// letters are always Type D modes.

// The meaning of standard (and/or well-used) channel and user mode letters can be found in the
// Channel Modes and User Modes sections. The meaning of any mode letters not in this list are
// defined by the server software and configuration.

// Type A modes are lists that can be viewed. The method of viewing these lists is not standardised
// across modes and different numerics are used for each. The specific numerics used for these are
// outlined here:

// Ban List "+b": Ban lists are returned with zero or more RPL_BANLIST (367) numerics, followed
// by one RPL_ENDOFBANLIST (368) numeric.
// Exception List "+e": Exception lists are returned with zero or more RPL_EXCEPTLIST (348)
// numerics,followed by one RPL_ENDOFEXCEPTLIST (349) numeric.
// Invite-Exception List "+I": Invite-exception lists are returned with zero or more
// RPL_INVITELIST (336) numerics, followed by one RPL_ENDOFINVITELIST (337) numeric.
// After the initial MODE command is sent to the server, the client receives the above numerics
// detailing the entries that appear on the given list. Servers MAY choose to restrict the above
// information to channel operators, or to only those clients who have permissions to change the
// given list.
// */

// std::vector<Reply>	Server::privmsg(User *user, std::vector<std::string> args)
// {
// 	std::vector<Reply> reply;
// 	(void)user;
// 	(void)args;
	
// 	return (reply);
// }
// /*
// Command: PRIVMSG
// Parameters: <target>{,<target>} <text to be sent>

// The PRIVMSG command is used to send private messages between users, as well as to send
// messages to channels. <target> is the nickname of a client or the name of a channel.

// If <target> is a channel name and the client is banned and not covered by a ban exception,
// the message will not be delivered and the command will silently fail. Channels with the
// moderated mode active may block messages from certain users. Other channel modes may affect
// the delivery of the message or cause the message to be modified before delivery, and these
// modes are defined by the server software and configuration being used.

// If a message cannot be delivered to a channel, the server SHOULD respond with an
// ERR_CANNOTSENDTOCHAN (404) numeric to let the user know that this message could not
// be delivered.

// If <target> is a channel name, it may be prefixed with one or more channel membership
// prefix character (@, +, etc) and the message will be delivered only to the members of
// that channel with the given or higher status in the channel. Servers that support this
// feature will list the prefixes which this is supported for in the STATUSMSG RPL_ISUPPORT
// parameter, and this SHOULD NOT be attempted by clients unless the prefix has been advertised
// in this token.

// If <target> is a user and that user has been set as away, the server may reply with an
// RPL_AWAY (301) numeric and the command will continue.

// The PRIVMSG message is sent from the server to client to deliver a message to that client.
// The <source> of the message represents the user or server that sent the message, and the
// <target> represents the target of that PRIVMSG (which may be the client, a channel, etc).

// When the PRIVMSG message is sent from a server to a client and <target> starts with a dollar
// character ('$', 0x24), the message is a broadcast sent to all clients on one or multiple servers.

// Numeric Replies:

// ERR_NOSUCHNICK (401)
// ERR_NOSUCHSERVER (402)
// ERR_CANNOTSENDTOCHAN (404)
// ERR_TOOMANYTARGETS (407)
// ERR_NORECIPIENT (411)
// ERR_NOTEXTTOSEND (412)
// ERR_NOTOPLEVEL (413)
// ERR_WILDTOPLEVEL (414)
// RPL_AWAY (301)
// There are strange "X@Y" target rules and such which are noted in the examples of the original PRIVMSG RFC section. We need to check to make sure modern servers actually process them properly, and if so then specify them.
// */

// std::vector<Reply>	Server::notice(User *user, std::vector<std::string> args)
// {
// 	std::vector<Reply> reply;
// 	(void)user;
// 	(void)args;
	
// 	return (reply);
// }
// /*
// Command: NOTICE
// Parameters: <target>{,<target>} <text to be sent>

// The NOTICE command is used to send notices between users, as well as to send notices
// to channels. <target> is interpreted the same way as it is for the PRIVMSG command.

// The NOTICE message is used similarly to PRIVMSG. The difference between NOTICE and
// PRIVMSG is that automatic replies must never be sent in response to a NOTICE message.
// This rule also applies to servers – they must not send any error back to the client on
// receipt of a NOTICE command. The intention of this is to avoid loops between a client
// automatically sending something in response to something it received. This is typically
// used by ‘bots’ (a client with a program, and not a user, controlling their actions) and
// also for server messages to clients.

// One thing for bot authors to note is that the NOTICE message may be interpreted differently
// by various clients. Some clients highlight or interpret any NOTICE sent to a channel in the
// same way that a PRIVMSG with their nickname gets interpreted. This means that users may be
// irritated by the use of NOTICE messages rather than PRIVMSG messages by clients or bots,
// and they are not commonly used by client bots for this reason.
// */

// std::vector<Reply>	Server::who(User *user, std::vector<std::string> args)
// {
// 	std::vector<Reply> reply;
// 	(void)user;
// 	(void)args;

// 	return (reply);
// }
// /*
// Command: WHO
// Parameters: <mask>

// This command is used to query a list of users who match the provided mask. The server will
// answer this command with zero, one or more RPL_WHOREPLY, and end the list with RPL_ENDOFWHO.

// The mask can be one of the following:

// A channel name, in which case the channel members are listed.
// An exact nickname, in which case a single user is returned.
// A mask pattern, in which case all visible users whose nickname matches are listed. Servers
// MAY match other user-specific values, such as the hostname, server, real name or username.
// Servers MAY not support mask patterns and return an empty list.
// Visible users are users who aren’t invisible (user mode +i) and who don’t have a common
// channel with the requesting client. Servers MAY filter or limit visible users replies
// arbitrarily.

// Numeric Replies:

// RPL_WHOREPLY (352)
// RPL_ENDOFWHO (315)
// ERR_NOSUCHSERVER (402)
// See also:

// IRCv3 multi-prefix Extension
// WHOX
// Examples
// Command Examples:

//   WHO emersion        ; request information on user "emersion"
//   WHO #ircv3          ; list users in the "#ircv3" channel
// Reply Examples:

//   :calcium.libera.chat 352 dan #ircv3 ~emersion sourcehut/staff/emersion calcium.libera.chat
//   		emersion H :1 Simon Ser
//   :calcium.libera.chat 315 dan emersion :End of WHO list
//                                   ; Reply to WHO emersion

//   :calcium.libera.chat 352 dan #ircv3 ~emersion sourcehut/staff/emersion calcium.libera.chat
//   		emersion H :1 Simon Ser
//   :calcium.libera.chat 352 dan #ircv3 ~val limnoria/val calcium.libera.chat val H :1 Val
//   :calcium.libera.chat 315 dan #ircv3 :End of WHO list
//                                   ; Reply to WHO #ircv3
// */

// std::vector<Reply>	Server::whois(User *user, std::vector<std::string> args)
// {
// 	std::vector<Reply> reply;
// 	(void)user;
// 	(void)args;
	
// 	return (reply);
// }
// /*
// Command: WHOIS
// Parameters: [<target>] <nick>

// This command is used to query information about particular users. The server will answer
// this command with several numeric messages with information about the nicks, ending with
// RPL_ENDOFWHOIS.

// Servers MUST end their reply to WHOIS messages with one of these numerics:

// ERR_NOSUCHNICK (401)
// ERR_NOSUCHSERVER (402)
// ERR_NONICKNAMEGIVEN (431)
// RPL_ENDOFWHOIS (318)otherwise, even if they did not send any other numeric message. This allows
// clients to stop waiting for new numerics.
// In exceptional error conditions, servers MAY not reply to a WHOIS command. Clients SHOULD
// implement a hard timeout to avoid waiting for a reply which won’t come.

// Client MUST NOT not assume all numeric messages are sent at once, as server can interleave
// other messages before the end of the WHOIS response.

// If the <target> parameter is specified, it SHOULD be a server name or the nick of a user->
// Servers SHOULD send the query to a specific server with that name, or to the server <target>
// is connected to, respectively. Typically, it is used by clients who want to know how long
// the user in question has been idle (as typically only the server the user is directly connected
// to knows that information, while everything else this command returns is globally known).

// The following numerics MAY be returned as part of the whois reply:

// RPL_WHOISCERTFP (276)
// RPL_WHOISREGNICK (307)
// RPL_WHOISUSER (311)
// RPL_WHOISSERVER (312)
// RPL_WHOISOPERATOR (313)
// RPL_WHOISIDLE (317)
// RPL_WHOISCHANNELS (319)
// RPL_WHOISSPECIAL (320)
// RPL_WHOISACCOUNT (330)
// RPL_WHOISACTUALLY (338)
// RPL_WHOISHOST (378)
// RPL_WHOISMODES (379)
// RPL_WHOISSECURE (671)
// RPL_AWAY (301)

// Servers typically send some of these numerics only to the client itself and to servers operators,
// as they contain privacy-sensitive information that should not be revealed to other users.

// Server implementers wishing to send information not covered by these numerics may send other
// vendor-specific numerics, such that:

// the first and second parameters MUST be the client’s nick, and the target nick, and
// the last parameter SHOULD be designed to be human-readable, so that user interfaces can display
// unknown numerics
// Additionally, server implementers should consider submitting these to IRCv3 for standardization,
// if relevant.

// Optional extensions
// This section describes extension to the common WHOIS command above. They exist mainly on
// historical ervers, and are rarely implemented, because of resource usage they incur.

// Servers MAY allow more than one target nick. They can advertise the maximum the number of
// target users per WHOIS command via the TARGMAX RPL_ISUPPORT parameter, and silently drop
// targets if the number of targets exceeds the limit.

// Servers MAY allow wildcards in <nick>. Servers who do SHOULD reply with information about all
// matching nicks. They may restrict what information is available in this case, to limit resource
// usage.

// IRCv3 multi-prefix Extension

// Examples :

// Command Examples:

//   WHOIS val                     ; request information on user "val"
//   WHOIS val val                 ; request information on user "val",
//                                 from the server they are on
//   WHOIS calcium.libera.chat val ; request information on user "val",
//                                 from server calcium.libera.chat

// Reply Example:

//   :calcium.libera.chat 311 val val ~val limnoria/val * :Val
//   :calcium.libera.chat 319 val val :#ircv3 #libera +#limnoria
//   :calcium.libera.chat 319 val val :#weechat
//   :calcium.libera.chat 312 val val calcium.libera.chat :Montreal, CA
//   :calcium.libera.chat 671 val val :is using a secure connection [TLSv1.3, TLS_AES_256_GCM_SHA384]
//   :calcium.libera.chat 317 val val 657 1628028154 :seconds idle, signon time
//   :calcium.libera.chat 330 val val pinkieval :is logged in as
//   :calcium.libera.chat 318 val val :End of /WHOIS list.
// */

// std::vector<Reply>	Server::whowas(User *user, std::vector<std::string> args)
// {
// 	std::vector<Reply> reply;
// 	(void)user;
// 	(void)args;
	
// 	return (reply);
// }
// /*
// Command: WHOWAS
// Parameters: <nick> [<count>]

// Whowas asks for information about a nickname which no longer exists. This may either be due to a nickname change or the user leaving IRC. In response to this query, the server searches through its nickname history, looking for any nicks which are lexically the same (no wild card matching here). The history is searched backward, returning the most recent entry first. If there are multiple entries, up to <count> replies will be returned (or all of them if no <count> parameter is given).

// If given, <count> SHOULD be a positive number. Otherwise, a full search is done.

// Servers MUST reply with either ERR_WASNOSUCHNICK (406) or a non-empty list of WHOWAS entries, both followed with RPL_ENDOFWHOWAS (369)

// A WHOWAS entry is a series of numeric messages starting with RPL_WHOWASUSER (314), optionally followed by other numerics relevant to that user, such as RPL_WHOISACTUALLY (338) and RPL_WHOISSERVER (312). Clients MUST NOT assume any particular numeric other than RPL_WHOWASUSER (314) is present in a WHOWAS entry.

// If the <nick> argument is missing, they SHOULD send a single reply, using either ERR_NONICKNAMEGIVEN (431) or ERR_NEEDMOREPARAMS (461).

// Examples
// Command Examples:

//   WHOWAS someone
//   WHOWAS someone 2
// Reply Examples:

//   :inspircd.server.example 314 val someone ident3 127.0.0.1 * :Realname
//   :inspircd.server.example 312 val someone My.Little.Server :Sun Mar 20 2022 10:59:26
//   :inspircd.server.example 314 val someone ident2 127.0.0.1 * :Realname
//   :inspircd.server.example 312 val someone My.Little.Server :Sun Mar 20 2022 10:59:16
//   :inspircd.server.example 369 val someone :End of WHOWAS

//   :ergo.server.example 314 val someone ~ident3 127.0.0.1 * Realname
//   :ergo.server.example 314 val someone ~ident2 127.0.0.1 * Realname
//   :ergo.server.example 369 val someone :End of WHOWAS

//   :solanum.server.example 314 val someone ~ident3 localhost * :Realname
//   :solanum.server.example 338 val someone 127.0.0.1 :actually using host
//   :solanum.server.example 312 val someone solanum.server.example :Sun Mar 20 10:07:44 2022
//   :solanum.server.example 314 val someone ~ident2 localhost * :Realname
//   :solanum.server.example 338 val someone 127.0.0.1 :actually using host
//   :solanum.server.example 312 val someone solanum.server.example :Sun Mar 20 10:07:34 2022
//   :solanum.server.example 369 val someone :End of WHOWAS

//   :server.example 406 val someone :There was no such nickname
//   :server.example 369 val someone :End of WHOWAS
// */

// std::vector<Reply>	Server::kill(User *user, std::vector<std::string> args)
// {
// 	std::vector<Reply> reply;
// 	(void)user;
// 	(void)args;
	
// 	return (reply);
// }
// /*
// Command: KILL
// Parameters: <nickname> <comment>

// The KILL command is used to close the connection between a given client and the server
// they are connected to. KILL is a privileged command and is available only to IRC Operators.
// <nickname> represents the user to be ‘killed’, and <comment> is shown to all users and to
// the user themselves upon being killed.

// When a KILL command is used, the client being killed receives the KILL message, and the
// <source> of the message SHOULD be the operator who performed the command. The user being
// killed and every user sharing a channel with them receives a QUIT message representing that
// they are leaving the network. The <reason> on this QUIT message typically has the form:
// "Killed (<killer> (<reason>))" where <killer> is the nickname of the user who performed the
// KILL. The user being killed then receives the ERROR message, typically containing a <reason>
// of "Closing Link: <servername> (Killed (<killer> (<reason>)))". After this, their connection
// is closed.

// If a KILL message is received by a client, it means that the user specified by <nickname>
// is being killed. With certain servers, users may elect to receive KILL messages created for
// other users to keep an eye on the network. This behavior may also be restricted to operators.

// Clients can rejoin instantly after this command is performed on them. However, it can serve
// as a warning to a user to stop their activity. As it breaks the flow of data from the user,
// it can also be used to stop large amounts of ‘flooding’ from abusive users or due to accidents.
// Abusive users may not care and promptly reconnect and resume their abusive behaviour. In
// these cases, opers may look at the KLINE command to keep them from rejoining the network
// for a longer time.

// As nicknames across an IRC network MUST be unique, if duplicates are found when servers join,
// one or both of the clients MAY be KILLed and removed from the network. Servers may also handle
// this case in alternate ways that don’t involve removing users from the network.

// Servers MAY restrict whether specific operators can remove users on other servers (remote users).
// If the operator tries to remove a remote user but is not privileged to, they should receive the
// ERR_NOPRIVS (723) numeric.

// <comment> SHOULD reflect why the KILL was performed. For user-generated KILLs, it is up to the
// user to provide an adequate reason.

// Numeric Replies:

// ERR_NOSUCHSERVER (402)
// ERR_NEEDMOREPARAMS (461)
// ERR_NOPRIVILEGES (481)
// ERR_NOPRIVS (723)
// NOTE: The KILL message is weird, and I need to look at it more closely, add some examples, etc.
// */

// std::vector<Reply>	Server::rehash(User *user, std::vector<std::string> args)
// {
// 	std::vector<Reply> reply;
// 	(void)user;
// 	(void)args;
	
// 	return (reply);
// }
// /*
// Command: REHASH
// Parameters: None

// The REHASH command is an administrative command which can be used by an operator to force
// the local server to re-read and process its configuration file. This may include other data,
// such as modules or TLS certificates.

// Servers MAY accept, as an optional argument, the name of a remote server that should be
// rehashed instead of the current one.

// Numeric replies:

// RPL_REHASHING (382)
// ERR_NOPRIVILEGES (481)
// Example:

//  REHASH                          ; message from user with operator
//                                  status to server asking it to reread
//                                  its configuration file.
// */

// std::vector<Reply>	Server::restart(User *user, std::vector<std::string> args)
// {
// 	std::vector<Reply> reply;
// 	(void)user;
// 	(void)args;
	
// 	return (reply);
// }
// /*
// Command: RESTART
// Parameters: None

// An operator can use the restart command to force the server to restart itself.
// This message is optional since it may be viewed as a risk to allow arbitrary
// people to connect to a server as an operator and execute this command, causing
// (at least) a disruption to service.

// Numeric replies:

// ERR_NOPRIVILEGES (481)
// */

// std::vector<Reply>	Server::squit(User *user, std::vector<std::string> args)
// {
// 	std::vector<Reply> reply;
// 	(void)user;
// 	(void)args;
	
// 	return (reply);
// 	// does nothing, we only have one server
// }
// /*
// Command: SQUIT
// Parameters: <server> <comment>

// The SQUIT command disconnects a server from the network. SQUIT is a privileged
// command and is only available to IRC Operators. <comment> is the reason why the
// server link is being disconnected.

// In a traditional spanning-tree topology, the command gets forwarded to the specified
// server. And the link between the specified server and the last server to propagate
// the command gets broken.

// Numeric replies:

// ERR_NOSUCHSERVER (402)
// ERR_NEEDMOREPARAMS (461)
// ERR_NOPRIVILEGES (481)
// ERR_NOPRIVS (723)
// */

// std::vector<Reply>	Server::away(User *user, std::vector<std::string> args)
// {
// 	std::vector<Reply> reply;
// 	(void)user;
// 	(void)args;
	
// 	return (reply);
// }
// /*
// Command: AWAY
// Parameters: [ <text> ]

// The AWAY command lets clients indicate that their user is away. If this command is
// sent with a nonempty parameter (the ‘away message’) then the user is set to be away.
// If this command is sent with no parameters, or with the empty string as the parameter,
// the user is no longer away.

// The server acknowledges the change in away status by returning the RPL_NOWAWAY (306)
// and RPL_UNAWAY (305) numerics. If the IRCv3 away-notify capability has been requested
// by a client, the server MAY also send that client AWAY messages to tell them how the
// away status of other users has changed.

// Servers SHOULD notify clients when a user they’re interacting with is away when relevant,
// including sending these numerics:

// RPL_AWAY (301), with the away message, when a PRIVMSG command is directed at the away user
// (not to a channel they are on).
// RPL_AWAY (301), with the away message, in replies to WHOIS messages.
// In the RPL_USERHOST (302) numeric, as the + or - character.
// In the RPL_WHOREPLY (352) numeric, as the H or G character.
// Numeric Replies:

// RPL_UNAWAY (305)
// RPL_NOWAWAY (306)
// */

// std::vector<Reply>	Server::links(User *user, std::vector<std::string> args)
// {
// 	std::vector<Reply> reply;
// 	(void)user;
// 	(void)args;
	
// 	return (reply);
// }
// /*
// Command: LINKS
// Parameters: None

// With LINKS, a user can list all servers which are known by the server answering the query,
// usually including the server itself.

// In replying to the LINKS message, a server MUST send replies back using zero or more
// RPL_LINKS (364) messages and mark the end of the list using a RPL_ENDOFLINKS (365) message.

// Servers MAY omit some or all servers on the network, including itself.

// Numeric Replies:

// RPL_LINKS (364)
// RPL_ENDOFLINKS (365)
// */

// std::vector<Reply>	Server::userhost(User *user, std::vector<std::string> args)
// {
// 	std::vector<Reply> reply;
// 	(void)user;
// 	(void)args;
	
// 	return (reply);
// }
// /*
// Command: USERHOST
// Parameters: <nickname>{ <nickname>}

// The USERHOST command is used to return information about users with the given nicknames.
// The USERHOST command takes up to five nicknames, each a separate parameters. The nicknames
// are returned in RPL_USERHOST (302) numerics.

// Numeric Replies:

// ERR_NEEDMOREPARAMS (461)
// RPL_USERHOST (302)
// Command Examples:

//   USERHOST Wiz Michael Marty p    ;USERHOST request for information on
//                                   nicks "Wiz", "Michael", "Marty" and "p"
// Reply Examples:

//   :ircd.stealth.net 302 yournick :syrk=+syrk@millennium.stealth.net
//                                   ; Reply for user syrk
// */

// std::vector<Reply>	Server::wallops(User *user, std::vector<std::string> args)
// {
// 	std::vector<Reply> reply;
// 	(void)user;
// 	(void)args;
	
// 	return (reply);
// }
// /*
// Command: WALLOPS
// Parameters: <text>

// The WALLOPS command is used to send a message to all currently connected users who have set the ‘w’ user mode for themselves. The <text> SHOULD be non-empty.

// Servers MAY echo WALLOPS messages to their sender even if they don’t have the ‘w’ user mode.

// Servers MAY send WALLOPS only to operators.

// Servers may generate it themselves, and MAY allow operators to send them.

// Numeric replies:

// ERR_NEEDMOREPARAMS (461)
// ERR_NOPRIVILEGES (481)
// ERR_NOPRIVS (723)
// Examples:

//  :csd.bu.edu WALLOPS :Connect '*.uiuc.edu 6667' from Joshua
//                                  ;WALLOPS message from csd.bu.edu announcing
//                                  a CONNECT message it received and acted
//                                  upon from Joshua.

// */

// // to run these test uncomment (return (0) on Server::polling_loop) and comment 
// // send(user->get_fd(), message.c_str(), message.length(), 0); on Server::send_message()
// // then compile with :
// // clang++ -Wall -Wextra -Werror SRCS/Command.cpp SRCS/User.cpp SRCS/Reply.cpp SRCS/Server.cpp

// // int	main()
// // {
// // 	std::cout << "coucou" << std::endl;
// // 	Server						s;
// // 	User						u1(1); // irssi connection
// // 	User						u2(2); // unknow command
// // 	User						u3(3); // banned
// // 	User						u4(4); // pass
// // 	User						u5(5); // nick
// // 	User						u6(6); // nick
// // 	User						u7(7); // nick
// // 	std::vector<std::string>	str;

// // 	u1.set_hostname("User1_hostname");
// // 	u1.set_hostaddr("User1_hostaddr");
// // 	u2.set_hostname("User2_hostname");
// // 	u2.set_hostaddr("User2_hostaddr");
// // 	u3.set_hostname("User3_hostname");
// // 	u3.set_hostaddr("User3_hostaddr");
// // 	u3.set_status(USR_STAT_BAN);
// // 	u4.set_hostname("User4_hostname");
// // 	u4.set_hostaddr("User4_hostaddr");
// // 	u5.set_hostname("User5_hostname");
// // 	u5.set_hostaddr("User5_hostaddr");
// // 	u6.set_hostname("User6_hostname");
// // 	u6.set_hostaddr("User6_hostaddr");
// // 	u7.set_hostname("User7_hostname");
// // 	u7.set_hostaddr("User7_hostaddr");

// // 	s._usr_list.push_back(&u1);
// // 	s._usr_list.push_back(&u2);
// // 	s._usr_list.push_back(&u3);
// // 	s._usr_list.push_back(&u4);
// // 	s._usr_list.push_back(&u5);
// // 	s._usr_list.push_back(&u6);
// // 	s._usr_list.push_back(&u7);

// // 	std::cout << "\033[1;36m---- TEST NORMAL CONNECTION IRSSI ----\033[0m" << std::endl;
// // 	s.run_buffer(1, "CAP LS \nPASS abc \nNICK cmaginot \nUSER cmaginot cmaginot 127.0.0.1 :Celia MAGINOT \n");



// // 	std::cout << "\033[1;36m---- TEST UNKNOW COMMAND ----\033[0m" << std::endl;
// // 	s.run_buffer(2, "BLABLA");



// // 	std::cout << "\033[1;36m---- TEST PASS ----\033[0m" << std::endl;
// // 	std::cout << "\033[36m- ban -\033[0m" << std::endl;
// // 	s.run_buffer(3, "PASS I AM BANNED");



// // 	std::cout << "\033[36m- error -\033[0m" << std::endl;
// // 	s.run_buffer(4, "PASS");
// // 	s.run_buffer(4, "PASS  ");
// // 	s.run_buffer(4, "PASS pass");
// // 	s.run_buffer(4, "PASS pass word");
// // 	s.run_buffer(4, "PASS pass abc");

// // 	std::cout << "\033[36m- good multiple time -\033[0m" << std::endl;
// // 	s.run_buffer(4, "PASS abc word");
// // 	s.run_buffer(4, "PASS abc");
// // 	s.run_buffer(4, "PASS abc");



// // 	std::cout << "\033[1;36m---- TEST NICK ----\033[0m" << std::endl;
// // 	std::cout << "\033[36m- ban -\033[0m" << std::endl;
// // 	s.run_buffer(3, "NICK I AM BANNED");

// // 	std::cout << "\033[36m- not register -\033[0m" << std::endl;
// // 	s.run_buffer(5, "NICK cmaginot");

// // 	std::cout << "\033[36m- bad nick -\033[0m" << std::endl;
// // 	s.run_buffer(5, "PASS abc");
// // 	s.run_buffer(5, "NICK");
// // 	s.run_buffer(5, "NICK    ");
// // 	s.run_buffer(5, "NICK freya~");
// // 	s.run_buffer(5, "NICK freya*");
// // 	s.run_buffer(5, "NICK 123freya");
// // 	s.run_buffer(5, "NICK -freya");

// // 	std::cout << "\033[36m- good nick -\033[0m" << std::endl;
// // 	s.run_buffer(5, "NICK Freya");
// // 	s.run_buffer(5, "NICK freya");
// // 	s.run_buffer(5, "NICK Cmaginot");
// // 	s.run_buffer(5, "NICK e1r1p1");
// // 	s.run_buffer(5, "NICK Freya-Tenebrae");
// // 	s.run_buffer(5, "NICK Freya");

// // 	std::cout << "\033[36m- try to put same nick -\033[0m" << std::endl;
// // 	s.run_buffer(5, "NICK Freya");

// // 	std::cout << "\033[36m- good nick but already exist on another user -\033[0m" << std::endl;
// // 	s.run_buffer(6, "PASS abc");
// // 	s.run_buffer(6, "NICK Freya");
// // 	s.run_buffer(6, "NICK Freya-Tenebrae");

// // 	std::cout << "\033[1;36m---- TEST USER ----\033[0m" << std::endl;
// // 	std::cout << "\033[36m- ban -\033[0m" << std::endl;
// // 	s.run_buffer(3, "NICK I AM BANNED");

// // 	std::cout << "\033[36m- not register -\033[0m" << std::endl;
// // 	s.run_buffer(7, "NICK cmaginot");

// // 	std::cout << "\033[36m- nick not done before -\033[0m" << std::endl;
// // 	s.run_buffer(7, "PASS abc");
// // 	s.run_buffer(7, "USER cmaginot cmaginot 127.0.0.1 :Celia MAGINOT");

// // 	std::cout << "\033[36m- wrong -\033[0m" << std::endl;
// // 	s.run_buffer(7, "PASS abc");
// // 	s.run_buffer(7, "USER cmaginot cmaginot 127.0.0.1 :Celia MAGINOT");

// // 	std::cout << "\033[36m- correct -\033[0m" << std::endl;
// // 	s.run_buffer(7, "NICK cmaginot");
// // 	s.run_buffer(7, "USER cmaginot cmaginot 127.0.0.1 :Celia MAGINOT");

// // 	std::cout << "\033[36m- second user -\033[0m" << std::endl;
// // 	s.run_buffer(7, "NICK cmaginot");
// // 	s.run_buffer(7, "USER cmaginot cmaginot 127.0.0.1 :Celia MAGINOT");



// // 	std::cout << "\033[1;36m---- END OF TESTS ----\033[0m" << std::endl;
// // 	return (0);
// // }