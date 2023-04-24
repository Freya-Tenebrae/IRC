/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   who.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plam <plam@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 18:15:54 by cmaginot          #+#    #+#             */
/*   Updated: 2023/04/24 16:55:59 by plam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INCL/User.hpp"
#include "../../INCL/Reply.hpp"
#include "../../INCL/Server.hpp"

/*
Command: WHO
Parameters: <mask>

This command is used to query a list of users who match the provided mask. The server will
answer this command with zero, one or more RPL_WHOREPLY, and end the list with RPL_ENDOFWHO.

The mask can be one of the following:

A channel name, in which case the channel members are listed.
An exact nickname, in which case a single user is returned.
A mask pattern, in which case all visible users whose nickname matches are listed. Servers
MAY match other user-specific values, such as the hostname, server, real name or username.
Servers MAY not support mask patterns and return an empty list.
Visible users are users who aren’t invisible (user mode +i) and who don’t have a common
channel with the requesting client. Servers MAY filter or limit visible users replies
arbitrarily.

Numeric Replies:

RPL_WHOREPLY (352)
RPL_ENDOFWHO (315)
ERR_NOSUCHSERVER (402)
See also:

IRCv3 multi-prefix Extension
WHOX
Examples
Command Examples:

  WHO emersion        ; request information on user "emersion"
  WHO #ircv3          ; list users in the "#ircv3" channel
Reply Examples:

  :calcium.libera.chat 352 dan #ircv3 ~emersion sourcehut/staff/emersion calcium.libera.chat
  		emersion H :1 Simon Ser
  :calcium.libera.chat 315 dan emersion :End of WHO list
                                  ; Reply to WHO emersion

  :calcium.libera.chat 352 dan #ircv3 ~emersion sourcehut/staff/emersion calcium.libera.chat
  		emersion H :1 Simon Ser
  :calcium.libera.chat 352 dan #ircv3 ~val limnoria/val calcium.libera.chat val H :1 Val
  :calcium.libera.chat 315 dan #ircv3 :End of WHO list
                                  ; Reply to WHO #ircv3
*/

std::vector<Reply>	Server::who(User *user, std::vector<std::string> args)
{
	std::vector<Reply> reply;
	if (args.size() == 1)
	{
		if (args[0].empty() == false) 
		{
			if (args[0][0] == '#')
			{			
				args[0].erase(0, 1);
				for (std::vector<Channel *>::iterator it = _cha_list.begin(); it != _cha_list.end(); it++)
				{
					if ((*it)->get_name().compare(args[0]))
					{
						const std::vector<User *> ch_usr_list_ref = (*it)->get_ch_usr_list();
						for (std::vector<User *>::const_iterator it_usr = ch_usr_list_ref.begin(); it_usr != ch_usr_list_ref.end(); it_usr++)
						{
							reply.push_back(RPL_WHOREPLY);
							reply[reply.size()-1].add_arg("channel to do", "channel");
							reply[reply.size()-1].add_arg((*it_usr)->get_nickname(), "user");
						}
						break ;
					}
				}
			}
			else
			{
				for (std::vector<User *>::iterator it_usr = _usr_list.begin(); it_usr != _usr_list.end(); it_usr++)
				{
					if ((*it_usr)->get_nickname().compare(args[0]))
					{
						reply.push_back(RPL_WHOREPLY);
						reply[reply.size()-1].add_arg("channel to do", "channel");
						reply[reply.size()-1].add_arg((*it_usr)->get_nickname(), "user");
					}
					break ;
				}
			}
		}
		else
			reply.push_back(ERR_NOSUCHSERVER);
		reply.push_back(RPL_ENDOFWHO);
	}
	for (std::vector<Reply>::iterator it = reply.begin(); it != reply.end(); it++)
	{
		it->add_user(user);
		it->prep_to_send(1);
	}
	return (reply);
}
