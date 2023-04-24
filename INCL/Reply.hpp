/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Reply.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaginot <cmaginot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 17:32:30 by cmaginot          #+#    #+#             */
/*   Updated: 2023/04/24 19:41:25 by cmaginot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REPLY_HPP
# define REPLY_HPP

# include <vector>
# include <string>
# include <cstring>
# include <iostream>
# include <sstream>

# include "../INCL/User.hpp"

class Reply
{
	private:
		int				_value;
		std::string		_message;
		User			*_user;

	public:
		Reply();
		Reply(int value, std::string message);
		Reply(const Reply &reply);
		~Reply();
		Reply		&operator=(const Reply &other);
		void		add_loop(std::string loop, int pos = -1);
		void		add_arg(std::string arg, std::string to_replace);
		void		add_arg_alt(std::string arg, std::string to_replace);
		void		add_user(User *user);
		int			get_value() const;
		std::string	get_message() const;
		void		prep_to_send(int mode = 0);

};

#define RPL_WELCOME Reply(001, "<client> :Welcome to the <networkname> Network, <nick>[!<user>@<host>]\n")
#define RPL_YOURHOST Reply(002, "<client> :Your host is <servername>, running version <version>\n")
#define RPL_CREATED Reply(003, "<client> :This server was created <datetime>\n")
#define RPL_MYINFO Reply(004, "<client> <servername> <version> <available user modes> <available channel modes> [<channel modes with a parameter>]\n")
#define RPL_ISUPPORT Reply(005, "<client> <1-13 tokens> :are supported by this server\n")
#define RPL_BOUNCE Reply(010, "<client> <hostname> <port> :<info>\n")
#define RPL_STATSLINKINFO Reply(211, "\n")
#define RPL_STATSCOMMANDS Reply(212, "\n")
#define RPL_STATSCLINE Reply(213, "\n")
#define RPL_STATSILINE Reply(215, "\n")
#define RPL_STATSKLINE Reply(216, "\n")
#define RPL_ENDOFSTATS Reply(219, "\n")
#define RPL_UMODEIS Reply(221, "<client> <user modes>\n")
#define RPL_STATSLLINE Reply(241, "\n")
#define RPL_STATSUPTIME Reply(242, "\n")
#define RPL_STATSOLINE Reply(243, "\n")
#define RPL_STATSHLINE Reply(244, "\n")
#define RPL_LUSERCLIENT Reply(251, "<client> :There are <u> users and <i> invisible on <s> servers\n")
#define RPL_LUSEROP Reply(252, "<client> <ops> :operator(s) online\n")
#define RPL_LUSERUNKNOWN Reply(253, "<client> <connections> :unknown connection(s)\n")
#define RPL_LUSERCHANNELS Reply(254, "<client> <channels> :channels formed\n")
#define RPL_LUSERME Reply(255, "<client> :I have <c> clients and <s> servers\n")
#define RPL_ADMINME Reply(256, "<client> [<server>] :Administrative info\n")
#define RPL_ADMINLOC1 Reply(257, "<client> :<info>\n")
#define RPL_ADMINLOC2 Reply(258, "<client> :<info>\n")
#define RPL_ADMINEMAIL Reply(259, "<client> :<info>\n")
#define RPL_TRYAGAIN Reply(263, "<client> <command> :Please wait a while and try again.\n")
#define RPL_LOCALUSERS Reply(265, "<client> [<u> <m>] :Current local users <u>, max <m>\n")
#define RPL_GLOBALUSERS Reply(266, "<client> [<u> <m>] :Current global users <u>, max <m>\n")
#define RPL_WHOISCERTFP Reply(276, "<nick> <client>:has client certificate fingerprint <fingerprint>\n")
#define RPL_NONE Reply(300, "")
#define RPL_AWAY Reply(301, "<client> <nick> :<message>\n")
#define RPL_USERHOST Reply(302, "<client> :[<reply>{ <reply>}]\n")
#define RPL_UNAWAY Reply(305, "<client> :You are no longer marked as being away\n")
#define RPL_NOWAWAY Reply(306, "<client> :You have been marked as being away\n")
#define RPL_WHOISREGNICK Reply(307, "<client> <nick> :has identified for this nick\n")
#define RPL_WHOISUSER Reply(311, "<nick> <client> <username> <hostname> * <realname>\n")
#define RPL_WHOISSERVER Reply(312, "<client> <nick> <server> :<server info>\n")
#define RPL_WHOISOPERATOR Reply(313, "<client> <nick> :is an IRC operator\n")
#define RPL_WHOWASUSER Reply(314, "<client> <nick> <username> <host> * :<realname>\n")
#define RPL_ENDOFWHO Reply(315, "<client> <mask> :End of WHO list\n")
#define RPL_WHOISIDLE Reply(317, "<client> <nick> <secs> <signon> :seconds idle, signon time\n")
#define RPL_ENDOFWHOIS Reply(318, "<client> <nick> :End of /WHOIS list\n")
#define RPL_WHOISCHANNELS Reply(319, "<client> <nick> :[prefix]<channel>{ [prefix]<channel>}\n")
#define RPL_WHOISSPECIAL Reply(320, "<client> <nick> :<message>\n")
#define RPL_LISTSTART Reply(321, "<client> Channel :Users  Name\n")
#define RPL_LIST Reply(322, "<client> <channel> <client count> :<topic>\n")
#define RPL_LISTEND Reply(323, "<client> :End of /LIST\n")
#define RPL_CHANNELMODEIS Reply(324, "<client> <channel> <modestring> <mode arguments>...\n")
#define RPL_CREATIONTIME Reply(329, "<client> <channel> <creationtime>\n")
#define RPL_WHOISACCOUNT Reply(330, "<client> <nick> <account> :is logged in as\n")
#define RPL_NOTOPIC Reply(331, "<client> <channel> :No topic is set\n")
#define RPL_TOPIC Reply(332, "<client> <channel> :<topic>\n")
#define RPL_TOPICWHOTIME Reply(333, "<client> <channel> <nick> <setat>\n")
#define RPL_INVITELIST Reply(336, "<client> <channel>\n")
#define RPL_ENDOFINVITELIST Reply(337, "<client> :End of /INVITE list\n")
#define RPL_WHOISACTUALLY Reply(338, "<client> <nick> <username>@<hostname> <ip> :Is actually using host\n")
#define RPL_INVITING Reply(341, "<client> <nick> <channel>\n")
#define RPL_INVEXLIST Reply(346, "<client> <channel> <mask>\n")
#define RPL_ENDOFINVEXLIST Reply(347, "<client> <channel> :End of Channel Invite Exception List\n")
#define RPL_EXCEPTLIST Reply(348, "<client> <channel> <mask>\n")
#define RPL_ENDOFEXCEPTLIST Reply(349, "<client> <channel> :End of channel exception list\n")
#define RPL_VERSION Reply(351, "<client> <version> <server> :<comments>\n")
#define RPL_WHOREPLY Reply(352, "<client> <channel> <username> <host> <server> <nick> <flags> :<hopcount> <realname>\n")
#define RPL_NAMREPLY Reply(353, "<client> <symbol> <channel> :[prefix]<nick>\n")
#define RPL_NAMREPLY_LOOP " [prefix]<nick>"
#define RPL_LINKS Reply(364, "<client> * <server> :<hopcount> <server info>\n")
#define RPL_ENDOFLINKS Reply(365, "<client> * :End of /LINKS list\n")
#define RPL_ENDOFNAMES Reply(366, "<client> <channel> :End of /NAMES list\n")
#define RPL_BANLIST Reply(367, "<client> <channel> <mask> [<who> <set-ts>]\n")
#define RPL_ENDOFBANLIST Reply(368, "<client> <channel> :End of channel ban list\n")
#define RPL_ENDOFWHOWAS Reply(369, "<client> <nick> :End of WHOWAS\n")
#define RPL_INFO Reply(371, "<client> :<string>\n")
#define RPL_MOTD Reply(372, "<client> :<line of the motd>\n")
#define RPL_ENDOFINFO Reply(374, "<client> :End of INFO list\n")
#define RPL_MOTDSTART Reply(375, "<client> :- <server> Message of the day - \n")
#define RPL_ENDOFMOTD Reply(376, "<client> :End of /MOTD command\n")
#define RPL_WHOISHOST Reply(378, "<client> <nick> :is connecting from *@localhost 127.0.0.1\n")
#define RPL_WHOISMODES Reply(379, "<client> <nick> :is using modes +ailosw\n")
#define RPL_YOUREOPER Reply(381, "<client> :You are now an IRC operator\n")
#define RPL_REHASHING Reply(382, "<client> <config file> :Rehashing\n")
#define RPL_TIME Reply(391, "<client> <server> [<timestamp> [<TS offset>]] :<human-readable time>\n")
#define ERR_UNKNOWNERROR Reply(400, "<client> <command>{ <subcommand>} :<info>\n")
#define ERR_NOSUCHNICK Reply(401, "<client> <nickname> :No such nick/channel\n")
#define ERR_NOSUCHSERVER Reply(402, "<client> <server name> :No such server\n")
#define ERR_NOSUCHCHANNEL Reply(403, "<client> <channel> :No such channel\n")
#define ERR_CANNOTSENDTOCHAN Reply(404, "<client> <channel> :Cannot send to channel\n")
#define ERR_TOOMANYCHANNELS Reply(405, "<client> <channel> :You have joined too many channels\n")
#define ERR_WASNOSUCHNICK Reply(406, "<client> :There was no such nickname\n")
#define ERR_TOOMANYTARGETS Reply(407, "<client> :There are too many target\n")
#define ERR_NOORIGIN Reply(409, "<client> :No origin specified\n")
#define ERR_NORECIPIENT Reply(411, "<client> :No recipient given (<command>)\n")
#define ERR_NOTEXTTOSEND Reply(412, "<client> :No text to send\n")
#define ERR_NOTOPLEVEL Reply(413, "<client> <mask> :No toplevel domain specified\n")
#define ERR_WILDTOPLEVEL Reply(414, "<client> <mask> :Wildcard in toplevel domain\n")
#define ERR_INPUTTOOLONG Reply(417, "<client> :Input line was too long\n")
#define ERR_UNKNOWNCOMMAND Reply(421, "<client> <command> :Unknown command\n")
#define ERR_NOMOTD Reply(422, "<client> :MOTD File is missing\n")
#define ERR_NONICKNAMEGIVEN Reply(431, "<client> :No Nickname Given\n")
#define ERR_ERRONEUSNICKNAME Reply(432, "<client> <nick> :Erroneus nickname\n")
#define ERR_NICKNAMEINUSE Reply(433, "<client> <nick> :Nickname is already in use\n")
#define ERR_NICKCOLLISION Reply(436, "<client> <nick> :Nickname collision\n") // not usefull on this project
#define ERR_USERNOTINCHANNEL Reply(441, "<client> <nick> <channel> :They aren't on that channel\n")
#define ERR_NOTONCHANNEL Reply(442, "<client> <channel> :You're not on that channel\n")
#define ERR_USERONCHANNEL Reply(443, "<client> <nick> <channel> :is already on channel\n")
#define ERR_NOTREGISTERED Reply(451, "<client> :You have not registered\n")
#define ERR_NEEDMOREPARAMS Reply(461, "<client> <command> :Not enough parameters\n")
#define ERR_ALREADYREGISTERED Reply(462, "<client> :You may not reregister\n")
#define ERR_PASSWDMISMATCH Reply(464, "<client> :Password incorrect\n")
#define ERR_YOUREBANNEDCREEP Reply(465, "<client> :You are banned from this server.\n")
#define ERR_CHANNELISFULL Reply(471, "<client> <channel> :Cannot join channel (+l)\n")
#define ERR_UNKNOWNMODE Reply(472, "<client> <modechar> :is unknown mode char to me\n")
#define ERR_INVITEONLYCHAN Reply(473, "<client> <channel> :Cannot join channel (+i)\n")
#define ERR_BANNEDFROMCHAN Reply(474, "<client> <channel> :Cannot join channel (+b)\n")
#define ERR_BADCHANNELKEY Reply(475, "<client> <channel> :Cannot join channel (+k)\n")
#define ERR_BADCHANMASK Reply(476, "<channel> :Bad Channel Mask\n")
#define ERR_NOPRIVILEGES Reply(481, "<client> :Permission denied - You are not an IRC operator\n")
#define ERR_CHANOPRIVSNEEDED Reply(482, "<client> <channel> :You're not channel operator\n")
#define ERR_CANTKILLSERVER Reply(483, "<client> :You cant kill a server!\n")
#define ERR_NOOPERHOST Reply(491, "<client> :No O-lines for your host\n")
#define ERR_UMODEUNKNOWNFLAG Reply(501, "<client> :Unknown MODE flag\n")
#define ERR_USERSDONTMATCH Reply(502, "<client> :Cant change mode for other users\n")
#define ERR_HELPNOTFOUND Reply(524, "<client> <subject> :No help available on this topic\n")
#define ERR_INVALIDKEY Reply(525, "<client> <target chan> :Key is not well-formed\n")
#define RPL_STARTTLS Reply(670, "<client> :STARTTLS successful, proceed with TLS handshake\n")
#define RPL_WHOISSECURE Reply(671, "<client> <nick> :is using a secure connection\n")
#define ERR_STARTTLS Reply(691, "<client> :STARTTLS failed (Wrong moon phase)\n")
#define ERR_INVALIDMODEPARAM Reply(696, "<client> <target chan/user> <mode char> <parameter> :<description>\n")
#define RPL_HELPSTART Reply(704, "<client> <subject> :<first line of help section>\n")
#define RPL_HELPTXT Reply(705, "<client> <subject> :<line of help text>\n")
#define RPL_ENDOFHELP Reply(706, "<client> <subject> :<last line of help text>\n")
#define ERR_NOPRIVS Reply(723, "<client> <priv> :Insufficient oper privileges.\n")
#define RPL_LOGGEDIN Reply(900, "<client> <nick>!<user>@<host> <account> :You are now logged in as <username>\n")
#define RPL_LOGGEDOUT Reply(901, "<client> <nick>!<user>@<host> :You are now logged out\n")
#define ERR_NICKLOCKED Reply(902, "<client> :You must use a nick assigned to you\n")
#define RPL_SASLSUCCESS Reply(903, "<client> :SASL authentication successful\n")
#define ERR_SASLFAIL Reply(904, "<client> :SASL authentication failed\n")
#define ERR_SASLTOOLONG Reply(905, "<client> :SASL message too long\n")
#define ERR_SASLABORTED Reply(906, "<client> :SASL authentication aborted\n")
#define ERR_SASLALREADY Reply(907, "<client> :You have already authenticated using SASL\n")
#define RPL_SASLMECHS Reply(908, "<client> <mechanisms> :are available SASL mechanisms\n")





#define ERR_TOKENMISMATCH Reply(0, "<client> :token incorrect\n")
#define RPL_PONG Reply(0, "<client> :PONG <tocken>\n")
#define RPL_NICKSET Reply(0, "NICK :<client>\n")
#define MGS_WALLOP Reply(0, "WALLOP <message>\n")
#define MGS_JOIN Reply(0, "JOIN :<channel>\n")
#define MSG_PRIVMSG Reply(0, "PRIVMSG <channel_or_client> :<message>\n")

#define ERR_ERROSAMENICKNAME Reply(434, "<client> :you already use this nickname\n")

#endif
