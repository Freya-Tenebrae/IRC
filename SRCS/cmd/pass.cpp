/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaginot <cmaginot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 18:15:54 by cmaginot          #+#    #+#             */
/*   Updated: 2023/04/17 18:43:51 by cmaginot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INCL/User.hpp"
#include "../../INCL/Reply.hpp"
#include "../../INCL/Server.hpp"

/*
Command: PASS
Parameters: <password>

The PASS command is used to set a ‘connection password’. If set, the password 
must be set before any attempt to register the connection is made. This requires 
that clients send a PASS command before sending the NICK / USER combination.

The password supplied must match the one defined in the server configuration. 
It is possible to send multiple PASS commands before registering but only the 
last one sent is used for verification and it may not be changed once the client 
has been registered.

If the password supplied does not match the password expected by the server, 
then the server SHOULD send ERR_PASSWDMISMATCH (464) and MAY then close the 
connection with ERROR. Servers MUST send at least one of these two messages.

Servers may also consider requiring SASL authentication upon connection as an 
alternative to this, when more information or an alternate form of identity 
verification is desired.

Numeric replies:

ERR_NEEDMOREPARAMS (461)
ERR_ALREADYREGISTERED (462)
ERR_PASSWDMISMATCH (464)
*/

std::vector<Reply>	Server::pass(User *user, std::vector<std::string> args)
{
	std::vector<Reply>	reply;
	int 				password = 0;

	if (user->get_status() == USR_STAT_BAN)
		reply.push_back(ERR_YOUREBANNEDCREEP);
	else if (args.empty() == true || args[password].compare("") == 0)
	{
		reply.push_back(ERR_NEEDMOREPARAMS);
		reply[0].add_arg("PASS", "command");
	}
	else if (user->get_connected() == true)
		reply.push_back(ERR_ALREADYREGISTERED);
	else if (args[password].compare(this->_password))
		reply.push_back(ERR_PASSWDMISMATCH);
	else
	{
		user->set_connected();
		reply.push_back(RPL_NONE);
	}
	reply[0].add_user(user);
	reply[0].prep_to_send(1);
	return(reply);
}
