/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   names.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaginot <cmaginot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 18:15:54 by cmaginot          #+#    #+#             */
/*   Updated: 2023/05/19 13:01:05 by cmaginot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INCL/User.hpp"
#include "../../INCL/Reply.hpp"
#include "../../INCL/Server.hpp"

/*
Command: NAMES
Parameters: <channel>{,<channel>}

The NAMES command is used to view the nicknames joined to a channel and their channel membership prefixes. The param of this command is a list of channel names, delimited by a comma (",", 0x2C) character.

The channel names are evaluated one-by-one. For each channel that exists and they are able to see the users in, the server returns one of more RPL_NAMREPLY numerics containing the users joined to the channel and a single RPL_ENDOFNAMES numeric. If the channel name is invalid or the channel does not exist, one RPL_ENDOFNAMES numeric containing the given channel name should be returned. If the given channel has the secret channel mode set and the user is not joined to that channel, one RPL_ENDOFNAMES numeric is returned. Users with the invisible user mode set are not shown in channel responses unless the requesting client is also joined to that channel.

Servers MAY allow more than one target channel. They can advertise the maximum the number of target users per NAMES command via the TARGMAX RPL_ISUPPORT parameter.

Numeric Replies:

RPL_NAMREPLY (353)
RPL_ENDOFNAMES (366)
*/

std::vector<Reply>	Server::names(User *user, std::vector<std::string> args)
{
	std::vector<Reply> reply;
	int channel_name = 0;
	
	if (user->get_status() == USR_STAT_BAN)
		reply.push_back(ERR_YOUREBANNEDCREEP);
	else if (user->get_connected() == false)
		reply.push_back(ERR_NOTREGISTERED);
	else if (args.empty() == true || args[channel_name].compare("") == 0)
	{
		reply.push_back(ERR_NEEDMOREPARAMS);
		reply[reply.size() - 1].add_arg("NAMES", "command");
	}
	else
	{
		Channel *chan = find_channel(args[channel_name]);
		if (chan == NULL)
		{
			reply.push_back(ERR_NOSUCHCHANNEL);
			reply[reply.size() - 1].add_arg(args[channel_name], "channel");
		}
		else
		{
			const std::vector<User *> ch_usr_list_ref = chan->get_ch_usr_list();
			reply.push_back(RPL_NAMREPLY);
			reply[reply.size() - 1].add_arg("=", "symbol"); // for the moment, need to check if it's always '='
			reply[reply.size() - 1].add_arg(args[channel_name], "channel");
			for (std::vector<User *>::const_iterator it = ch_usr_list_ref.begin(); it != ch_usr_list_ref.end(); it++)
			{
				if (it != ch_usr_list_ref.begin())
					reply[reply.size() - 1].add_loop(RPL_NAMREPLY_LOOP);

				if (chan->check_if_complexe_mode_is_correct('o', (*it)->get_nickname()) == true)
					reply[reply.size() - 1].add_arg_alt("@", "prefix");
				else
					reply[reply.size() - 1].add_arg_alt("", "prefix");

				reply[reply.size() - 1].add_arg((*it)->get_nickname(), "nick");
			}
			
			reply.push_back(RPL_ENDOFNAMES);
			reply[reply.size() - 1].add_arg(args[channel_name], "channel");
		}
	}

	for (std::vector<Reply>::iterator it = reply.begin(); it != reply.end(); it++)
	{
		it->add_user(user);
		it->prep_to_send(1);
	}

	return (reply);
}
