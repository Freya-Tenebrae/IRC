/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pong.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaginot <cmaginot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 18:15:54 by cmaginot          #+#    #+#             */
/*   Updated: 2023/03/28 17:49:56 by cmaginot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INCL/User.hpp"
#include "../../INCL/Reply.hpp"
#include "../../INCL/Server.hpp"

/*
Command: PONG
Parameters: [<server>] <token>

The PONG command is used as a reply to PING commands, by both clients and servers.
The <token> should be the same as the one in the PING message that triggered this PONG.

Servers MUST send a <server> parameter, and clients SHOULD ignore it. It exists for
historical reasons, and indicates the name of the server sending the PONG.
Clients MUST NOT send a <server> parameter.

Numeric Replies:

None
*/

static bool token_match(User *user, std::string token)
{
	(void)token;
	(void)user;
	return (true);
}

std::vector<Reply>	Server::pong(User *user, std::vector<std::string> args)
{
	std::vector<Reply>	reply;
	int 				token = 0;

	if (user->get_status() == USR_STAT_BAN)
		reply.push_back(ERR_YOUREBANNEDCREEP);
	else if (user->get_connected() == false)
		reply.push_back(ERR_NOTREGISTERED);
	else if (args.empty() == true || args[token].compare("") == 0)	// NEED TO SEE HOW TO IDENTIFY THE NICKNAME IN ARGS
		reply.push_back(ERR_NOORIGIN);
	else if (token_match(user, args[token]) == false) // check if token is the same
		reply.push_back(ERR_TOKENMISMATCH);
	else
	{
		// update ping/pong value on User.cpp
		reply.push_back(NO_REPLY);
	}
	reply[0].add_user(user);
	reply[0].add_arg("PONG", "");
	reply[0].prep_to_send(1);
	return (reply);
}
