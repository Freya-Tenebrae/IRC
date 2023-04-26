/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   notice.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaginot <cmaginot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 18:15:54 by cmaginot          #+#    #+#             */
/*   Updated: 2023/04/26 13:40:52 by cmaginot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INCL/User.hpp"
#include "../../INCL/Reply.hpp"
#include "../../INCL/Server.hpp"

/*
Command: NOTICE
Parameters: <target>{,<target>} <text to be sent>

The NOTICE command is used to send notices between users, as well as to send notices
to channels. <target> is interpreted the same way as it is for the PRIVMSG command.

The NOTICE message is used similarly to PRIVMSG. The difference between NOTICE and
PRIVMSG is that automatic replies must never be sent in response to a NOTICE message.
This rule also applies to servers – they must not send any error back to the client on
receipt of a NOTICE command. The intention of this is to avoid loops between a client
automatically sending something in response to something it received. This is typically
used by ‘bots’ (a client with a program, and not a user, controlling their actions) and
also for server messages to clients.

One thing for bot authors to note is that the NOTICE message may be interpreted differently
by various clients. Some clients highlight or interpret any NOTICE sent to a channel in the
same way that a PRIVMSG with their nickname gets interpreted. This means that users may be
irritated by the use of NOTICE messages rather than PRIVMSG messages by clients or bots,
and they are not commonly used by client bots for this reason.
*/

static bool channel_exist(Server *server, std::string target)
{
	Channel *chan = server->find_channel(target);
	if (chan == NULL)
		return (false);
	return (true);
}

static bool user_is_on_channel(Channel *chan, User *user)
{
	for (std::vector<User *>::const_iterator it = chan->get_ch_usr_list().begin(); it != chan->get_ch_usr_list().end(); it++)
	{
		if (*it == user)
			return (true);
	}
	return (false);
}

void Server::notice_channel(User *user, std::vector<std::string> &args, std::string &message)
{
	std::vector<Reply>	to_send;

	args[0].erase(0, 1);

	for (std::vector<Channel *>::iterator it = _cha_list.begin(); it != _cha_list.end(); it++)
	{
		std::string chan_name = (*it)->get_name();
		chan_name.erase(0, 1);
		if (chan_name.compare(args[0]) == 0)
		{
			if (((*it)->check_if_complexe_mode_is_correct('b', user->get_nickname()) == false || \
				(*it)->check_if_complexe_mode_is_correct('e', user->get_nickname()) == true || \
				(*it)->check_if_complexe_mode_is_correct('o', user->get_nickname()) == true) && \
				!((*it)->check_if_simple_mode_is_used('n') == true && user_is_on_channel(*it, user) == false) && \
				!((*it)->check_if_simple_mode_is_used('m') == true && ((*it)->check_if_complexe_mode_is_correct('o', user->get_nickname()) == false && \
					(*it)->check_if_complexe_mode_is_correct('v', user->get_nickname()) == false)))
			{
				to_send.push_back(MSG_NOTICE);
				to_send[0].add_user(user);
				to_send[0].add_arg((*it)->get_name(), "channel_or_client");
				to_send[0].add_arg(message, "message");
				to_send[0].prep_to_send(1);

				for (std::vector<User *>::const_iterator it_usr = (*it)->get_ch_usr_list().begin(); it_usr != (*it)->get_ch_usr_list().end(); it_usr++)
				{
					if (*it_usr != user)
						send_message(*it_usr, to_send[0].get_message());
				}
			}
			break;
		}
	}
}

void Server::notice_user(User *user, const User *target, std::string &message)
{
	std::vector<Reply>	to_send;

	to_send.push_back(MSG_NOTICE);
	to_send[0].add_user(user);
	to_send[0].add_arg(target->get_nickname(), "channel_or_client");
	to_send[0].add_arg(message, "message");
	to_send[0].prep_to_send(1);

	send_message(target, to_send[0].get_message());
}

std::vector<Reply>	Server::notice(User *user, std::vector<std::string> args)
{
	std::vector<Reply>	reply;
	int					target = 0;
	int					message_strat = 1;
	std::string			message;

	if (user->get_status() != USR_STAT_BAN && user->get_connected() == true && \
		args.empty() == false && args[target].compare("") != 0 && \
		args.size() >= 2 && args[message_strat].compare("") != 0 && \
		args[message_strat][0] == ':' && (args.size() >= 3 || args[message_strat].compare(":") != 0))
	{
		for (std::vector<std::string>::iterator it = args.begin() + 1; it != args.end(); it++)
		{
			message.append(" ");
			message.append(*it);
		}
		message.erase(0, 2);

		if (args[target][0] == '#' || args[target][0] == '&')
		{
			if (channel_exist(this, args[target]) == true)
				privmsg_channel(user, args, message);
		}
		else
		{
			const User *user_target = find_user_by_nickname(args[target]);
			if (user_target != NULL)
				notice_user(user, user_target, message);
		}
	}
	return (reply);
}
