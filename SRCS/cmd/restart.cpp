/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   restart.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmercore <mmercore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 18:15:54 by cmaginot          #+#    #+#             */
/*   Updated: 2023/04/25 15:57:17 by mmercore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INCL/User.hpp"
#include "../../INCL/Reply.hpp"
#include "../../INCL/Server.hpp"

/*
Command: RESTART
Parameters: None

An operator can use the restart command to force the server to restart itself.
This message is optional since it may be viewed as a risk to allow arbitrary
people to connect to a server as an operator and execute this command, causing
(at least) a disruption to service.

Numeric replies:

ERR_NOPRIVILEGES (481)
*/

std::vector<Reply>	Server::restart(User *user, std::vector<std::string> args)
{
	std::vector<Reply> reply;
	(void)user;
	(void)args;
	if (user->get_status() == USR_STAT_BAN)
		reply.push_back(ERR_YOUREBANNEDCREEP);
	else if (user->get_connected() == false)
		reply.push_back(ERR_NOTREGISTERED);
	else if (user->check_if_mode_is_used('o') == false)
		reply.push_back(ERR_NOPRIVILEGES);
	else
		this->errval = server_restart;
	return (reply);
}
