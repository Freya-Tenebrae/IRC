/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaginot <cmaginot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 18:15:54 by cmaginot          #+#    #+#             */
/*   Updated: 2023/05/22 17:05:57 by cmaginot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INCL/User.hpp"
#include "../../INCL/Reply.hpp"
#include "../../INCL/Server.hpp"

/*
Command: PING
Parameters: <token>

The PING command is sent by either clients or servers to check the other side
of the connection is still connected and/or to check for connection latency,
at the application layer.

The <token> may be any non-empty string.
str
When receiving a PING message, clients or servers must reply to it with a PONG
message with the same <token> value. This allows either to match PONG with the
PING they reply to, for example to compute latency.

Clients should not send PING during connection registration, though servers may
accept it. Servers may send PING during connection registration and clients must
reply to them.

Older versions of the protocol gave specific semantics to the <token> and allowed
an extra parameter; but these features are not consistently implemented and should
not be relied on. Instead, the <token> should be treated as an opaque value by
the receiver.

Numeric Replies:

ERR_NEEDMOREPARAMS (461)
ERR_NOORIGIN (409)
*/

std::vector<Reply>	Server::ping(User *user, std::vector<std::string> args)
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

// std::vector<Reply>	Server::ping(User *user, std::vector<std::string> args)
// {
// 	std::vector<Reply>	reply;
// 	int 				token = 0;

// 	if (user->get_status() == USR_STAT_BAN)
// 		reply.push_back(ERR_YOUREBANNEDCREEP);
// 	else if (user->get_connected() == false)
// 		reply.push_back(ERR_NOTREGISTERED);
// 	else if (args.empty() == true || args[token].compare("") == 0)	// NEED TO SEE HOW TO IDENTIFY THE NICKNAME IN ARGS
// 		reply.push_back(ERR_NOORIGIN);
// 	else
// 	{
// 		reply.push_back(RPL_PONG);
// 		reply[0].add_user(user);
// 		reply[0].add_arg(args[token], "tocken");
// 		return (reply);
// 	}
// 	reply[0].add_user(user);
// 	reply[0].add_arg("PING", "command");
// 	reply[0].prep_to_send(1);
// 	return (reply);
// }
