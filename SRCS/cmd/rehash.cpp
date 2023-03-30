/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rehash.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaginot <cmaginot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 18:15:54 by cmaginot          #+#    #+#             */
/*   Updated: 2023/03/28 16:35:16 by cmaginot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INCL/User.hpp"
#include "../../INCL/Reply.hpp"
#include "../../INCL/Server.hpp"

/*
Command: REHASH
Parameters: None

The REHASH command is an administrative command which can be used by an operator to force
the local server to re-read and process its configuration file. This may include other data,
such as modules or TLS certificates.

Servers MAY accept, as an optional argument, the name of a remote server that should be
rehashed instead of the current one.

Numeric replies:

RPL_REHASHING (382)
ERR_NOPRIVILEGES (481)
Example:

 REHASH                          ; message from user with operator
                                 status to server asking it to reread
                                 its configuration file.
*/

std::vector<Reply>	Server::rehash(User *user, std::vector<std::string> args)
{
	std::vector<Reply> reply;
	(void)args;

	if (user->get_status() == USR_STAT_BAN)
		reply.push_back(ERR_YOUREBANNEDCREEP);
	else if (user->get_connected() == false)
		reply.push_back(ERR_NOTREGISTERED);
	else
	{
		reply.push_back(ERR_UNKNOWNCOMMAND);
		reply[0].add_user(user);
		reply[0].add_arg("REHASH", "command");
		reply[0].prep_to_send(1);
	}
	return (reply);
}
