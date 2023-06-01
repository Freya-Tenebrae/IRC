/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   away.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaginot <cmaginot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 18:15:54 by cmaginot          #+#    #+#             */
/*   Updated: 2023/06/01 16:07:38 by cmaginot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INCL/User.hpp"
#include "../../INCL/Reply.hpp"
#include "../../INCL/Server.hpp"

/*
Command: AWAY
Parameters: [ <text> ]

The AWAY command lets clients indicate that their user is away. If this command is
sent with a nonempty parameter (the ‘away message’) then the user is set to be away.
If this command is sent with no parameters, or with the empty string as the parameter,
the user is no longer away.

The server acknowledges the change in away status by returning the RPL_NOWAWAY (306)
and RPL_UNAWAY (305) numerics. If the IRCv3 away-notify capability has been requested
by a client, the server MAY also send that client AWAY messages to tell them how the
away status of other users has changed.

Servers SHOULD notify clients when a user they’re interacting with is away when relevant,
including sending these numerics:

RPL_AWAY (301), with the away message, when a PRIVMSG command is directed at the away user
(not to a channel they are on).
RPL_AWAY (301), with the away message, in replies to WHOIS messages.
In the RPL_USERHOST (302) numeric, as the + or - character.
In the RPL_WHOREPLY (352) numeric, as the H or G character.
Numeric Replies:

RPL_UNAWAY (305)
RPL_NOWAWAY (306)
*/

std::vector<Reply>	Server::away(User *user, std::vector<std::string> args)
{
	std::vector<Reply>	reply;
	std::string			away_message;

	if (user->get_status() == USR_STAT_BAN)
		reply.push_back(ERR_YOUREBANNEDCREEP);
	else if (user->get_connected() == false)
		reply.push_back(ERR_NOTREGISTERED);
	else if (args.size() == 0)
	{
		user->set_status(USR_STAT_REGISTERED);
		user->set_status_message("");
		reply.push_back(RPL_UNAWAY);
	}
	else if (args.size() >= 1 && args[0].empty() == false)
	{
		for (std::vector<std::string>::iterator it = args.begin() + 1; it != args.end(); it++)
		{
			away_message.append(" ");
			away_message.append(*it);
		}
		away_message.erase(0, 1);

		user->set_status(USR_STAT_AWAY);
		user->set_status_message(away_message);
		reply.push_back(RPL_NOWAWAY);
	}
	reply[0].add_user(user);
	reply[0].prep_to_send(1);
	return (reply);
}
