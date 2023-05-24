/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaginot <cmaginot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 18:15:54 by cmaginot          #+#    #+#             */
/*   Updated: 2023/05/24 18:14:02 by cmaginot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INCL/User.hpp"
#include "../../INCL/Reply.hpp"
#include "../../INCL/Server.hpp"

/*
Command: INFO
Parameters: None
The INFO command is used to return information which describes the server.
This information usually includes the software name/version and its authors.
Some other info that may be returned includes the patch level and compile date
of the server, the copyright on the server software, and whatever miscellaneous
information the server authors consider relevant.

Upon receiving an INFO command, the server will respond with zero or more RPL_INFO
replies, followed by one RPL_ENDOFINFO numeric.

Numeric Replies:

RPL_INFO (371)
RPL_ENDOFINFO (374)
*/

std::vector<Reply>	Server::info(User *user, std::vector<std::string> args) // do not use
{
	std::vector<Reply> reply;
	(void)args;

	if (user->get_status() == USR_STAT_BAN)
		reply.push_back(ERR_YOUREBANNEDCREEP);
	else
	{
		reply.push_back(ERR_UNKNOWNCOMMAND);
		reply[0].add_user(user);
		reply[0].add_arg("INFO", "command");
		reply[0].prep_to_send(1);
	}
	return (reply);
}

// std::vector<Reply>	Server::info(User *user, std::vector<std::string> args)
// {
// 	(void)args;

// 	std::vector<Reply> reply;

// 	if (user->get_status() == USR_STAT_BAN)
// 		reply.push_back(ERR_YOUREBANNEDCREEP);
// 	else if (user->get_connected() == false)
// 		reply.push_back(ERR_NOTREGISTERED);
// 	else
// 	{
// 		for (std::vector<std::string>::iterator it = _info.begin(); it != _info.end(); it++)
// 		{
// 			Reply r(RPL_INFO);
// 			r.add_arg(*it, "string");
// 			reply.push_back(r);
// 		}
// 		reply.push_back(RPL_ENDOFINFO);
// 	}

// 	for (std::vector<Reply>::iterator it = reply.begin(); it != reply.end(); it++)
// 	{
// 		it->add_user(user);
// 		it->prep_to_send(1);
// 	}

// 	return (reply);
// }
