/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaginot <cmaginot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 18:15:54 by cmaginot          #+#    #+#             */
/*   Updated: 2023/05/19 12:59:50 by cmaginot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INCL/User.hpp"
#include "../../INCL/Reply.hpp"
#include "../../INCL/Server.hpp"

/*
Command: JOIN
Parameters: <channel>{,<channel>} [<key>{,<key>}]
Alt Params: 0

The JOIN command indicates that the client wants to join the given channel(s),
each channel using the given key for it. The server receiving the command checks
whether or not the client can join the given channel, and processes the request.
Servers MUST process the parameters of this command as lists on incoming commands
from clients, with the first <key> being used for the first <channel>, the
second <key> being used for the second <channel>, etc.

While a client is joined to a channel, they receive all relevant information
about that channel including the JOIN, PART, KICK, and MODE messages affecting
the channel. They receive all PRIVMSG and NOTICE messages sent to the channel,
and they also receive QUIT messages from other clients joined to the same channel
(to let them know those users have left the channel and the network).
This allows them to keep track of other channel members and channel modes.

If a client’s JOIN command to the server is successful, the server MUST send,
in this order:

A JOIN message with the client as the message <source> and the channel they have
joined as the first parameter of the message.
The channel’s topic (with RPL_TOPIC (332) and optionally RPL_TOPICWHOTIME (333)),
and no message if the channel does not have a topic.
A list of users currently joined to the channel (with one or more RPL_NAMREPLY (353)
numerics followed by a single RPL_ENDOFNAMES (366) numeric). These RPL_NAMREPLY
messages sent by the server MUST include the requesting client that has just joined
the channel.
The key, client limit , ban - exception, invite-only - exception, and other
(depending on server software) channel modes affect whether or not a given client
may join a channel. More information on each of these modes and how they affect
the JOIN command is available in their respective sections.

Servers MAY restrict the number of channels a client may be joined to at one time.
This limit SHOULD be defined in the CHANLIMIT RPL_ISUPPORT parameter. If the
client cannot join this channel because they would be over their limit, they
will receive an ERR_TOOMANYCHANNELS (405) reply and the command will fail.

Note that this command also accepts the special argument of ("0", 0x30) instead
of any of the usual parameters, which requests that the sending client leave all
channels they are currently connected to. The server will process this command as
though the client had sent a PART command for each channel they are a member of.

This message may be sent from a server to a client to notify the client that someone
has joined a channel. In this case, the message <source> will be the client who is
joining, and <channel> will be the channel which that client has joined. Servers
SHOULD NOT send multiple channels in this message to clients, and SHOULD distribute
these multiple-channel JOIN messages as a series of messages with a single channel
name on each.

Numeric Replies:

ERR_NEEDMOREPARAMS (461)
ERR_NOSUCHCHANNEL (403) // not use
ERR_TOOMANYCHANNELS (405) // not use (maybe)
ERR_BADCHANNELKEY (475)
ERR_BANNEDFROMCHAN (474)
ERR_CHANNELISFULL (471)
ERR_INVITEONLYCHAN (473)
ERR_BADCHANMASK (476)
RPL_TOPIC (332)
RPL_TOPICWHOTIME (333)
RPL_NAMREPLY (353)
RPL_ENDOFNAMES (366)

Command Examples:

  JOIN #foobar                    ; join channel #foobar.

  JOIN &foo fubar                 ; join channel &foo using key "fubar".

  JOIN #foo,&bar fubar            ; join channel #foo using key "fubar"
								  and &bar using no key.

  JOIN #foo,#bar fubar,foobar     ; join channel #foo using key "fubar".
								  and channel #bar using key "foobar".

  JOIN #foo,#bar                  ; join channels #foo and #bar.

Message Examples:

  :WiZ JOIN #Twilight_zone        ; WiZ is joining the channel
								  #Twilight_zone

  :dan-!d@localhost JOIN #test    ; dan- is joining the channel #test
*/

size_t npos = -1;

std::vector<Reply> Server::try_to_join(User *user, std::string channel_name, std::string channel_key)
{
	std::vector<Reply>			reply, to_send, reply_topic, reply_names;
	std::vector<std::string>	args_to_topic_and_name;
	bool						is_creator = false;

	Channel *chan = find_channel(channel_name);
	if (chan == NULL)
	{
		chan = new Channel(channel_name);
		_cha_list.push_back(chan);
		is_creator = true;
	}

		// ERR_TOOMANYCHANNELS (405) // not use (maybe)
	if (chan->check_if_complexe_mode_is_used('k') && chan->check_if_complexe_mode_is_correct('k', channel_key) == false)
		reply.push_back(ERR_BADCHANNELKEY);
	else if (chan->check_if_simple_mode_is_used('i') == true && chan->check_if_complexe_mode_is_correct('I', user->get_nickname()) == false)
		reply.push_back(ERR_INVITEONLYCHAN);
	else if (chan->get_number_max_user() != -1 && chan->get_number_act_user() >= chan->get_number_max_user())
		reply.push_back(ERR_CHANNELISFULL);
	else if (chan->check_if_complexe_mode_is_used('b') == true && chan->check_if_complexe_mode_is_correct('b', user->get_nickname()) == true && chan->check_if_complexe_mode_is_correct('e', user->get_nickname()) == false) // tmp ban on nickname
		reply.push_back(ERR_BANNEDFROMCHAN);
	else
	{
		chan->add_user(user);
		if (is_creator == true)
			chan->add_complex_channelmode('o', user->get_nickname());

		const std::vector<User *> ch_usr_list_ref = chan->get_ch_usr_list();

		args_to_topic_and_name.push_back(channel_name);
		reply_topic = topic(user, args_to_topic_and_name);
		reply_names = names(user, args_to_topic_and_name);

		reply.push_back(MGS_JOIN);

		to_send.push_back(MGS_JOIN);
		to_send[0].add_user(user);
		to_send[0].add_arg(chan->get_name(), "channel");
		to_send[0].prep_to_send(1);

		for (std::vector<User *>::const_iterator it = ch_usr_list_ref.begin(); it != ch_usr_list_ref.end(); it++)
		{
			if (*it != user)
				send_message(*it, to_send[0].get_message());
		}

	}
	for (std::vector<Reply>::iterator it = reply.begin(); it != reply.end(); it++)
	{
		it->add_user(user);
		it->add_arg(chan->get_name(), "channel");
		it->prep_to_send(1);
	}
	reply.insert(reply.end(), reply_topic.begin(), reply_topic.end());
	reply.insert(reply.end(), reply_names.begin(), reply_names.end());
	return (reply);
}

std::vector<Reply> Server::join(User *user, std::vector<std::string> args)
{
	std::vector<Reply>						reply;
	int										channel_name = 0;
	int										channel_key = 1;
	std::multimap<std::string, std::string>	name_key;

	if (user->get_status() == USR_STAT_BAN)
		reply.push_back(ERR_YOUREBANNEDCREEP);
	else if (user->get_connected() == false)
		reply.push_back(ERR_NOTREGISTERED);
	else if (args.empty() == true || args[channel_name].compare("") == 0)
	{
		reply.push_back(ERR_NEEDMOREPARAMS);
		reply[reply.size() - 1].add_arg("JOIN", "command");
	}
	else
	{
		std::string channel_name_list = args[channel_name].substr();
		std::string channel_key_list = "";
		if (args.size() != 1)
			channel_key_list = args[channel_key].substr();

		while (channel_name_list.compare("") != 0)
		{
			std::string	channel_name_unique = "", channel_key_unique = "";
			size_t		channel_name_coma_pos = 0, channel_key_coma_pos = 0;

			channel_name_coma_pos = channel_name_list.find_first_of(',');
			if (channel_name_coma_pos == npos)
			{
				channel_name_unique = channel_name_list.substr();
				channel_name_list = "";
			}
			else
			{
				channel_name_unique = channel_name_list.substr(0, channel_name_coma_pos);
				channel_name_list.erase(0, channel_name_coma_pos + 1);
			}

			channel_key_coma_pos = channel_key_list.find_first_of(',');
			if (channel_key_coma_pos == npos)
			{
				channel_key_unique = channel_key_list.substr();
				channel_key_list = "";
			}
			else
			{
				channel_key_unique = channel_key_list.substr(0, channel_key_coma_pos);
				channel_key_list.erase(0, channel_key_coma_pos + 1);
			}
			name_key.insert(std::pair<std::string, std::string>(channel_name_unique,channel_key_unique));
		}

		for (std::multimap<std::string, std::string>::iterator it = name_key.begin(); it != name_key.end(); it++)
		{
			std::vector<Reply> tmp_reply = try_to_join(user, it->first, it->second);
			reply.insert(reply.end(), tmp_reply.begin(), tmp_reply.end());
		}
	}

	return (reply);
}
