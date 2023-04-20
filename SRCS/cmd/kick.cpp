/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaginot <cmaginot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 18:15:54 by cmaginot          #+#    #+#             */
/*   Updated: 2023/04/17 18:46:59 by cmaginot         ###   ########.fr       */
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

std::vector<Reply>	Server::kick(User *user, std::vector<std::string> args)
{
	std::vector<Reply> reply;
	(void)user;
	(void)args;

	// only channel orperator can do this command
	
	return (reply);
}
