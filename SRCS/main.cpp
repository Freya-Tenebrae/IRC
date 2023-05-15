/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaginot <cmaginot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 18:26:22 by mmercore          #+#    #+#             */
/*   Updated: 2023/05/09 15:50:51 by cmaginot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCL/ft_irc.hpp"

/* poll() reference source : http://manpagesfr.free.fr/man/man2/poll.2.html */

#include <string.h>

// Server side C/C++ program to demonstrate Socket
// programming
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#define PORT 8080

int	main(int ac, char **av, char **envp) {
	(void)ac, (void)av, (void)envp;
	int restart;
	int port;

	port = 0;
	restart = 1;
	if (ac > 1)
	{
		std::string s_port = av[1];
		std::stringstream strstr;
		strstr << s_port;
		strstr >> port;	
	}
	while (restart)
	{
		if (ac == 1)
		{
			Server a;
			restart = a.start();
		}
		if (ac == 2)
		{
			Server a(port);
			restart = a.start();
		}
		if (ac == 3)
		{
			Server a(port, av[2]);
			restart = a.start();
		}		
	}
	return (0);
}