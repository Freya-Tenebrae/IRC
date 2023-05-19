/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wallops.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaginot <cmaginot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 18:15:54 by cmaginot          #+#    #+#             */
/*   Updated: 2023/05/19 13:03:37 by cmaginot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INCL/User.hpp"
#include "../../INCL/Reply.hpp"
#include "../../INCL/Server.hpp"

/*
Command: WALLOPS
Parameters: <text>

The WALLOPS command is used to send a message to all currently connected users who have set the ‘w’ user mode for themselves. The <text> SHOULD be non-empty.

Servers MAY echo WALLOPS messages to their sender even if they don’t have the ‘w’ user mode.

Servers MAY send WALLOPS only to operators.

Servers may generate it themselves, and MAY allow operators to send them.

Numeric replies:

ERR_NEEDMOREPARAMS (461)
ERR_NOPRIVILEGES (481)
ERR_NOPRIVS (723)
Examples:

 :csd.bu.edu WALLOPS :Connect '*.uiuc.edu 6667' from Joshua
                                 ;WALLOPS message from csd.bu.edu announcing
                                 a CONNECT message it received and acted
                                 upon from Joshua.

*/

std::vector<Reply>	Server::wallops(User *user, std::vector<std::string> args)
{
	std::vector<Reply>	reply, to_send;
	std::string			message = "";
	int					text = 0;

	if (user->get_status() == USR_STAT_BAN)
		reply.push_back(ERR_YOUREBANNEDCREEP);
	else if (user->get_connected() == false)
		reply.push_back(ERR_NOTREGISTERED);
	else if (args.empty() == true || args[text].compare("") == 0)
	{
		reply.push_back(ERR_NEEDMOREPARAMS);
		reply[reply.size() - 1].add_arg("WALLOPS", "command");
	}
	else if (user->check_if_mode_is_used('o') == false)
		reply.push_back(ERR_NOPRIVILEGES);
	else
	{
		to_send.push_back(MGS_WALLOP);
		to_send[0].add_user(user);
		for (std::vector<std::string>::iterator it = args.begin(); it != args.end(); it++)
		{
			message.append(*it);
			message.push_back(' ');
		}
		to_send[0].add_arg(message, "message");
		to_send[0].prep_to_send(1);
		for (std::vector<User *>::iterator it = _usr_list.begin(); it != _usr_list.end(); it++)
		{
			if (*it == user || (*it)->check_if_mode_is_used('w') == true)
				send_message(*it, to_send[0].get_message());
		}
		return (reply);
	}
	reply[0].add_user(user);
	reply[0].prep_to_send(1);
	return (reply);
}
