/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Reply.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaginot <cmaginot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 17:31:59 by cmaginot          #+#    #+#             */
/*   Updated: 2023/04/21 20:09:53 by cmaginot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCL/Reply.hpp"

Reply::Reply() : _value(0), _message("")
{

}

Reply::Reply(int value, std::string message) : _value(value), _message(message)
{
	_user = NULL;
}

void	Reply::add_loop(std::string loop, int pos)
{
	if (pos == -1)
		_message.insert(_message.length() - 1, loop);
	else if (pos > 0 && pos < static_cast<int>(_message.length()))
		_message.insert(pos, loop);
}

void	Reply::add_arg(std::string arg, std::string to_replace)
{
	std::size_t found, size;
	std::string balise = "<";
	balise.append(to_replace);
	balise.append(">");
	size = balise.length();

	if (_message.compare("") != 0)
	{
		found = _message.find(balise);
		if (found != std::string::npos)
		{
			_message.replace(found, size, arg);
		}
	}
}

void	Reply::add_arg_alt(std::string arg, std::string to_replace)
{
	std::size_t found, size;
	std::string balise = "[";
	balise.append(to_replace);
	balise.append("]");
	size = balise.length();

	if (_message.compare("") != 0)
	{
		found = _message.find(balise);
		if (found != std::string::npos)
		{
			_message.replace(found, size, arg);
		}
	}
}

void	Reply::add_user(User *user)
{
	std::size_t found, size = 8;

	_user = user;
	if (_message.compare("") != 0)
	{
		found = _message.find("<client>");
		if (found != std::string::npos)
		{
			if (_user->get_nickname().compare("") != 0)
				_message.replace(found,size,_user->get_nickname());
			else
			{
				_message.replace(found,size,"Unknow_user");
			}
		}
	}
}


Reply::Reply(const Reply &other)
{
	*this = other;
}

Reply::~Reply() { }

Reply		&Reply::operator=(const Reply &other)
{
	if (this != &other) {
		_value = other.get_value();
		_message = other.get_message();
	}
	return (*this);
}

int			Reply::get_value() const
{
	return (_value);
}

std::string	Reply::get_message() const
{
	return (_message);
}

void	Reply::prep_to_send(int mode)
{
	std::stringstream s_value;
	s_value << _value;
	std::string value_str = s_value.str();

	if (mode > 0)
	{
		if (_value != 0)
		{
			_message.insert(0, " ");
			_message.insert(0, value_str);
		}
		if (_user != NULL)
		{
			_message.insert(0, " ");
			_message.insert(0, _user->get_hostaddr());
			_message.insert(0, "@");
			_message.insert(0, _user->get_username());
			_message.insert(0, "!");
			_message.insert(0, _user->get_nickname());
			_message.insert(0, ":");
		}
	}
	for (std::string::iterator it = _message.begin(); it != _message.end(); it++)
	{
		if (*it == '[' || *it == ']')
		{
			it = _message.erase(it);
		}
	}
}
