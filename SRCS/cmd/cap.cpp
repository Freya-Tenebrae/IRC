/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cap.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaginot <cmaginot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 18:15:54 by cmaginot          #+#    #+#             */
/*   Updated: 2023/03/30 18:18:05 by cmaginot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INCL/User.hpp"
#include "../../INCL/Reply.hpp"
#include "../../INCL/Server.hpp"

/*
Command: CAP
Parameters: <subcommand> [:<capabilities>]

The CAP command is used for capability negotiation between a server and a client.

The CAP message may be sent from the server to the client.

For the exact semantics of the CAP command and subcommands, please see the
Capability Negotiation specification.
(https://ircv3.net/specs/extensions/capability-negotiation.html)
*/

std::vector<Reply>	Server::cap(User *user, std::vector<std::string> args) // do not use
{
	std::vector<Reply> reply;
	(void)args;

	if (user->get_status() == USR_STAT_BAN)
		reply.push_back(ERR_YOUREBANNEDCREEP);
	else
	{
		reply.push_back(ERR_UNKNOWNCOMMAND);
		reply[0].add_user(user);
		reply[0].add_arg("CAP", "command");
		reply[0].prep_to_send(1);
	}
	return (reply);
}
