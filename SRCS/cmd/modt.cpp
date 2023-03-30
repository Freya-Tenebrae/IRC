/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modt.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaginot <cmaginot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 18:15:54 by cmaginot          #+#    #+#             */
/*   Updated: 2023/03/28 15:46:36 by cmaginot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INCL/User.hpp"
#include "../../INCL/Reply.hpp"
#include "../../INCL/Server.hpp"

/*
Command: MOTD
Parameters: [<target>]

The MOTD command is used to get the “Message of the Day” of the given server.
If <target> is not given, the MOTD of the server the client is connected to
should be returned.

If <target> is a server, the MOTD for that server is requested. If <target> is
given and a matching server cannot be found, the server will respond with the
ERR_NOSUCHSERVER numeric and the command will fail.

If the MOTD can be found, one RPL_MOTDSTART numeric is returned, followed by one
or more RPL_MOTD numeric, then one RPL_ENDOFMOTD numeric.

If the MOTD does not exist or could not be found, the ERR_NOMOTD numeric is returned.

Numeric Replies:

ERR_NOSUCHSERVER (402)
ERR_NOMOTD (422)
RPL_MOTDSTART (375)
RPL_MOTD (372)
RPL_ENDOFMOTD (376)
*/

std::vector<Reply>	Server::motd(User *user, std::vector<std::string> args)
{
	std::vector<Reply>	reply;
	int 				target = 0;
	int					i = 0;

	if (user->get_status() == USR_STAT_BAN)
		reply.push_back(ERR_YOUREBANNEDCREEP);
	else if (user->get_connected() == false)
		reply.push_back(ERR_NOTREGISTERED);
	else if (args.empty() != true && args[target].compare("") != 0 && _name.compare(args[target]) != 0)
		reply.push_back(ERR_NOSUCHSERVER);
	else
	{
		if (_modt.empty() == true)
			reply.push_back(ERR_NOMOTD);
		else
		{
			reply.push_back(RPL_MOTDSTART);
			reply[0].add_arg(get_name(), "server");
			for (std::vector<std::string>::iterator it = _modt.begin(); it != _modt.end(); it++)
			{
				++i;
				reply.push_back(RPL_MOTD);
				reply[i].add_arg(*it, "line of the motd");
			}
			reply.push_back(RPL_ENDOFMOTD);
		}
	}
	for (std::vector<Reply>::iterator it = reply.begin(); it != reply.end(); it++)
	{
		it->add_user(user);
		it->prep_to_send(1);
	}
	return (reply);
}
