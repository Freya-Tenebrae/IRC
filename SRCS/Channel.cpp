/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaginot <cmaginot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 16:37:57 by plam              #+#    #+#             */
/*   Updated: 2023/04/25 21:08:28 by cmaginot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCL/Channel.hpp"

Channel::Channel():_name(""), _number_max_user(-1)
{
	// do not use this;
}

Channel::Channel(std::string	name):_name(name), _number_max_user(-1)
{

}

Channel::Channel(const Channel &other)
{
	*this = other;
	// do not use this;
}

Channel::~Channel()
{

}

Channel	&Channel::operator=(const Channel &other)
{
	this->_name = other.get_name();
	this->_number_max_user = other.get_number_max_user();

	std::vector<User *> tmp_usr_list = other.get_ch_usr_list();
	for (std::vector<User *>::const_iterator it = tmp_usr_list.begin(); it != tmp_usr_list.end(); it++)
	{
		this->_ch_usr_list.push_back(*it);
	}

	std::multimap<char, std::string> tmp_channelmode = other.get_channelmode();
	for (std::multimap<char, std::string>::const_iterator it = tmp_channelmode.begin(); it != tmp_channelmode.end(); it++)
	{
		this->_channelmode.insert(std::pair<char, std::string>(it->first, it->second));
	}
	this->_topic = other._topic;
	return *this;
}

const std::string	&Channel::get_name() const
{
	return (_name);
}

const int	&Channel::get_number_max_user() const
{
	return (_number_max_user);
}

int	Channel::get_number_act_user() const
{
	return (_ch_usr_list.size());
}

const std::vector<User *>	&Channel::get_ch_usr_list() const
{
	return (_ch_usr_list);
}

const User	*Channel::get_User(int fd) const
{
	for (std::vector<User *>::const_iterator it = _ch_usr_list.begin(); it != _ch_usr_list.end(); it++)
	{
		if ((*it)->get_fd() == fd)
			return (*it);
	}
	return (NULL);
}

const std::multimap<char, std::string>	&Channel::get_channelmode() const
{
	return (_channelmode);
}

void	Channel::add_user(User *user)
{
	this->_ch_usr_list.push_back(user);
}

void	Channel::del_user(User *user)
{
	for (std::vector<User *>::iterator it = _ch_usr_list.begin(); it != _ch_usr_list.end(); it++)
	{
		if (*it == user)
		{
			it = _ch_usr_list.erase(it);
			break;
		}
	}
}

bool	Channel::check_if_simple_mode_is_used(const char mod)
{
	for (std::multimap<char, std::string>::iterator it = _channelmode.begin(); it != _channelmode.end(); it++)
	{
		if (it->first == mod)
			return (true);
	}
	return (false);
}

void	Channel::add_simple_channelmode(const char newMod)
{
	this->_channelmode.insert(std::pair<char, std::string>(newMod, ""));
}

void	Channel::del_simple_channelmode(const char oldMod)
{
	for (std::multimap<char, std::string>::iterator it = _channelmode.begin(); it != _channelmode.end(); it++)
	{
		if (it->first == oldMod)
		{
			_channelmode.erase(it);
			break;
		}
	}
}

bool	Channel::check_if_complexe_mode_is_used(const char mod)
{
	for (std::multimap<char, std::string>::iterator it = _channelmode.begin(); it != _channelmode.end(); it++)
	{
		if (it->first == mod)
			return (true);
	}
	return (false);
}

bool	Channel::check_if_complexe_mode_is_correct(const char mod, const std::string mask)
{
	for (std::multimap<char, std::string>::iterator it = _channelmode.begin(); it != _channelmode.end(); it++)
	{
		if (it->first == mod && it->second.compare(mask) == 0)
			return (true);
	}
	return (false);
}

void	Channel::add_complex_channelmode(const char newMod, const std::string newmask)
{
	this->_channelmode.insert(std::pair<char, std::string>(newMod, newmask));
}

void	Channel::del_complex_channelmode(const char oldMod, const std::string oldmask)
{
	for (std::multimap<char, std::string>::iterator it = _channelmode.begin(); it != _channelmode.end(); it++)
	{
		if (it->first == oldMod && it->second.compare(oldmask) == 0)
		{
			_channelmode.erase(it);
			break;
		}
	}
}

bool	Channel::check_if_specific_mode_is_used(const char mod)
{
	if (mod == 'l' && _number_max_user == -1)
		return (false);
	return (true);
}

void	Channel::add_specific_channelmode(const char newMod, const int n)
{
	if (newMod == 'l')
		_number_max_user = n;
}

void	Channel::del_specific_channelmode(const char oldMod)
{
	if (oldMod == 'l')
		_number_max_user = -1;
}


void	Channel::set_topic(std::string newTopic)
{
	this->_topic = newTopic;
}

const std::string	&Channel::get_topic()
{
	return this->_topic;
}
