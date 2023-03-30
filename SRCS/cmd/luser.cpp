/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   luser.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaginot <cmaginot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 18:15:54 by cmaginot          #+#    #+#             */
/*   Updated: 2023/03/28 17:51:21 by cmaginot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INCL/User.hpp"
#include "../../INCL/Reply.hpp"
#include "../../INCL/Server.hpp"

/*
Command: LUSERS
Parameters: None

Returns statistics about local and global users, as numeric replies.

Servers MUST reply with RPL_LUSERCLIENT and RPL_LUSERME, and SHOULD
also include all those defined below.

Clients SHOULD NOT try to parse the free-form text in the trailing
parameter, and rely on specific parameters instead.

RPL_LUSERCLIENT (251)
RPL_LUSEROP (252)
RPL_LUSERUNKNOWN (253)
RPL_LUSERCHANNELS (254)
RPL_LUSERME (255)
RPL_LOCALUSERS (265)
RPL_GLOBALUSERS (266)
*/

std::vector<Reply>	Server::lusers(User *user, std::vector<std::string> args)
{
	(void)args;

	std::vector<Reply> reply;

	if (user->get_status() == USR_STAT_BAN)
		reply.push_back(ERR_YOUREBANNEDCREEP);
	else if (user->get_connected() == false)
		reply.push_back(ERR_NOTREGISTERED);
	else
	{
		reply.push_back(RPL_LUSERCLIENT);
		reply[0].add_arg(convert_int_to_string(_usr_list.size()), "u"); // number of user connected
		reply[0].add_arg(convert_int_to_string(check_number_user_with_specific_mod('i')), "i"); // number of invisible user
		reply[0].add_arg("1", "s"); // number of server = 1
		reply.push_back(RPL_LUSEROP);
		reply[1].add_arg(convert_int_to_string(check_number_user_with_specific_mod('o')), "ops"); // number of operators connected
		reply.push_back(RPL_LUSERUNKNOWN);
		reply[2].add_arg(convert_int_to_string(_usr_list.size()), "connections"); // number of connections = user ??
		reply.push_back(RPL_LUSERCHANNELS);
		reply[3].add_arg("", "channels"); // number of channel
		reply.push_back(RPL_LUSERME);
		reply[4].add_arg(convert_int_to_string(_usr_list.size()), "c"); // number of clients = user ??
		reply[4].add_arg("1", "s"); // number of server = 1
		// RPL_LOCALUSERS and RPL_GLOBALUSERS are not used here : no connection between server.
	}
	for (std::vector<Reply>::iterator it = reply.begin(); it != reply.end(); it++)
	{
		it->add_user(user);
		it->prep_to_send(1);
	}
	return (reply);
}
