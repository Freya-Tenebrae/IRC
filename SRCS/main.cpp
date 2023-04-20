/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmercore <mmercore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 18:26:22 by mmercore          #+#    #+#             */
/*   Updated: 2023/04/17 19:33:46 by mmercore         ###   ########.fr       */
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
// int main(int argc, char const* argv[])
// {
// 	(void)argv;
// 	(void)argc;
//     int server_fd, new_socket = 0;
//     struct sockaddr_in address;
//     int opt = 1;
//     str hello = "Hello from server";
 
// 	perror("funni");
//     // Creating socket file descriptor
//     if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
//         perror("socket failed");
//         exit(EXIT_FAILURE);
//     }
 
//     // Forcefully attaching socket to the port 8080
//     if (setsockopt(server_fd, SOL_SOCKET,
//                    SO_REUSEADDR | SO_REUSEPORT, &opt,
//                    sizeof(opt))) {
//         perror("setsockopt");
//         exit(EXIT_FAILURE);
//     }
//     address.sin_family = AF_INET;
//     address.sin_addr.s_addr = INADDR_ANY;
//     address.sin_port = htons(PORT);
 
//     // Forcefully attaching socket to the port 8080
//     if (bind(server_fd, (struct sockaddr*)&address,
//              sizeof(address))
//         < 0) {
//         perror("bind failed");
//         exit(EXIT_FAILURE);
//     }

 
//     // closing the connected socket
//     close(new_socket);
//     // closing the listening socket
//     shutdown(server_fd, SHUT_RDWR);
//     return 0;
// }
#define restart 1

int	main(int ac, char **av, char **envp) {
	(void)ac, (void)av, (void)envp;

	while (restart)
	{
		if (ac == 1)
		{
			Server a;
		}
		if (ac == 2)
		{
			Server a(atoi(av[1]));
		}
		if (ac == 3)
		{
			Server a(atoi(av[1]), av[2]);
		}		
	}

	
	//while(1);
	// struct pollfd	fds[1];
	// fds[0].fd = 0;
	// fds[0].events = POLLIN;

	// Server a;
	// while (true) {
	// 	int	ret = poll(fds, 1, -1);
	// 	if	(ret == -1) {
	// 		std::cerr << "poll() error" << std::endl;
	// 		return 1;
	// 	}
	// 	if (fds[0].revents & POLLIN) {
	// 		char	buf[1024];
	// 		std::cin.getline(buf, sizeof(buf));
	// 		std::cout << "input: " << buf << std::endl;
	// 	}
	// }
	return (0);
}