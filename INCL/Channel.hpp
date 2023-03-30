/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaginot <cmaginot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 12:51:43 by plam              #+#    #+#             */
/*   Updated: 2023/03/30 16:29:44 by cmaginot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __CHANNEL_HPP__
# define __CHANNEL_HPP__
# include "ft_irc.hpp"

#define UNIQUE_CHANNEL_MODE_AVAILABLE "i"
#define MULTIPLE_CHANNEL_MODE_AVAILABLE "b"

class Channel
{
	private:
		std::vector<User *>	_ch_usr_list;

	protected:
		std::string	_name;
		std::multimap<char, std::string>	_channelmode;

	public:
		Channel();
		Channel(const Channel &other);
		~Channel();
		Channel	&operator=(const Channel &other);

		void	add(User &user);
		void	del(User &user);
};

#endif