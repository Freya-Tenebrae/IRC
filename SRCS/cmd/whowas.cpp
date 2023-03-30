/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   whowas.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaginot <cmaginot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 18:15:54 by cmaginot          #+#    #+#             */
/*   Updated: 2023/03/22 16:23:54 by cmaginot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INCL/User.hpp"
#include "../../INCL/Reply.hpp"
#include "../../INCL/Server.hpp"

/*
Command: WHOWAS
Parameters: <nick> [<count>]

Whowas asks for information about a nickname which no longer exists. This may either be due to a nickname change or the user leaving IRC. In response to this query, the server searches through its nickname history, looking for any nicks which are lexically the same (no wild card matching here). The history is searched backward, returning the most recent entry first. If there are multiple entries, up to <count> replies will be returned (or all of them if no <count> parameter is given).

If given, <count> SHOULD be a positive number. Otherwise, a full search is done.

Servers MUST reply with either ERR_WASNOSUCHNICK (406) or a non-empty list of WHOWAS entries, both followed with RPL_ENDOFWHOWAS (369)

A WHOWAS entry is a series of numeric messages starting with RPL_WHOWASUSER (314), optionally followed by other numerics relevant to that user, such as RPL_WHOISACTUALLY (338) and RPL_WHOISSERVER (312). Clients MUST NOT assume any particular numeric other than RPL_WHOWASUSER (314) is present in a WHOWAS entry.

If the <nick> argument is missing, they SHOULD send a single reply, using either ERR_NONICKNAMEGIVEN (431) or ERR_NEEDMOREPARAMS (461).

Examples
Command Examples:

  WHOWAS someone
  WHOWAS someone 2
Reply Examples:

  :inspircd.server.example 314 val someone ident3 127.0.0.1 * :Realname
  :inspircd.server.example 312 val someone My.Little.Server :Sun Mar 20 2022 10:59:26
  :inspircd.server.example 314 val someone ident2 127.0.0.1 * :Realname
  :inspircd.server.example 312 val someone My.Little.Server :Sun Mar 20 2022 10:59:16
  :inspircd.server.example 369 val someone :End of WHOWAS

  :ergo.server.example 314 val someone ~ident3 127.0.0.1 * Realname
  :ergo.server.example 314 val someone ~ident2 127.0.0.1 * Realname
  :ergo.server.example 369 val someone :End of WHOWAS

  :solanum.server.example 314 val someone ~ident3 localhost * :Realname
  :solanum.server.example 338 val someone 127.0.0.1 :actually using host
  :solanum.server.example 312 val someone solanum.server.example :Sun Mar 20 10:07:44 2022
  :solanum.server.example 314 val someone ~ident2 localhost * :Realname
  :solanum.server.example 338 val someone 127.0.0.1 :actually using host
  :solanum.server.example 312 val someone solanum.server.example :Sun Mar 20 10:07:34 2022
  :solanum.server.example 369 val someone :End of WHOWAS

  :server.example 406 val someone :There was no such nickname
  :server.example 369 val someone :End of WHOWAS
*/

std::vector<Reply>	Server::whowas(User *user, std::vector<std::string> args)
{
	std::vector<Reply> reply;
	(void)user;
	(void)args;
	
	return (reply);
}
