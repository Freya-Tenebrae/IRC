/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaginot <cmaginot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 18:15:54 by cmaginot          #+#    #+#             */
/*   Updated: 2023/03/30 18:14:00 by cmaginot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INCL/User.hpp"
#include "../../INCL/Reply.hpp"
#include "../../INCL/Server.hpp"

/*
Command: NICK
Parameters: <nickname>

The NICK command is used to give the client a nickname or change the previous one.

If the server receives a NICK command from a client where the desired nickname 
is already in use on the network, it should issue an ERR_NICKNAMEINUSE numeric 
and ignore the NICK command.

If the server does not accept the new nickname supplied by the client as valid 
(for instance, due to containing invalid characters), it should issue an 
ERR_ERRONEUSNICKNAME numeric and ignore the NICK command.

If the server does not receive the <nickname> parameter with the NICK command, 
it should issue an ERR_NONICKNAMEGIVEN numeric and ignore the NICK command.

The NICK message may be sent from the server to clients to acknowledge their NICK 
command was successful, and to inform other clients about the change of nickname. 
In these cases, the <source> of the message will be the old 
nickname [ [ "!" user ] "@" host ] of the user who is changing their nickname.

Numeric Replies:

ERR_NONICKNAMEGIVEN (431)
ERR_ERRONEUSNICKNAME (432)
ERR_NICKNAMEINUSE (433)
ERR_NICKCOLLISION (436)
*/

/*
ERR_NICKCOLLISION (436) don't know what it is
check return when sucess
*/

bool Server::is_nickname_valid(std::string nickname)
{
	std::string autorise_special_char = "0123456789`|^_-{}[]\\"; // valid char exept for begin
	if (nickname.compare("") == 0)
		return (false);
	for (std::string::iterator it = nickname.begin(); it != nickname.end(); it++)
	{
		if (!((*it >= 'a' && *it <= 'z') || (*it >= 'A' && *it <= 'Z') || \
			(autorise_special_char.find(*it) != std::string::npos && it != nickname.begin())))
			return (false);
	}
	return (true);
}

bool Server::is_nickname_free(std::string nickname)
{
	for (std::vector<User *>::iterator it = _usr_list.begin(); it != _usr_list.end(); it++)
	{
		if ((*it)->get_nickname().compare(nickname) == 0)
			return (false);
	}
	return (true);
}

std::vector<Reply>	Server::nick(User *user, std::vector<std::string> args)
{
	std::vector<Reply>	reply;
	int					nickname = 0;

	if (user->get_status() == USR_STAT_BAN)
		reply.push_back(ERR_YOUREBANNEDCREEP);
	else if (user->get_connected() == false)
		reply.push_back(ERR_NOTREGISTERED);
	else if (args.empty() == true || args[nickname].compare("") == 0)
		reply.push_back(ERR_NONICKNAMEGIVEN);
	else if (is_nickname_valid(args[nickname]) == false)
	{
		reply.push_back(ERR_ERRONEUSNICKNAME);
		reply[0].add_arg(args[0], "nick");
	}
	else if (args[nickname] == user->get_nickname())
		reply.push_back(ERR_ERROSAMENICKNAME);
	else if (is_nickname_free(args[nickname]) == false)
	{
		reply.push_back(ERR_NICKNAMEINUSE);
		reply[0].add_arg(args[0], "nick");
		if (user->get_nickname().compare("") == 0)
		{
			std::string tmp_nick = args[nickname];
			tmp_nick.insert(0, "tmp_");
			while (is_nickname_free(tmp_nick) == false)
				tmp_nick.push_back('X');
			user->set_nickname(tmp_nick);
		}
	}
	else
	{
		reply.push_back(RPL_NICKSET);
		reply[0].add_arg(args[nickname], "client");
		reply[0].add_user(user);
		reply[0].prep_to_send(2);
		user->set_nickname(args[nickname]);
		return(reply);
	}
	reply[0].add_user(user);
	reply[0].prep_to_send(1);
	return(reply);
}
