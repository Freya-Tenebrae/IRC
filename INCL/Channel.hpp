/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaginot <cmaginot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 12:51:43 by plam              #+#    #+#             */
/*   Updated: 2023/04/17 19:30:51 by cmaginot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "ft_irc.hpp"

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

#define SIMPLE_CHANNEL_MODE_AVAILABLE "imnpst"
// i : When enabled, users need to be invited into the channel or have a matching entry in the invite list.
// m : When enabled, users who are not opped or voiced cannot send messages to the channel.
// n : When enabled, users who are not on the channel cannot send messages to it.
// p : When enabled, the channel will not be displayed in your WHOIS output.
// s : When enabled, the channel will not be displayed in the LIST output.
// t : When enabled, users who are not opped or voices cannot modify the channel topic.

#define COMPLEX_CHANNEL_MODE_AVAILABLE "beIkov"
// b : Adds or removes a ban; a ban will prevent a user who matches the given mask from joining the channel unless he or she is invited or in the exempt list.
// e : Adds or removes a ban exception; users who match a mask on the exempt list are able to join a channel even if they also match an entry on the ban list.
// I : Adds or removes an invite; users who match a mask on the invite list are able to join even if the channel is set to invite only.
// k : Adds or removes a channel key, aka a password; users will not be able to join the channel without providing the key.
// o : Adds or removes the operator status from a nickname.
// v : Adds or removes the voice status from a nickname.

#define SPECIFIC_CHANNEL_MODE_AVAILABLE "l"
// l <count>: Adds, removes or updates the maximum amount of users that may join the channel.

class Channel
{
	private:
		std::string							_name;
		int									_number_max_user;
		std::vector<User *>					_ch_usr_list;
		std::multimap<char, std::string>	_channelmode;

	public:
		Channel();
		Channel(std::string	name);
		Channel(const Channel &other);
		~Channel();
		Channel	&operator=(const Channel &other);

		const std::string						&get_name() const;
		const int								&get_number_max_user() const;
		const std::vector<User *>				&get_ch_usr_list() const;
		const User								*get_User(int fd) const;
		const std::multimap<char, std::string>	&get_channelmode() const;

		void						add_user(User *user);
		void						del_user(User *user);

		bool						check_if_simple_mode_is_used(const char mod);
		void						add_simple_channelmode(const char newMod);
		void						del_simple_usermode(const char oldMod);

		bool						check_if_complexe_mode_is_used(const char mod, const std::string mask);
		void						add_complex_channelmode(const char newMod, const std::string newmask);
		void						del_complex_usermode(const char oldMod, const std::string oldmask);

		bool						check_if_specific_mode_is_used(const char mod);
		void						add_complex_channelmode(const char newMod, const int n);
		void						del_complex_usermode(const char oldMod);
};

#endif