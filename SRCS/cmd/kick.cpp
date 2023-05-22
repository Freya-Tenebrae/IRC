/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaginot <cmaginot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 18:15:54 by cmaginot          #+#    #+#             */
/*   Updated: 2023/05/19 13:00:14 by cmaginot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INCL/User.hpp"
#include "../../INCL/Reply.hpp"
#include "../../INCL/Server.hpp"

/*
Command: KICK
Parameters: <channel> <user> *( "," <user> ) [<comment>]

The KICK command can be used to request the forced removal of a user from a channel.
It causes the <user> to be removed from the <channel> by force. If no comment
is given, the server SHOULD use a default message instead.

The server MUST NOT send KICK messages with multiple users to clients. This is
necessary to maintain backward compatibility with existing client software.

Servers MAY limit the number of target users per KICK command via the TARGMAX
parameter of RPL_ISUPPORT, and silently drop targets if the number of targets
exceeds the limit.

Numeric Replies:

ERR_NEEDMOREPARAMS (461)
ERR_NOSUCHCHANNEL (403)
ERR_CHANOPRIVSNEEDED (482)
ERR_USERNOTINCHANNEL (441)
ERR_NOTONCHANNEL (442)
Deprecated Numeric Reply:

ERR_BADCHANMASK (476)
Examples:

   KICK #Finnish Matthew           ; Command to kick Matthew from
								   #Finnish

   KICK &Melbourne Matthew         ; Command to kick Matthew from
								   &Melbourne

   KICK #Finnish John :Speaking English
								   ; Command to kick John from #Finnish
								   using "Speaking English" as the
								   reason (comment).

   :WiZ!jto@tolsun.oulu.fi KICK #Finnish John
								   ; KICK message on channel #Finnish
								   from WiZ to remove John from channel
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

std::vector<Reply>	Server::kick(User *user, std::vector<std::string> args)
{
	std::vector<Reply>			reply, to_send;
	int								chan_name = 0;
	int								usr_targeted = 1;
	std::string 					message = "";

	if (user->get_status() == USR_STAT_BAN)
		reply.push_back(ERR_YOUREBANNEDCREEP);
	else if (user->get_connected() == false)
		reply.push_back(ERR_NOTREGISTERED);
	else if (args.empty() == true || args[chan_name].compare("") == 0 || args.size() <= 1 || args[usr_targeted].compare("") == 0)
	{
		reply.push_back(ERR_NEEDMOREPARAMS);
		reply[reply.size() - 1].add_arg("KICK", "command");
	}
	else
	{
		if (channel_exist(this, args[chan_name]) == false)
		{
			reply.push_back(ERR_NOSUCHCHANNEL);
			reply[reply.size() - 1].add_arg(args[chan_name], "channel");
		}
		else
		{
			Channel *chan = find_channel(args[chan_name]);

			if (user_is_on_channel(chan, user) == false)
			{
				reply.push_back(ERR_NOTONCHANNEL);
				reply[reply.size() - 1].add_arg(args[chan_name], "channel");
			}
			else if (chan->check_if_complexe_mode_is_correct('o', user->get_nickname()) == false)
			{
				reply.push_back(ERR_CHANOPRIVSNEEDED);
				reply[reply.size() - 1].add_arg(args[chan_name], "channel");
			}
			else
			{
				User *usr = find_user_by_nickname(args[usr_targeted]);

				if (user_is_on_channel(chan, usr) == false)
				{
					reply.push_back(ERR_USERNOTINCHANNEL);
					reply[reply.size() - 1].add_arg(args[chan_name], "channel");
					reply[reply.size() - 1].add_arg(args[usr_targeted], "nick");
				}
				else
				{
					if (args.size() >= 2)
					{
						for (std::vector<std::string>::iterator it = args.begin() + 2; it != args.end(); it++)
						{
							message.append(" ");
							message.append(*it);
						}
						message.erase(0, 2);
					}

					reply.push_back(MSG_KICK);
					reply[reply.size() - 1].add_arg(args[chan_name], "channel");
					reply[reply.size() - 1].add_arg(args[usr_targeted], "nick");
					reply[reply.size() - 1].add_arg(message, "message");

					to_send.push_back(MSG_KICK);
					to_send[0].add_user(user);
					to_send[0].add_arg(args[chan_name], "channel");
					to_send[0].add_arg(args[usr_targeted], "nick");
					to_send[0].add_arg(message, "message");
					to_send[0].prep_to_send(1);

					for (std::vector<User *>::const_iterator it_usr = chan->get_ch_usr_list().begin(); it_usr != chan->get_ch_usr_list().end(); it_usr++)
					{
						if (*it_usr != user)
							send_message(*it_usr, to_send[0].get_message());
					}

					chan->del_user(usr);
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
