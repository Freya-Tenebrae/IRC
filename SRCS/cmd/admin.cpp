/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   admin.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaginot <cmaginot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 18:15:54 by cmaginot          #+#    #+#             */
/*   Updated: 2023/05/24 18:10:49 by cmaginot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INCL/User.hpp"
#include "../../INCL/Reply.hpp"
#include "../../INCL/Server.hpp"
#include "../../INCL/Channel.hpp"

/*
Command: ADMIN
Parameters: [<target>]

The ADMIN command is used to find the name of the administrator
of the given server. If <target> is not given, the information
for the server the client is connected to should be returned.

If <target> is a server, the information for that server is requested.
If <target> is a client, the information for the server that client is
connected to is requested. If <target> is given and a matching server
cannot be found, the server will respond with the ERR_NOSUCHSERVER
numeric and the command will fail.

Wildcards are allowed in the <target> parameter.

Upon receiving an ADMIN command, the given server SHOULD respond with
the RPL_ADMINME, RPL_ADMINLOC1, RPL_ADMINLOC2, and RPL_ADMINEMAIL replies.

Numeric Replies:

ERR_NOSUCHSERVER (402)
RPL_ADMINME (256)
RPL_ADMINLOC1 (257)
RPL_ADMINLOC2 (258)
RPL_ADMINEMAIL (259)
*/

std::vector<Reply>	Server::admin(User *user, std::vector<std::string> args) // do not use
{
	std::vector<Reply> reply;
	(void)args;

	if (user->get_status() == USR_STAT_BAN)
		reply.push_back(ERR_YOUREBANNEDCREEP);
	else
	{
		reply.push_back(ERR_UNKNOWNCOMMAND);
		reply[0].add_user(user);
		reply[0].add_arg("ADMIN", "command");
		reply[0].prep_to_send(1);
	}
	return (reply);
}

// std::vector<Reply>	Server::admin(User *user, std::vector<std::string> args)
// {
// 	std::vector<Reply> reply;
	
// 	if (user->get_status() == USR_STAT_BAN)
// 		reply.push_back(ERR_YOUREBANNEDCREEP);
// 	else if (user->get_connected() == false)
// 		reply.push_back(ERR_NOTREGISTERED);
// 	else if (args.empty() == true || (args.size() == 1 && args[0].compare(this->get_name())))
// 	{
// 		reply.push_back(RPL_ADMINME);
// 		reply.push_back(RPL_ADMINLOC1);
// 		reply.push_back(RPL_ADMINLOC2);
// 		reply.push_back(RPL_ADMINEMAIL);
// 	}
// 	else
// 		reply.push_back(ERR_NOSUCHSERVER);
// 	return (reply);
// }
