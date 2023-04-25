/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmercore <mmercore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 17:01:36 by mmercore          #+#    #+#             */
/*   Updated: 2023/04/25 19:26:42 by mmercore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCL/ft_irc.hpp"

int main(int ac, char **av)
{
	int port;

	port = DEFAULT_PORT;
	if (ac > 1)
	{
		std::string s_port = av[1];
		std::stringstream strstr;
		strstr << s_port;
		strstr >> port;	
	}
	
	t_sock_conf sock_conf;
	int _socket;
	ssocki connect_conf;
	
	sock_conf = DEFAULT_SC;
	_socket  = socket(sock_conf.domain, sock_conf.type, sock_conf.protocol);
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
	send(_socket, "CAP LS \n\r", sizeof(char)*9, MSG_DONTWAIT);
	send(_socket, "PASS abc \n\r", sizeof(char)*11, MSG_DONTWAIT);
//	send(_socket, DEFAULT_PWD, sizeof(DEFAULT_PWD), MSG_DONTWAIT);
//	send(_socket, " \n\r", sizeof(char)*3, MSG_DONTWAIT);
	send(_socket, "NICK COUCOUBOT \n\r", sizeof(char)*17, MSG_DONTWAIT);
	send(_socket, "USER coucoubot coucoubot coucouhost :Coucou Bot \n\r", sizeof(char)*50, MSG_DONTWAIT);

	send(_socket, "OPER admin admin \n\r", sizeof(char)*19, MSG_DONTWAIT);
	send(_socket, "JOIN bot_wisdom \n\r", sizeof(char)*19, MSG_DONTWAIT);

	while(1);
	close(_socket);
	return (0);
}