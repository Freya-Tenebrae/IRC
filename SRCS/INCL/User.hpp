/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmercore <mmercore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 12:46:03 by plam              #+#    #+#             */
/*   Updated: 2023/04/24 17:29:52 by mmercore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __USER_HPP__
# define __USER_HPP__

# include <iostream>
# include <vector>
# include <fcntl.h>

#define USR_STAT_BAN -2
#define USR_STAT_REGISTERED 1
#define USR_STAT_AWAY 2
#define USER_MODE_AVAILABLE "iws"

class User
{
	private:
		User();
		User(const User &other);		//copy member function
		User				&operator=(const User &other);
		int					_kicked;

	protected:
		int					_fd;		// fd of the User
		int					_status;	// User's status
		bool				_connected; // if user give the password
		std::string			_usermode;
		std::string			_nickname;
		std::string			_username;
		std::string			_realname;
		std::string			_hostname;
		std::string			_hostaddr;
		std::string			_status_message;
		std::string			_ping_pong_token;
		int					_deltaTimePing;
		int					_lastTimePing;

	public:
		User(const int fd);
		virtual ~User();

		//setter member functions
		void				set_status(const int newStatus);
		void				set_connected();
		void				set_disconnected();
		void				set_nickname(const std::string newNick);
		void				set_username(const std::string newUser);
		void				set_realname(const std::string newReal);
		void				set_hostname(const std::string newHost);
		void				set_hostaddr(const std::string newAddr);
		void				set_status_message(const std::string newStat_message);
		void				set_ping_pong_token(const std::string newPing_pong_token);
		void				set_deltaTimePing(const int newDeltaTimePing);
		void				set_lastTimePing(const int newLastTimePing);
		void				set_kicked(int val);


		//getter member functions
		const int			&get_fd() const;
		const int			&get_status() const;
		const bool			&get_connected() const;
		const std::string	&get_nickname() const;
		const std::string	&get_username() const;
		const std::string	&get_realname() const;
		const std::string	&get_hostname() const;
		const std::string	&get_hostaddr() const;
		const std::string	&get_usermode() const;
		const std::string	&get_status_message() const;
		const std::string	&get_ping_pong_token() const;
		const int			&get_deltaTimePing() const;
		const int			&get_lastTimePing() const;
		int					get_kicked() const;


		bool				check_if_mode_is_used(const char mod);
		void				add_usermode(const char newMod);
		void				del_usermode(const char oldMod);
};

std::ostream				&operator<<(std::ostream &ost, const User &other);

#endif
