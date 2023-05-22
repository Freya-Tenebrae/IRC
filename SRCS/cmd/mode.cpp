/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaginot <cmaginot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 18:15:54 by cmaginot          #+#    #+#             */
/*   Updated: 2023/05/22 17:26:10 by cmaginot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INCL/User.hpp"
#include "../../INCL/Reply.hpp"
#include "../../INCL/Server.hpp"

/*
Command: MODE
Parameters: <target> [<modestring> [<mode arguments>...]]

The MODE command is used to set or remove options (or modes) from a given target.

User mode
If <target> is a nickname that does not exist on the network, the ERR_NOSUCHNICK (401)
numeric is returned. If <target> is a different nick than the user who sent the command,
the ERR_USERSDONTMATCH (502) numeric is returned.

If <modestring> is not given, the RPL_UMODEIS (221) numeric is sent back containing the
current modes of the target user->

If <modestring> is given, the supplied modes will be applied, and a MODE message will be
sent to the user containing the changed modes. If one or more modes sent are not
implemented on the server, the server MUST apply the modes that are implemented, and
then send the ERR_UMODEUNKNOWNFLAG (501) in reply along with the MODE message.

Channel mode
If <target> is a channel that does not exist on the network, the ERR_NOSUCHCHANNEL (403)
numeric is returned.

If <modestring> is not given, the RPL_CHANNELMODEIS (324) numeric is returned. Servers
MAY choose to hide sensitive information such as channel keys when sending the current
modes. Servers MAY also return the RPL_CREATIONTIME (329) numeric following RPL_CHANNELMODEIS.

If <modestring> is given, the user sending the command MUST have appropriate channel
privileges on the target channel to change the modes given. If a user does not have
appropriate privileges to change modes on the target channel, the server MUST NOT process
the message, and ERR_CHANOPRIVSNEEDED (482) numeric is returned. If the user has permission
to change modes on the target, the supplied modes will be applied based on the type of the
mode (see below). For type A, B, and C modes, arguments will be sequentially obtained from
<mode arguments>. If a type B or C mode does not have a parameter when being set, the server
MUST ignore that mode. If a type A mode has been sent without an argument, the contents of
the list MUST be sent to the user, unless it contains sensitive information the user is not
allowed to access. When the server is done processing the modes, a MODE command is sent to all
members of the channel containing the mode changes. Servers MAY choose to hide sensitive
information when sending the mode changes.

<modestring> starts with a plus ('+', 0x2B) or minus ('-', 0x2D) character, and is made up of
the following characters:

'+': Adds the following mode(s).
'-': Removes the following mode(s).
'a-zA-Z': Mode letters, indicating which modes are to be added/removed.
The ABNF representation for <modestring> is:

  modestring  =  1*( modeset )
  modeset     =  plusminus *( modechar )
  plusminus   =  %x2B / %x2D
                   ; + or -
  modechar    =  ALPHA
There are four categories of channel modes, defined as follows:

Type A: Modes that add or remove an address to or from a list. These modes MUST always have a
parameter when sent from the server to a client. A client MAY issue this type of mode without
an argument to obtain the current contents of the list. The numerics used to retrieve contents
of Type A modes depends on the specific mode. Also see the EXTBAN parameter.
Type B: Modes that change a setting on a channel. These modes MUST always have a parameter.
Type C: Modes that change a setting on a channel. These modes MUST have a parameter when being
set, and MUST NOT have a parameter when being unset.
Type D: Modes that change a setting on a channel. These modes MUST NOT have a parameter.
Channel mode letters, along with their types, are defined in the CHANMODES parameter. User mode
letters are always Type D modes.

The meaning of standard (and/or well-used) channel and user mode letters can be found in the
Channel Modes and User Modes sections. The meaning of any mode letters not in this list are
defined by the server software and configuration.

Type A modes are lists that can be viewed. The method of viewing these lists is not standardised
across modes and different numerics are used for each. The specific numerics used for these are
outlined here:

Ban List "+b": Ban lists are returned with zero or more RPL_BANLIST (367) numerics, followed
by one RPL_ENDOFBANLIST (368) numeric.
Exception List "+e": Exception lists are returned with zero or more RPL_EXCEPTLIST (348)
numerics,followed by one RPL_ENDOFEXCEPTLIST (349) numeric.
Invite-Exception List "+I": Invite-exception lists are returned with zero or more
RPL_INVITELIST (336) numerics, followed by one RPL_ENDOFINVITELIST (337) numeric.
After the initial MODE command is sent to the server, the client receives the above numerics
detailing the entries that appear on the given list. Servers MAY choose to restrict the above
information to channel operators, or to only those clients who have permissions to change the
given list.
*/

/*

	WE CHOSE TO ONLY WORK WITH ONLY ONE TARGET 

*/

static bool user_is_on_channel(Channel *chan, User *user)
{
	for (std::vector<User *>::const_iterator it = chan->get_ch_usr_list().begin(); it != chan->get_ch_usr_list().end(); it++)
	{
		if (*it == user)
			return (true);
	}
	return (false);
}

static bool channel_exist(Server *server, std::string target)
{
	Channel *chan = server->find_channel(target);
	if (chan == NULL)
		return (false);
	return (true);
}

static bool modestring_valid(std::string modestring)
{
	if (modestring.compare("") == 0 || (modestring[0] != '-' && modestring[0] != '+'))
		return (false);
	for (std::string::iterator it = modestring.begin() + 1; it != modestring.end(); it++)
	{
		if (!((*it >= 'a' && *it <= 'z') || (*it >= 'A' && *it <= 'Z')))
			return (false);
	}
	return (true);
}

static void	reply_channel_mode(Channel *chan, std::vector<std::string> &args, std::vector<Reply> &reply)
{
	int target = 0;

	reply.push_back(RPL_CHANNELMODEIS);
	reply[reply.size() - 1].add_arg(args[target], "channel");
	for (std::multimap<char, std::string>::const_iterator it = chan->get_channelmode().begin(); it != chan->get_channelmode().end(); it++)
	{
		std::string modestring = "";
		modestring.append(1, it->first);
		std::string m_args = it->second;

		reply[reply.size() - 1].add_loop(RPL_CHANNELMODEIS_LOOP);
		reply[reply.size() - 1].add_arg(modestring, "modestring");
		reply[reply.size() - 1].add_arg(m_args, "mode arguments");
	}

	for (std::multimap<char, std::string>::const_iterator it = chan->get_channelmode().begin(); it != chan->get_channelmode().end(); it++)
	{
		if (it->first == 'b')
		{
			reply.push_back(RPL_BANLIST);

			reply[reply.size() - 1].add_arg(args[target], "channel");
			reply[reply.size() - 1].add_arg(it->second, "mask");
		}
	}
	reply.push_back(RPL_ENDOFBANLIST);
	reply[reply.size() - 1].add_arg(args[target], "channel");

	for (std::multimap<char, std::string>::const_iterator it = chan->get_channelmode().begin(); it != chan->get_channelmode().end(); it++)
	{
		if (it->first == 'e')
		{
			reply.push_back(RPL_EXCEPTLIST);

			reply[reply.size() - 1].add_arg(args[target], "channel");
			reply[reply.size() - 1].add_arg(it->second, "mask");
		}
	}
	reply.push_back(RPL_ENDOFEXCEPTLIST);
	reply[reply.size() - 1].add_arg(args[target], "channel");

	for (std::multimap<char, std::string>::const_iterator it = chan->get_channelmode().begin(); it != chan->get_channelmode().end(); it++)
	{
		if (it->first == 'I')
		{
			reply.push_back(RPL_INVITELIST);

			reply[reply.size() - 1].add_arg(args[target], "channel");
			reply[reply.size() - 1].add_arg(it->second, "mask");
		}
	}
	reply.push_back(RPL_ENDOFINVITELIST);
	reply[reply.size() - 1].add_arg(args[target], "channel");
}

static void kick_after_ban(Server *serv, User *user, Channel *chan, std::string mask)
{
	std::vector<Reply> to_send;
	User *usr = serv->find_user_by_nickname(mask);

	if (user_is_on_channel(chan, usr) == true)
	{
		to_send.push_back(MSG_KICK);
		to_send[0].add_user(user);
		to_send[0].add_arg(chan->get_name(), "channel");
		to_send[0].add_arg(mask, "nick");
		to_send[0].add_arg("you are banned from this channel", "message");
		to_send[0].prep_to_send(1);

		for (std::vector<User *>::const_iterator it_usr = chan->get_ch_usr_list().begin(); it_usr != chan->get_ch_usr_list().end(); it_usr++)
			serv->send_message(*it_usr, to_send[0].get_message());

		chan->del_user(usr);
	}
}

static void	apply_mode_on_channel(Server *serv, User *user, Channel *chan, std::vector<std::string> &args, std::vector<Reply> &reply)
{
	int		argument_ptr = 1;
	int		modestring = 1;
	bool	all_mode_are_valid = true;
	bool	is_addition = true;

	if (modestring_valid(args[modestring]) == false)
		reply.push_back(ERR_UMODEUNKNOWNFLAG);
	else
	{
		if (args[modestring][0] == '-')
			is_addition = false;
		for (std::string::iterator it = args[modestring].begin() + 1; it != args[modestring].end(); it++)
		{
			std::string sim_mode = SIMPLE_CHANNEL_MODE_AVAILABLE;
			std::string com_mode = COMPLEX_CHANNEL_MODE_AVAILABLE;
			std::string spe_mode = SPECIFIC_CHANNEL_MODE_AVAILABLE;


			if (sim_mode.find(*it) == std::string::npos && com_mode.find(*it) == std::string::npos && spe_mode.find(*it) == std::string::npos)
				all_mode_are_valid = false;
			else if (sim_mode.find(*it) != std::string::npos)
			{
				if (is_addition == true && chan->check_if_simple_mode_is_used(*it) == false)
					chan->add_simple_channelmode(*it);
				else if (is_addition == false && chan->check_if_simple_mode_is_used(*it) == true)
					chan->del_simple_channelmode(*it);
			}
			else if (com_mode.find(*it) != std::string::npos)
			{
				if (args.size() > static_cast<size_t>(modestring + argument_ptr))
				{
					std::string mask = args[modestring + argument_ptr++];
					if (is_addition == true && chan->check_if_complexe_mode_is_correct(*it, mask) == false)
					{
						chan->add_complex_channelmode(*it, mask);
						if (*it == 'b' && chan->check_if_complexe_mode_is_correct('e', mask) == false && chan->check_if_complexe_mode_is_correct('o', mask) == false)
							kick_after_ban(serv, user, chan, mask);
					}
					else if (is_addition == false && chan->check_if_complexe_mode_is_correct(*it, mask) == true)
						chan->del_complex_channelmode(*it, mask);
				}
				else
					all_mode_are_valid = false;
			}
			else
			{
				if (args.size() > static_cast<size_t>(modestring + argument_ptr))
				{
					if (is_addition == true)
					{
						std::string s_value = args[modestring + argument_ptr++];
						std::stringstream strstr;
						int value;
						strstr << s_value;
						strstr >> value;

						chan->add_specific_channelmode(*it, value);
					}
					else if (is_addition == false && chan->check_if_specific_mode_is_used(*it) == true)
						chan->del_specific_channelmode(*it);
				}
				else
					all_mode_are_valid = false;
			}
		}

		if (all_mode_are_valid != true)
			reply.push_back(ERR_UMODEUNKNOWNFLAG);
		reply_channel_mode(chan, args, reply);
	}
}

static void	apply_mode_on_user(User *user, std::vector<std::string> &args, std::vector<Reply> &reply)
{
	bool	all_mode_are_valid = true;
	int		modestring = 1;
	bool	is_addition = true;

	if (modestring_valid(args[modestring]) == false)
		reply.push_back(ERR_UMODEUNKNOWNFLAG);
	else
	{
		if (args[modestring][0] == '-')
			is_addition = false;
		for (std::string::iterator it = args[modestring].begin() + 1; it != args[modestring].end(); it++)
		{
			std::string str = USER_MODE_AVAILABLE;
			if (str.find(*it) == std::string::npos)
				all_mode_are_valid = false;
			else if (is_addition == true && user->check_if_mode_is_used(*it) == false)
				user->add_usermode(*it);
			else if (is_addition == false && user->check_if_mode_is_used(*it) == true)
				user->del_usermode(*it);
		}

		if (all_mode_are_valid != true)
			reply.push_back(ERR_UMODEUNKNOWNFLAG);
		reply.push_back(RPL_UMODEIS);
		reply.back().add_arg(user->get_usermode(), "user modes");
	}
}

std::vector<Reply>	Server::mode(User *user, std::vector<std::string> args)
{
	std::vector<Reply> reply;
	unsigned long target = 0;
	unsigned long modestring = 1;

	if (user->get_status() == USR_STAT_BAN)
		reply.push_back(ERR_YOUREBANNEDCREEP);
	else if (user->get_connected() == false)
		reply.push_back(ERR_NOTREGISTERED);
	else if (args.empty() == true || args[target].compare("") == 0)
	{
		reply.push_back(ERR_NEEDMOREPARAMS);
		reply[reply.size() - 1].add_arg("MODE", "command");
	}
	else
	{
		if (args[target][0] == '#' || args[target][0] == '&')
		{
			if (channel_exist(this, args[target]) == false)
				reply.push_back(ERR_NOSUCHCHANNEL);
			else
			{
				Channel *chan = find_channel(args[target]);

				if (modestring == args.size())
					reply_channel_mode(chan, args, reply);
				else
				{
					if (chan->check_if_complexe_mode_is_correct('o', user->get_nickname()) == false)
					{
						reply.push_back(ERR_CHANOPRIVSNEEDED);
						reply[reply.size() - 1].add_arg(args[target], "channel");
					}
					else
						apply_mode_on_channel(this, user, chan, args, reply);
				}
			}
		}
		else
		{
			if (user->get_nickname().compare(args[target]) != 0)
				reply.push_back(ERR_USERSDONTMATCH);
			else
			{
				if (modestring == args.size())
				{
					reply.push_back(RPL_UMODEIS);
					reply.back().add_arg(user->get_usermode(), "user modes");
				}
				else
					apply_mode_on_user(user, args, reply);
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
