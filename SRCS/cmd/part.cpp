/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaginot <cmaginot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 18:15:54 by cmaginot          #+#    #+#             */
/*   Updated: 2023/04/25 20:58:59 by cmaginot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INCL/User.hpp"
#include "../../INCL/Reply.hpp"
#include "../../INCL/Server.hpp"

/*
Command: PART
Parameters: <channel>{,<channel>} [<reason>]

The PART command removes the client from the given channel(s).
On sending a successful PART command, the user will receive a PART message from
the server for each channel they have been removed from. <reason> is the reason
that the client has left the channel(s).

For each channel in the parameter of this command, if the channel exists and the
client is not joined to it, they will receive an ERR_NOTONCHANNEL (442) reply and
that channel will be ignored. If the channel does not exist, the client will
receive an ERR_NOSUCHCHANNEL (403) reply and that channel will be ignored.

This message may be sent from a server to a client to notify the client that
someone has been removed from a channel. In this case, the message <source> will
be the client who is being removed, and <channel> will be the channel which that
client has been removed from. Servers SHOULD NOT send multiple channels in this
message to clients, and SHOULD distribute these multiple-channel PART messages as
a series of messages with a single channel name on each. If a PART message is
distributed in this way, <reason> (if it exists) should be on each of these messages.

Numeric Replies:

ERR_NEEDMOREPARAMS (461)
ERR_NOSUCHCHANNEL (403)
ERR_NOTONCHANNEL (442)
Command Examples:

  PART #twilight_zone             ; leave channel "#twilight_zone"

  PART #oz-ops,&group5            ; leave both channels "&group5" and
								  "#oz-ops".
Message Examples:

  :dan-!d@localhost PART #test    ; dan- is leaving the channel #test
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

std::vector<Reply>	Server::part(User *user, std::vector<std::string> args)
{
	std::vector<Reply>			reply, to_send;
	std::vector<std::string>	chan_name;
	int							target = 0;
	std::string 				message = "";

	if (user->get_status() == USR_STAT_BAN)
		reply.push_back(ERR_YOUREBANNEDCREEP);
	else if (user->get_connected() == false)
		reply.push_back(ERR_NOTREGISTERED);
	else if (args.empty() == true || args[target].compare("") == 0)
		reply.push_back(ERR_NEEDMOREPARAMS);
	else
	{
		std::string channel_name_list = args[target].substr();
		while (channel_name_list.compare("") != 0)
		{
			std::string	channel_name_unique = "";
			size_t		channel_name_coma_pos = 0;

			channel_name_coma_pos = channel_name_list.find_first_of(',');
			if (channel_name_coma_pos == std::string::npos)
			{
				channel_name_unique = channel_name_list.substr();
				channel_name_list = "";
			}
			else
			{
				channel_name_unique = channel_name_list.substr(0, channel_name_coma_pos);
				channel_name_list.erase(0, channel_name_coma_pos + 1);
			}
			chan_name.push_back(channel_name_unique);
		}

		if (args.size() >= 2)
		{
			for (std::vector<std::string>::iterator it = args.begin() + 1; it != args.end(); it++)
			{
				message.append(" ");
				message.append(*it);
			}
			message.erase(0, 2);
		}

		for (std::vector<std::string>::iterator it = chan_name.begin(); it != chan_name.end(); it++)
		{
			if (channel_exist(this, *it) == false)
			{
				reply.push_back(ERR_NOSUCHCHANNEL);
				reply[reply.size() - 1].add_arg(*it, "channel");
			}
			else
			{
				Channel *chan = find_channel(*it);

				if (user_is_on_channel(chan, user) == false)
				{
					reply.push_back(ERR_NOTONCHANNEL);
					reply[reply.size() - 1].add_arg(*it, "channel");
				}
				else
				{
					chan->del_user(user);

					reply.push_back(MSG_PART);
					reply[reply.size() - 1].add_arg(chan->get_name(), "channel");
					reply[reply.size() - 1].add_arg(message, "message");

					to_send.push_back(MSG_PART);
					to_send[0].add_user(user);
					to_send[0].add_arg(chan->get_name(), "channel");
					to_send[0].add_arg(message, "message");
					to_send[0].prep_to_send(1);

					for (std::vector<User *>::const_iterator it_usr = chan->get_ch_usr_list().begin(); it_usr != chan->get_ch_usr_list().end(); it_usr++)
					{
						if (*it_usr != user)
							send_message(*it_usr, to_send[0].get_message());
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
