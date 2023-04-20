/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   who.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaginot <cmaginot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 18:15:54 by cmaginot          #+#    #+#             */
/*   Updated: 2023/04/17 18:44:03 by cmaginot         ###   ########.fr       */
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
	(void)user;
	(void)args;

	return (reply);
}
