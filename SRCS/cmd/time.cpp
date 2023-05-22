/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaginot <cmaginot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 18:15:54 by cmaginot          #+#    #+#             */
/*   Updated: 2023/04/17 18:43:57 by cmaginot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INCL/User.hpp"
#include "../../INCL/Reply.hpp"
#include "../../INCL/Server.hpp"

/*
Command: TIME
Parameters: [<server>]

The TIME command is used to query local time from the specified server.
If the server parameter is not given, the server handling the command
must reply to the query.

Numeric Replies:

ERR_NOSUCHSERVER (402)
RPL_TIME (391)
*/

std::vector<Reply>	Server::time(User *user, std::vector<std::string> args)
{
	std::vector<Reply> reply;
	int					target = 0;

	if (user->get_status() == USR_STAT_BAN)
		reply.push_back(ERR_YOUREBANNEDCREEP);
	else if (user->get_connected() == false)
		reply.push_back(ERR_NOTREGISTERED);
	else if (args.empty() == true || args[target].compare(this->_name))
		reply.push_back(RPL_TIME);
	else
		reply.push_back(ERR_NOSUCHSERVER);
	reply[0].add_user(user);
	reply[0].prep_to_send(1);
	return (reply);
}
