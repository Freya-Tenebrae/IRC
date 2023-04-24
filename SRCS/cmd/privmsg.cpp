/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaginot <cmaginot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 18:15:54 by cmaginot          #+#    #+#             */
/*   Updated: 2023/04/24 20:36:19 by cmaginot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INCL/User.hpp"
#include "../../INCL/Reply.hpp"
#include "../../INCL/Server.hpp"

/*
Command: PRIVMSG
Parameters: <target>{,<target>} <text to be sent>

The PRIVMSG command is used to send private messages between users, as well as to send
messages to channels. <target> is the nickname of a client or the name of a channel.

If <target> is a channel name and the client is banned and not covered by a ban exception,
the message will not be delivered and the command will silently fail. Channels with the
moderated mode active may block messages from certain users. Other channel modes may affect
the delivery of the message or cause the message to be modified before delivery, and these
modes are defined by the server software and configuration being used.

If a message cannot be delivered to a channel, the server SHOULD respond with an
ERR_CANNOTSENDTOCHAN (404) numeric to let the user know that this message could not
be delivered.

If <target> is a channel name, it may be prefixed with one or more channel membership
prefix character (@, +, etc) and the message will be delivered only to the members of
that channel with the given or higher status in the channel. Servers that support this
feature will list the prefixes which this is supported for in the STATUSMSG RPL_ISUPPORT
parameter, and this SHOULD NOT be attempted by clients unless the prefix has been advertised
in this token.

If <target> is a user and that user has been set as away, the server may reply with an
RPL_AWAY (301) numeric and the command will continue.

The PRIVMSG message is sent from the server to client to deliver a message to that client.
The <source> of the message represents the user or server that sent the message, and the
<target> represents the target of that PRIVMSG (which may be the client, a channel, etc).

When the PRIVMSG message is sent from a server to a client and <target> starts with a dollar
character ('$', 0x24), the message is a broadcast sent to all clients on one or multiple servers.

Numeric Replies:

ERR_NOSUCHNICK (401)
ERR_NOSUCHSERVER (402)
ERR_CANNOTSENDTOCHAN (404)
ERR_TOOMANYTARGETS (407)
ERR_NORECIPIENT (411)
ERR_NOTEXTTOSEND (412)
ERR_NOTOPLEVEL (413)
ERR_WILDTOPLEVEL (414)
RPL_AWAY (301)
There are strange "X@Y" target rules and such which are noted in the examples of the original PRIVMSG RFC section. We need to check to make sure modern servers actually process them properly, and if so then specify them.
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

std::vector<Reply> Server::privmsg_channel(User *user, std::vector<std::string> &args, std::string &message)
{
	std::vector<Reply>	reply, to_send;

	args[0].erase(0, 1);

	for (std::vector<Channel *>::iterator it = _cha_list.begin(); it != _cha_list.end(); it++)
	{
		if ((*it)->get_name().compare(args[0]))
		{
			if ((*it)->check_if_complexe_mode_is_used('b') == true && (*it)->check_if_complexe_mode_is_correct('b', user->get_nickname()) == true && \
				(*it)->check_if_complexe_mode_is_correct('e', user->get_nickname()) == false && (*it)->check_if_complexe_mode_is_correct('o', user->get_nickname()) == false) // tmp ban on nickname
			{
				reply.push_back(ERR_BANNEDFROMCHAN);
				reply.push_back(ERR_CANNOTSENDTOCHAN);
			}
			else if (((*it)->check_if_simple_mode_is_used('n') == true && user_is_on_channel(*it, user) == false) || \
					((*it)->check_if_simple_mode_is_used('m') == true && \
					((*it)->check_if_complexe_mode_is_correct('o', user->get_nickname()) == false && (*it)->check_if_complexe_mode_is_correct('v', user->get_nickname()) == false)))
			{
				reply.push_back(ERR_CANNOTSENDTOCHAN);
			}
			else
			{
				to_send.push_back(MSG_PRIVMSG);
				to_send[0].add_user(user);
				to_send[0].add_arg((*it)->get_name(), "channel_or_client");
				to_send[0].add_arg(message, "message");
				to_send[0].prep_to_send(1);
				reply.push_back(RPL_NONE);

				for (std::vector<User *>::const_iterator it_usr = (*it)->get_ch_usr_list().begin(); it_usr != (*it)->get_ch_usr_list().end(); it_usr++)
				{
					if (*it_usr != user)
						send_message(*it_usr, to_send[0].get_message());
				}
			}
			break;
		}
	}

	return (reply);
}

std::vector<Reply> Server::privmsg_user(User *user, const User *target, std::string &message)
{
	std::vector<Reply>	reply, to_send;

	if (target->get_status() == USR_STAT_AWAY)
	{
		reply.push_back(RPL_AWAY);
		reply[reply.size() - 1].add_arg(target->get_nickname(), "nick");
		reply[reply.size() - 1].add_arg("away message -> TODO", "message");
	}

	to_send.push_back(MSG_PRIVMSG);
	to_send[0].add_user(user);
	to_send[0].add_arg(target->get_nickname(), "channel_or_client");
	to_send[0].add_arg(message, "message");
	to_send[0].prep_to_send(1);

	send_message(target, to_send[0].get_message());
	return (reply);
}

std::vector<Reply>	Server::privmsg(User *user, std::vector<std::string> args)
{
	std::vector<Reply>	reply;
	int					target = 0;
	int					message_strat = 1;
	std::string			message;

	if (user->get_status() == USR_STAT_BAN)
		reply.push_back(ERR_YOUREBANNEDCREEP);
	else if (user->get_connected() == false)
		reply.push_back(ERR_NOTREGISTERED);
	else if (args.empty() == true || args[target].compare("") == 0 || args.size() < 2 || args[message_strat].compare("") == 0)
		reply.push_back(ERR_NEEDMOREPARAMS);
	else if (args[message_strat][0] != ':')
		reply.push_back(ERR_TOOMANYTARGETS);
	else if (args.size() < 3 && args[message_strat].compare(":") == 0)
		reply.push_back(ERR_NOTEXTTOSEND);
	else
	{
		for (std::vector<std::string>::iterator it = args.begin() + 1; it != args.end(); it++)
		{
			message.append(" ");
			message.append(*it);
		}
		message.erase(0, 2);

		if (args[target][0] == '#' || args[target][0] == '&')
		{
			if (channel_exist(this, args[target]) == false)
				reply.push_back(ERR_NOSUCHCHANNEL);
			else
			{
				std::vector<Reply> tmp_reply = privmsg_channel(user, args, message);
				reply.insert(reply.end(), tmp_reply.begin(), tmp_reply.end());
			}
		}
		else
		{
			const User *user_target = find_user_by_nickname(args[target]);
			if (user_target == NULL)
				reply.push_back(ERR_NOSUCHNICK);
			else
			{
				std::vector<Reply> tmp_reply = privmsg_user(user, user_target, message);
				reply.insert(reply.end(), tmp_reply.begin(), tmp_reply.end());
			}
		}
	}
	for (std::vector<Reply>::iterator it = reply.begin(); it != reply.end(); it++)
	{
		it->add_user(user);
		it->prep_to_send(1);
	}
	return (reply);
}
