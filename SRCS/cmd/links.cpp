/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   links.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaginot <cmaginot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 18:15:54 by cmaginot          #+#    #+#             */
/*   Updated: 2023/05/24 18:08:47 by cmaginot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INCL/User.hpp"
#include "../../INCL/Reply.hpp"
#include "../../INCL/Server.hpp"

/*
Command: LINKS
Parameters: None

With LINKS, a user can list all servers which are known by the server answering the query,
usually including the server itself.

In replying to the LINKS message, a server MUST send replies back using zero or more
RPL_LINKS (364) messages and mark the end of the list using a RPL_ENDOFLINKS (365) message.

Servers MAY omit some or all servers on the network, including itself.

Numeric Replies:

RPL_LINKS (364)
RPL_ENDOFLINKS (365)
*/

std::vector<Reply>	Server::links(User *user, std::vector<std::string> args) // do not use
{
	std::vector<Reply> reply;
	(void)args;

	if (user->get_status() == USR_STAT_BAN)
		reply.push_back(ERR_YOUREBANNEDCREEP);
	else
	{
		reply.push_back(ERR_UNKNOWNCOMMAND);
		reply[0].add_user(user);
		reply[0].add_arg("LINKS", "command");
		reply[0].prep_to_send(1);
	}
	return (reply);
}

// std::vector<Reply>	Server::links(User *user, std::vector<std::string> args)
// {
// 	std::vector<Reply> reply;

// 	(void)args;

// 	if (user->get_status() == USR_STAT_BAN)
// 		reply.push_back(ERR_YOUREBANNEDCREEP);
// 	else if (user->get_connected() == false)
// 		reply.push_back(ERR_NOTREGISTERED);
// 	else
// 	{
// 		reply.push_back(RPL_LINKS);
// 		reply[0].add_arg(_name, "server");
// 		reply[0].add_arg("0", "hopcount");
// 		reply[0].add_arg("main server (there is no conection between server)", "server info");
// 		reply.push_back(RPL_ENDOFINFO);
// 	}

// 	for (std::vector<Reply>::iterator it = reply.begin(); it != reply.end(); it++)
// 	{
// 		it->add_user(user);
// 		it->prep_to_send(1);
// 	}

// 	return (reply);
// }
