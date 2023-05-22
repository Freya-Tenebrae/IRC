/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaginot <cmaginot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 18:15:54 by cmaginot          #+#    #+#             */
/*   Updated: 2023/05/19 12:59:28 by cmaginot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INCL/User.hpp"
#include "../../INCL/Reply.hpp"
#include "../../INCL/Server.hpp"

/*
Command: INVITE
Parameters: <nickname> <channel>

The INVITE command is used to invite a user to a channel. The parameter
<nickname> is the nickname of the person to be invited to the target channel <channel>.

The target channel SHOULD exist (at least one user is on it). Otherwise,
the server SHOULD reject the command with the ERR_NOSUCHCHANNEL numeric.

Only members of the channel are allowed to invite other users. Otherwise,
the server MUST reject the command with the ERR_NOTONCHANNEL numeric.

Servers MAY reject the command with the ERR_CHANOPRIVSNEEDED numeric.
In particular, they SHOULD reject it when the channel has invite-only mode set,
and the user is not a channel operator.

If the user is already on the target channel, the server MUST reject the command
with the ERR_USERONCHANNEL numeric.

When the invite is successful, the server MUST send a RPL_INVITING numeric to the
command issuer, and an INVITE message, with the issuer as <source>, to the target
user-> Other channel members SHOULD NOT be notified.

Numeric Replies:

RPL_INVITING (341)
ERR_NEEDMOREPARAMS (461)
ERR_NOSUCHCHANNEL (403)
ERR_NOTONCHANNEL (442)
ERR_CHANOPRIVSNEEDED (482)
ERR_USERONCHANNEL (443)
Command Examples:

  INVITE Wiz #foo_bar    ; Invite Wiz to #foo_bar
Message Examples:

  :dan-!d@localhost INVITE Wiz #test    ; dan- has invited Wiz
										to the channel #test
*/

static bool channel_exist(Server *server, std::string target)
{
	Channel *chan = server->find_channel(target);
	if (chan == NULL)
		return (false);
	return (true);
}

static bool user_is_on_channel(Channel *chan, User *user)
{
	for (std::vector<User *>::const_iterator it = chan->get_ch_usr_list().begin(); it != chan->get_ch_usr_list().end(); it++)
	{
		if (*it == user)
			return (true);
	}
	return (false);
}

std::vector<Reply>	Server::invite(User *user, std::vector<std::string> args)
{
	std::vector<Reply>	reply, to_send;
	
	if (user->get_status() == USR_STAT_BAN)
		reply.push_back(ERR_YOUREBANNEDCREEP);
	else if (user->get_connected() == false)
		reply.push_back(ERR_NOTREGISTERED);
	else if (args.empty() == true || args[0].compare("") == 0 || args.size() < 2 || args[1].compare("") == 0)
	{
		reply.push_back(ERR_NEEDMOREPARAMS);
		reply[reply.size() - 1].add_arg("INVITE", "command");
	}
	else if (channel_exist(this, args[1]) == false)
	{
		reply.push_back(ERR_NOSUCHCHANNEL);
		reply[reply.size() - 1].add_arg(args[1], "channel");
	}
	else
	{
		Channel	*chan = find_channel(args[1]);
		if (user_is_on_channel(chan, user) == false)
		{
			reply.push_back(ERR_NOTONCHANNEL);
			reply[reply.size() - 1].add_arg(args[1], "channel");
		}
		else
		{
			User *target = find_user_by_nickname(args[0]);
			if (target == NULL)
			{
				reply.push_back(ERR_NOSUCHNICK);
				reply[reply.size() - 1].add_arg(args[0], "nickname");
			}
			else
			{
				if (chan->check_if_simple_mode_is_used('i') == true)
				{
					if (user->check_if_mode_is_used('I') == true || user->check_if_mode_is_used('o') == true)	// only channel operator can invite a user on a invite only channel
					{
						reply.push_back(ERR_CHANOPRIVSNEEDED);
						reply[reply.size() - 1].add_arg(args[1], "channel");
					}
					else
					{
						if (user_is_on_channel(chan, target) == true)
						{
							reply.push_back(ERR_USERONCHANNEL);
							reply[reply.size() - 1].add_arg(args[0], "nick");
							reply[reply.size() - 1].add_arg(args[1], "channel");
						}
						else
						{
							chan->add_complex_channelmode('I', args[0]);
							reply.push_back(RPL_INVITING);
							reply[reply.size() - 1].add_arg(args[0], "nick");
							reply[reply.size() - 1].add_arg(args[1], "channel");

							to_send.push_back(MGS_INVITE);
							to_send[0].add_arg(args[0], "nick");
							to_send[0].add_arg(args[1], "channel");
							to_send[0].add_user(user);
							to_send[0].prep_to_send(1);
							send_message(target, to_send[0].get_message());
						}
					}
				}
				else
				{
					if (user_is_on_channel(chan, target) == true)
					{
						reply.push_back(ERR_USERONCHANNEL);
						reply[reply.size() - 1].add_arg(args[0], "nick");
						reply[reply.size() - 1].add_arg(args[1], "channel");
					}
					else
					{
						chan->add_complex_channelmode('I', args[0]);
						reply.push_back(RPL_INVITING);
						reply[reply.size() - 1].add_arg(args[0], "nick");
						reply[reply.size() - 1].add_arg(args[1], "channel");
						
						to_send.push_back(MGS_INVITE);
						to_send[0].add_arg(args[0], "nick");
						to_send[0].add_arg(args[1], "channel");
						to_send[0].add_user(user);
						to_send[0].prep_to_send(1);
						send_message(target, to_send[0].get_message());
					}
				}
			}
		}
	}
	for (std::vector<Reply>::iterator it = reply.begin(); it != reply.end(); it++)
	{
		it->add_user(user);
		it->prep_to_send(1);
	}
	return (reply);
}
