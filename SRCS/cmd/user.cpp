/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaginot <cmaginot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 18:15:54 by cmaginot          #+#    #+#             */
/*   Updated: 2023/05/19 13:03:14 by cmaginot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INCL/User.hpp"
#include "../../INCL/Reply.hpp"
#include "../../INCL/Server.hpp"

/*
Command: USER
Parameters: <username> 0 * <realname>

The USER command is used at the beginning of a connection to specify the
username and realname of a new user->

It must be noted that <realname> must be the last parameter because it may
contain SPACE (' ', 0x20) characters, and should be prefixed with a 
colon (:) if required.

Servers MAY use the Ident Protocol to look up the ‘real username’ of clients.
If username lookups are enabled and a client does not have an Identity Server
enabled, the username provided by the client SHOULD be prefixed by a tilde 
('~', 0x7E) to show that this value is user-set.

The maximum length of <username> may be specified by the USERLEN RPL_ISUPPORT
parameter. If this length is advertised, the username MUST be silently truncated
to the given length before being used. The minimum length of <username> is 1, ie.
it MUST NOT be empty. If it is empty, the server SHOULD reject the command with
ERR_NEEDMOREPARAMS (even if an empty parameter is provided); otherwise it MUST
use a default value instead.

The second and third parameters of this command SHOULD be sent as one zero 
('0', 0x30) and one asterisk character ('*', 0x2A) by the client, as the meaning
of these two parameters varies between different versions of the IRC protocol.

Clients SHOULD use the nickname as a fallback value for <username> and <realname>
when they don’t have a meaningful value to use.

If a client tries to send the USER command after they have already completed
registration with the server, the ERR_ALREADYREGISTERED reply should be sent
and the attempt should fail.

If the client sends a USER command after the server has successfully received
a username using the Ident Protocol, the <username> parameter from this command
should be ignored in favour of the one received from the identity server.

Numeric Replies:

ERR_NEEDMOREPARAMS (461)
ERR_ALREADYREGISTERED (462)
*/

int Server::check_number_user_with_specific_mod(char mod)
{
	int i = 0;

	for (std::vector<User *>::iterator it = _usr_list.begin(); it != _usr_list.end(); it++)
		if ((*it)->check_if_mode_is_used(mod) == true)
			i++;
	return (i);
}

std::vector<Reply>	Server::user(User *user, std::vector<std::string> args)
{
	std::vector<Reply>	reply, reply_motd, reply_luser;
	std::vector<std::string> to_motd, to_luser;
	std::string			realname_str = "";
	int 				username = 0;
	int					realname = 3;
	(void)args;

	if (user->get_status() == USR_STAT_BAN)
		reply.push_back(ERR_YOUREBANNEDCREEP);
	else if (user->get_connected() == false)
		reply.push_back(ERR_NOTREGISTERED);
	else if (args.empty() == true || args[username].compare("") == 0 || args.size() < 3)
	{
		reply.push_back(ERR_NEEDMOREPARAMS);
		reply[reply.size() - 1].add_arg("USER", "command");
	}
	else if (user->get_status() == USR_STAT_REGISTERED)
		reply.push_back(ERR_ALREADYREGISTERED);
	else
	{
		for (size_t i = realname; i < args.size(); i++)
			realname_str.append(args[i]);
		realname_str.erase(realname_str.begin());
		// if (username_is_conform())
		user->set_username(args[username]);
		// else
		// 	user->set_username(user.get_nickname());
		// if (realname_is_conform())
		user->set_realname(realname_str);
		// else
		// 	user->set_realname(user.get_nickname());
		user->set_status(USR_STAT_REGISTERED);
		reply.push_back(RPL_WELCOME);
		reply[0].add_arg("", "networkname");
		reply[0].add_arg(user->get_nickname(), "nick");
		reply[0].add_arg(user->get_username(), "user");
		reply[0].add_arg(user->get_hostaddr(), "host");
		reply.push_back(RPL_YOURHOST);
		reply[1].add_arg(get_name(), "servername");
		reply[1].add_arg(get_version(), "version");
		reply.push_back(RPL_CREATED);
		reply[2].add_arg("", "datetime");
		reply.push_back(RPL_MYINFO);
		reply[3].add_arg(get_name(), "servername");
		reply[3].add_arg(get_version(), "version");
		reply[3].add_arg("", "available user modes");
		reply[3].add_arg("", "available channel modes");
		// do something with [<channel modes with a parameter>]
	}
	for (std::vector<Reply>::iterator it = reply.begin(); it != reply.end(); it++)
	{
		it->add_user(user);
		it->prep_to_send(1);
	}
	reply_luser = lusers(user, to_luser);
	reply.insert(reply.end(), reply_luser.begin(), reply_luser.end());
	reply_motd = motd(user, to_motd);
	reply.insert(reply.end(), reply_motd.begin(), reply_motd.end());
	return (reply);
}
