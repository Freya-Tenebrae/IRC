/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plam <plam@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 18:15:54 by cmaginot          #+#    #+#             */
/*   Updated: 2023/04/25 19:59:49 by plam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INCL/User.hpp"
#include "../../INCL/Reply.hpp"
#include "../../INCL/Server.hpp"

/*
Command: TOPIC
Parameters: <channel> [<topic>]

The TOPIC command is used to change or view the topic of the given channel.
If <topic> is not given, either RPL_TOPIC or RPL_NOTOPIC is returned specifying
the current channel topic or lack of one. If <topic> is an empty string, the topic
for the channel will be cleared.

If the client sending this command is not joined to the given channel, and tries to
view its’ topic, the server MAY return the ERR_NOTONCHANNEL (442) numeric and have
the command fail.

If RPL_TOPIC is returned to the client sending this command, RPL_TOPICWHOTIME SHOULD
also be sent to that client.

If the protected topic mode is set on a channel, then clients MUST have appropriate
channel permissions to modify the topic of that channel. If a client does not have
appropriate channel permissions and tries to change the topic, the
ERR_CHANOPRIVSNEEDED (482) numeric is returned and the command will fail.

If the topic of a channel is changed or cleared, every client in that channel
(including the author of the topic change) will receive a TOPIC command with the new
topic as argument (or an empty argument if the topic was cleared) alerting them to how
the topic has changed.

Clients joining the channel in the future will receive a RPL_TOPIC numeric (or lack
thereof) accordingly.

Numeric Replies:

ERR_NEEDMOREPARAMS (461)
ERR_NOSUCHCHANNEL (403)
ERR_NOTONCHANNEL (442)
ERR_CHANOPRIVSNEEDED (482)
RPL_NOTOPIC (331)
RPL_TOPIC (332)
RPL_TOPICWHOTIME (333)
Command Examples:

  TOPIC #test :New topic          ; Setting the topic on "#test" to
								  "New topic".

  TOPIC #test :                   ; Clearing the topic on "#test"

  TOPIC #test                     ; Checking the topic for "#test"
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

std::vector<Reply>	Server::topic(User *user, std::vector<std::string> args)
{
	std::vector<Reply> reply;

	if (user->get_status() == USR_STAT_BAN)
		reply.push_back(ERR_YOUREBANNEDCREEP);
	else if (user->get_connected() == false)
		reply.push_back(ERR_NOTREGISTERED);
	else if (args.empty() == true || args[0].compare("") == 0)
		reply.push_back(ERR_NEEDMOREPARAMS);
	else
	{
		if (args.size() == 1 && args[0][0] == '#')
		{
			if (channel_exist(this, args[0]))
			{
				Channel	*chan = find_channel(args[0]);
				if (user_is_on_channel(chan, user) == true)			//verify if the static function work correctly
				{
					if (chan->get_topic().empty() == false)
					{
						reply.push_back(RPL_TOPIC);
						reply[reply.size()-1].add_arg(chan->get_topic(), "topic");
					}
					else
						reply.push_back(RPL_NOTOPIC);
				}
				else
					reply.push_back(ERR_NOTONCHANNEL);
			}
			else
				reply.push_back(ERR_NOSUCHCHANNEL);
		}
		else if (args.size() == 2 && args[0][0] == '#')
		{
			if (channel_exist(this, args[0]))
			{
				Channel	*chan = find_channel(args[0]);
				if (user_is_on_channel(chan, user) == true)			//verify if the static function work correctly
				{
					if (chan->check_if_simple_mode_is_used('t') == true)		// see if operators are the only users that can change the topic in the server
					{
						if (user->check_if_mode_is_used('o') == true || user->check_if_mode_is_used('v'))		// only channel operator can change the topic of a channel
						{
							chan->set_topic(args[1]);
							reply.push_back(RPL_TOPIC);
						}
					}
					else
						reply.push_back(ERR_CHANOPRIVSNEEDED);
				}
				else
					reply.push_back(ERR_NOTONCHANNEL);
			}
			else
				reply.push_back(ERR_NOSUCHCHANNEL);
		}
		else
			reply.push_back(ERR_NOSUCHCHANNEL);
	}
	for (std::vector<Reply>::iterator it = reply.begin(); it != reply.end(); it++)
	{
		it->add_user(user);
		it->prep_to_send(1);
	}
	return (reply);
}