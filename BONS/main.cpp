/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaginot <cmaginot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 17:01:36 by mmercore          #+#    #+#             */
/*   Updated: 2023/05/18 19:55:28 by cmaginot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCL/ft_irc.hpp"
#include "../SRCS/utils.cpp"

static void	print_message_received(const std::string &message)
{
	std::cout << "\033[32m" << message << "\033[0m" << std::endl;
}

static void	print_message_sent(std::string message)
{
	message.erase(message.begin() + message.size() - 1);
	message.erase(message.begin() + message.size() - 1);
	std::cout << "\033[35m" << message << "\033[0m" << std::endl;
}

static void send_message(int &_socket, std::string message)
{
	send(_socket, message.c_str(), message.length() * sizeof(char), MSG_DONTWAIT);
	print_message_sent(message);
}
static int receive(int &_socket, std::string &buffer)
{
	int result = 0;
	char	buffer_c[MAX_LINE_SIZE];
	ft_bzero((void *)buffer_c, (size_t)MAX_LINE_SIZE);

	result = recv(_socket, buffer_c, sizeof(buffer_c) - 5, 0);

	buffer.append(buffer_c);

	return (result);
}

static bool send_pass(int _socket, std::string pass)
{
	std::string message = "PASS ";
	std::string	buffer;

	message.append(pass);
	message.append(" \r\n");

	send_message(_socket, message);

	receive(_socket, buffer);
	print_message_received(buffer);

	if (buffer.find("Password incorrect") != std::string::npos)
		return (false);
	return (true);
}

static bool send_nick(int _socket, std::string nick)
{
	std::string message = "NICK ";
	std::string	buffer;

	message.append(nick);
	message.append(" \r\n");

	send_message(_socket, message);

	receive(_socket, buffer);
	print_message_received(buffer);

	if (buffer.find("Nickname is already in use") != std::string::npos)
		return (false);
	return (true);
}

static void send_user(int _socket, std::string nick)
{
	std::string message = "USER ";
	std::string	buffer;

	message.append(nick);
	message.append(" ");
	message.append(nick);
	message.append(" ");
	message.append("localhost");
	message.append(" :Bot \r\n");

	send_message(_socket, message);
	receive(_socket, buffer);
	print_message_received(buffer);
}

static bool send_oper(int _socket, std::string oper_id, std::string oper_pass)
{
	std::string message = "OPER ";
	std::string	buffer;

	message.append(oper_id);
	message.append(" ");
	message.append(oper_pass);
	message.append(" \r\n");

	send_message(_socket, message);

	while (receive(_socket, buffer) != 0)
	{
		if (buffer.find("Not enough parameters") != std::string::npos)
		{
			print_message_received(buffer);
			return (false);
		}
		if (buffer.find("Password incorrect") != std::string::npos)
		{
			print_message_received(buffer);
			return (false);
		}
		if (buffer.find("You are now an IRC operator") != std::string::npos)
		{
			print_message_received(buffer);
			return (true);
		}
	}
	print_message_received(buffer);
	return (true);
}

static bool send_join(int _socket, std::string chan_name)
{
	std::string message = "JOIN ";
	std::string	buffer;

	message.append(chan_name);
	message.append(" \r\n");

	send_message(_socket, message);

	while (receive(_socket, buffer) != 0);

	// check if bot is operator
	return (true);
}

static void send_topic(int _socket, std::string chan_name, std::string topic)
{
	std::string message = "TOPIC  ";
	std::string	buffer;

	message.append(chan_name);
	message.append(" :");
	message.append(topic);
	message.append(" \r\n");

	send_message(_socket, message);

	while (receive(_socket, buffer) != 0);
}

static void send_wallops(int _socket, std::string wallop, std::string user)
{
	std::string message = "WALLOPS ";
	std::string	buffer;

	message.append(user);
	message.append(" :"); // maybe change ':' by something else
	message.append(wallop);
	message.append(" \r\n");

	send_message(_socket, message);
}

static void send_privmsg_to_chan(int _socket, std::string chan_name, std::string msg)
{
	std::string message = "PRIVMSG ";
	std::string	buffer;

	message.append(chan_name);
	message.append(" :");
	message.append(msg);
	message.append(" \r\n");

	send_message(_socket, message);
}

static void create_message_for_bot_uppercase(int _socket, std::string buffer_after_dd)
{
	std::string message = buffer_after_dd;
	for (std::string::iterator it = message.begin(); it != message.end(); it++)
		*it = toupper(*it);

	send_privmsg_to_chan(_socket, "#bot_uppercase", message);
}

static void create_message_for_bot_lowercase(int _socket, std::string buffer_after_dd)
{
	std::string message = buffer_after_dd;
	for (std::string::iterator it = message.begin(); it != message.end(); it++)
		*it = tolower(*it);

	send_privmsg_to_chan(_socket, "#bot_lowercase", message);
}

static void manage_primsg_received(int _socket, std::string buffer_before_dd, std::string buffer_after_dd)
{
	if (buffer_before_dd.find("PRIVMSG") != std::string::npos) // && buffer_before_dd.find(nick) == std::string::npos)
	{
		if (buffer_before_dd.find("#bot_uppercase") != std::string::npos)
			create_message_for_bot_uppercase(_socket, buffer_after_dd);
		else if (buffer_before_dd.find("#bot_lowercase") != std::string::npos)
			create_message_for_bot_lowercase(_socket, buffer_after_dd);
	}
}

static void manage_notice_received(int _socket, std::string buffer_before_dd, std::string buffer_after_dd)
{
	if (buffer_before_dd.find("NOTICE") != std::string::npos)
	{
		std::string user_nickname;
		user_nickname = buffer_before_dd.substr(buffer_before_dd.find("NOTICE") + 1);

		send_wallops(_socket, buffer_after_dd, user_nickname);
	}
}

int main(int ac, char **av)
{
	int			port;
	std::string	buffer;
	std::string	nick = "bot";
	std::string	pass = "abc";
	std::string	oper_id = "admin";
	std::string	oper_pass = "admin";
	t_sock_conf	sock_conf;
	int			_socket;
	ssocki		connect_conf;

	port = DEFAULT_PORT;
	if (ac == 1)
	{
		PRERR "WRONG NUMBER OF ARGUMENTS" ENDL;
		return (0);
	}
	if (ac > 1) // if connection pass set
		nick = av[1];
	if (ac > 2) // if port set
	{
		std::string s_port = av[2];
		std::stringstream strstr;
		strstr << s_port;
		strstr >> port;	
	}
	if (ac > 3) // if connection pass set
		pass = av[3];
	if (ac > 4) // if oper id set
		oper_id = av[5];
	if (ac > 5) // if oper pass set
		oper_pass = av[5];
	if (ac > 6)
	{
		PRERR "WRONG NUMBER OF ARGUMENTS" ENDL;
		return (0);
	}
	
	
	sock_conf = DEFAULT_SC;
	_socket = socket(sock_conf.domain, sock_conf.type, sock_conf.protocol);
	if (_socket < 0)
	{
		PRERR "SYSCALL TO MAKE SOCKET FAILED" ENDL;
		return (0);
	}

	connect_conf.sin_family = AF_INET;
	connect_conf.sin_addr.s_addr = INADDR_ANY;
	connect_conf.sin_port = htons(port);
	if (connect(_socket, (ssock *)&(connect_conf), sizeof(connect_conf)) < 0)
	{
		PRERR "CONNECT FAIL" ENDL;
		return (0);
	}

	if (send_pass(_socket, pass) == false)
	{
		PRERR "WRONG PASS" ENDL;
		return (0);
	}

	if (send_nick(_socket, nick) == false)
	{
		PRERR "NICK ALREADY USED" ENDL;
		return (0);
	}

	send_user(_socket, nick);

	if (send_oper(_socket, oper_id, oper_pass) == false)
	{
		PRERR "WRONG OPER ID/PASS" ENDL;
		return (0);
	}

	if (send_join(_socket, "#bot_uppercase") == false)
	{
		PRERR "CANNOT CREATE #bot_uppercase CHANNEL" ENDL;
		return (0);
	}

	if (send_join(_socket, "#bot_lowercase") == false)
	{
		PRERR "CANNOT CREATE #bot_lowercase CHANNEL" ENDL;
		return (0);
	}

	send_topic(_socket, "#bot_uppercase", "channel qui va vous envoyer votre message en majuscule dans le channel");
	send_topic(_socket, "#bot_lowercase", "channel qui va vous envoyer votre message en minuscule dans le channel");
	send_wallops(_socket, "I'm on the server", nick);
	send_wallops(_socket, "you can join #bot_uppercase to put your message in uppercase", nick);
	send_wallops(_socket, "you can join #bot_lowercase to put your message in lowecase", nick);
	send_wallops(_socket, "you can send me a NOTICE, i'll put it in WALLOPS message", nick);

	while(1)
	{
		std::string buffer_before_dd = "";
		std::string buffer_after_dd = "";

		receive(_socket, buffer);

		buffer_before_dd = buffer.substr(0, buffer.find(':'));
		buffer_after_dd = buffer.substr(buffer.find(':') + 1);

		manage_primsg_received(_socket, buffer_before_dd, buffer_after_dd);
		manage_notice_received(_socket, buffer_before_dd, buffer_after_dd);
	}

	close(_socket);
	return (0);
}