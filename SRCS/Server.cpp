/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmercore <mmercore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 17:38:53 by mmercore          #+#    #+#             */
/*   Updated: 2023/05/19 13:48:01 by mmercore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCL/ft_irc.hpp"
#include <string.h>

Server::Server(int port, str password, t_sock_conf sock_conf):_password(password), _port(port)
{
	this->errval = nothing;
	this->_name = "ft_irc";
	this->_version = VERSION;
	this->_oper_id = DEFAULT_OPER_ID;
	this->_oper_password = DEFAULT_OPER_PWD;
	this->_socketfd = 0;
	this->_modt.push_back("⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⣿⣿⣿⣿⡿⣿⣻⡿⣿⡿⣿⣟⢿⡛⡗⡿⣿⣿⣿⣿⣿");
	this->_modt.push_back("⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⡿⣽⢾⢽⣳⢯⢿⢽⢯⢷⣳⣟⡷⡛⢕⢎⡪⡪⢎⢯⢿⣿⣿⣿⣿");
	this->_modt.push_back("⣿⣿⣿⣿⢿⢿⡿⣿⣻⣟⣯⢯⢿⢽⡽⡯⣯⢿⢽⢯⢿⣽⣳⣗⣟⡷⣝⢜⡘⣜⢜⢼⢽⣿⣿⣿⣿");
	this->_modt.push_back("⣿⣿⡓⡯⡍⡇⡏⠮⣸⢨⢪⡿⡽⣯⢯⡿⣽⡽⣯⡿⣟⡾⣞⡷⡯⣯⢯⡷⡩⡒⡝⣮⣿⣿⣿⣿⣿");
	this->_modt.push_back("⣿⣿⣞⢜⢌⢖⢜⢝⢜⢼⢽⣞⣯⢯⡯⣯⢷⣻⣳⣟⣽⢽⢯⢯⢿⢽⢽⣽⣳⢧⣳⣷⣿⣿⣿⣿⣿");
	this->_modt.push_back("⣿⣿⣷⡝⡎⡎⣕⢅⢧⢿⡽⣞⡾⢯⣟⣽⢽⡳⡏⡾⡱⢷⣧⡛⣬⣭⣷⣵⣫⢟⣞⣿⣿⣿⣿⣿⣿");
	this->_modt.push_back("⣿⣿⣿⣿⢵⡹⡢⣃⣯⢯⡯⣷⢋⣟⠮⣞⣏⣪⣗⢕⢱⣫⣾⣇⠈⣿⣿⣿⣿⣿⢵⡫⣟⣿⣿⣿⣿");
	this->_modt.push_back("⣿⣿⣿⣿⣿⡽⣞⣦⢯⡯⣯⢣⣪⡆⠙⣿⣿⣿⣿⣷⣟⣿⣿⣿⡄⢸⣿⣿⣿⡿⡙⢷⢮⣎⣻⣿⣿");
	this->_modt.push_back("⣿⣿⣿⣿⡿⡽⡋⡢⡿⣽⢣⢱⣿⣷⠀⠘⣿⣿⣿⣿⡿⣾⣟⡿⣿⣼⢿⣟⣿⠰⡑⡍⢯⢿⣿⣿⣿");
	this->_modt.push_back("⣿⣿⣿⣿⣹⣼⡧⡱⡿⡝⢔⢹⣿⣿⣧⡀⣿⣿⡿⣻⣾⣿⣽⣟⣿⣺⣿⣽⡏⢎⣬⡊⡆⡻⣿⣿⣿");
	this->_modt.push_back("⣿⣿⣿⣿⣿⣿⣇⣾⣯⣮⣼⣐⢍⢻⢻⣷⣽⣷⣟⢿⣻⣾⣺⣽⣯⣾⢿⢞⢜⠔⢼⣿⣷⣮⣿⣿⣿");
	this->_modt.push_back("⣿⣿⣿⣿⣿⢿⣽⡷⣿⢾⣻⣿⢷⡡⡣⢫⢳⢿⣽⡿⣷⣟⣯⣿⡾⣻⡑⢽⣷⣧⣹⣿⣿⣿⣿⣿⣿");
	this->_modt.push_back("⣿⣿⣿⣿⣟⣿⣽⢿⣻⣿⣻⣽⣿⡇⢎⣮⡢⡣⡩⡝⣝⣭⣹⣲⣮⣿⣟⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿");
	this->_modt.push_back("⣿⣿⣿⣿⣚⣿⣽⣿⣻⣽⣿⣽⡾⣝⢶⣧⣻⣿⣿⣷⣿⣿⣟⣯⣿⣿⣽⣿⣷⣿⣿⣿⣿⣿⣿⣿⣿");
	this->_modt.push_back("⣿⣿⣿⣿⣷⣎⡕⡟⢯⢻⢺⢓⢝⢝⢼⣿⣷⣿⡷⣿⣿⣿⣿⣿⣿⣿⣷⡹⡝⣟⣿⣾⣿⣿⣿⣿⣿");
	this->_modt.push_back("⣿⣿⣿⣿⣿⣿⣿⣾⣾⣾⣾⣗⢵⢱⢿⢿⢟⢯⣚⣿⣿⣿⣿⣿⣿⣿⣿⢪⣾⢿⣿⢯⣿⣿⣿⣿⣿");
	this->_modt.push_back("⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣷⣿⣿⡪⡲⡵⣿⣿⣿⣿⣿⣿⣿⡽⣟⣿⣷⣻⣿⣿⣿⣿⣿");
	this->_modt.push_back("⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠫⣇⢯⣻⣿⣿⣿⣿⣿⣿⠛⣿⣯⢿⣻⣿⣿⣿⣿⣿");
	this->_modt.push_back("⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⢿⡻⡐⠅⠀⠄⠄⢄⠡⢉⠛⡛⢋⢐⢈⢿⣾⢿⣻⣿⣿⣿⣿⣿");
	this->_modt.push_back("⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⢽⢏⢇⣮⠀⠁⠌⠌⡐⠨⢐⠐⡠⢁⠢⢐⢨⣶⣿⣿⣿⣿⣿⣿⣿");
	this->_modt.push_back("⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣯⢯⢫⣾⣿⡇⠀⠨⠨⢐⠠⢑⠐⠨⢐⢐⠨⢐⠸⣿⣿⣿⣿⣿⣿⣿⣿");
	this->_modt.push_back("⣿⣿⣿⣿⣿⣿⣿⣿⣿⢷⢯⣳⣿⣿⡟⠀⢈⠨⠠⠡⠨⢐⠨⠨⢐⠠⠨⢐⠐⣿⣿⣿⣿⣿⣿⣿⣿");
	this->_modt.push_back("⣿⣿⣿⣿⣿⣿⣿⣿⣻⡽⣽⣿⣿⣿⠃⠠⠐⠨⢐⢁⢊⢐⠨⢐⢐⠨⢈⢐⢈⢻⣿⣿⣿⣿⣿⣿⣿");
	this->_modt.push_back("⣿⣯⡿⣿⣿⣿⣿⡽⡗⣽⣿⣿⣿⡟⠀⠠⠨⠨⢐⠠⠂⠔⠨⢐⠠⠨⢐⠐⠠⢺⣿⣿⣿⣿⣿⣿⣿");
	this->_modt.push_back("⣧⢓⢿⣝⣟⡯⡾⣛⣼⣿⣿⣿⣿⣧⡔⠀⠌⡐⡐⠨⢈⠌⡨⢐⠨⢈⢐⠨⢨⣶⣿⣿⣿⣿⣿⣿⣿");
	this->_modt.push_back("⣿⣧⣇⣝⣚⣝⣼⣿⣿⣿⣿⣿⣿⣿⠀⠠⢀⣷⣶⣧⣦⣂⣂⣂⣬⡤⠀⡂⢼⣿⣿⣿⣿⣿⣿⣿⣿");
	this->_modt.push_back("⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡏⠀⠅⢸⣿⣿⣿⣿⣿⣿⣿⣿⡁⢐⠠⢈⠙⠻⣿⣿⣿⣿⣿⣿");
	this->_modt.push_back("⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡟⢁⠨⠐⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣦⣀⠂⠨⠐⡈⢙⢿⣿⣿⣿");
	this->_modt.push_back("⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠏⢀⠂⠄⣡⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣦⣄⠂⠐⡀⠢⣍⠻");
	this->_modt.push_back("⣿⣿⣿⣿⣿⣿⣿⣿⣿⠿⠃⡐⠠⢈⣼⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣦⣀⡁⠄⣂");
	this->_modt.push_back("⣿⣿⣿⣿⣿⣿⣿⠋⠄⢌⠔⡁⢌⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿");
	this->_modt.push_back("⣿⣿⣿⣿⣿⣿⣿⣴⣈⣀⣁⣤⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿");
	this->_modt.push_back("                    NECO_IRC                    ");
	this->_info.push_back("ft_irs is an irc server designed for irssi client");
	this->_info.push_back("it's actual version is 0.3 ans is developped by cmaginot, mmercore, and plam");
	if (MAX_USERS < 1 || MAX_LINE_SIZE < 50 || DEFAULT_TIMEOUT < 500 )
	{
		this->errval = bad_param;
		return ;
	}
	if (port < 0 || port > 65353)
	{
		this->errval = bad_param_port;
		return ;
	}
	if (!password[0])
	{
		this->errval = bad_param_pwd;
		return ;
	}
	set_socketfd(-1 ,sock_conf);
	if (!this->errval && !call_fcntl(get_socketfd(), sock_conf.optname2))
	{
		PRERR "FCNTL HAPPENED AND SUCCESS" ENDL
	}
	if (!this->errval && !set_sockopt(sock_conf.level, sock_conf.optname, (const void *)((unsigned long)&sock_conf + (unsigned long)sock_conf.optval), sock_conf.optlen))
	{
		//this->errval = nothing;
		// Documenter ceci
		this->_address.sin_family = AF_INET;
		// Peut venir de n'importe quelle addresse
		this->_address.sin_addr.s_addr = INADDR_ANY;
		// 
		this->_address.sin_port = htons(get_port());
		PRERR "SETSOCKOPT HAPPENED AND ERRVAL " << this->errval ENDL;
	}
//	if (!this->errval && !call_fcntl(get_socketfd(), sock_conf.optname2))
//	{
//		PRERR "FCNTL HAPPENED AND SUCCESS" ENDL
//	}
	if (!this->errval && !call_bind(get_socketfd(), (ssock *)&(this->_address), sizeof((this->_address))))
	{
		PRERR "BIND SUCCESS" ENDL;
	}
	if (!this->errval && !call_listen(get_socketfd()))
	{
		PRERR "LISTEN SUCCESS" ENDL;
	}
	if (!this->errval)
		PRINT "SERVER SUCCESSFULLY STARTED" ENDL;
}

Server::~Server()
{
	if (this->_socketfd != 0)
		close(_socketfd);
	if (this->errval == 0)
		PRINT "Server closed successfully with no issues" ENDL
	else
		PRINT "Error: Safe close. The errval is " << get_errval(this->errval) << " and the errno is " << strerror(errno) ENDL
	
	if (this->errval == server_restart)
	{
		PRINT "The server will be restarting" ENDL;
	}
	else
	{
		PRINT "The server will not be restarting" ENDL;
	}
}

str			Server::get_errval(t_serv_error errval) const
{
	switch (errval)
	{
		case nothing:		return("nothing");
		case bad_param:		return("bad_param");
		case bad_param_port:return("bad_param_port");
		case bad_param_pwd:	return("bad_param_pwd");
		case syscall_fail:	return("syscall_fail");
		case socket_fail:	return("socket_fail");
		case sock_opt_fail:	return("sock_opt_fail");
		case fcntl_fail:	return("fcntl_fail");
		case bind_fail:		return("bind_fail");
		case listen_fail:	return("listen_fail");
		case poll_fail:		return("poll_fail");
		case timeout:		return("timeout");
		case accept_fail:	return("accept_fail");
		case recv_fail:		return("recv_fail");
		case server_close:	return("server_close");
		case server_restart:return("server_restart");
		case user_close:	return("user_close");

	}
	return ("nothing");
}

str			Server::get_password() const
{
	return	(this->_password);
}


int		Server::get_port() const
{
	return (this->_port);
}

void	Server::set_port(int port)
{
	this->_port = port;	
}

int		Server::get_socketfd() const
{
	return (this->_socketfd);
}

void	Server::set_socketfd(int socketfd, t_sock_conf sock_conf)
{
	this->_socketfd = socketfd;
	if (this->_socketfd < 0)
		this->_socketfd = socket(sock_conf.domain, sock_conf.type, sock_conf.protocol);
	if (this->_socketfd < 0)
	{
		PRERR "SYSCALL TO MAKE SOCKET FAILED" ENDL;
		this->errval = socket_fail;
	}
}

int		Server::set_sockopt(int level, int optname, const void *optval, socklen_t optlen)
{
	if (setsockopt(this->_socketfd, level, optname, optval, optlen) == -1)
	{
		PRERR "FAILED TO SET SOCKET OPTION" ENDL;
		this->errval = sock_opt_fail;
		return (1);	
	}
	return (0);
}

std::string	Server::get_name()
{
	return (_name);
}

void	Server::set_name(std::string name)
{
	_name = name;
}

std::string	Server::get_version()
{
	return (_version);
}

void		Server::set_version(std::string version)
{
	_version = version;
}


int			Server::call_fcntl(int fd, int request)
{
//	int flags;

	//flags = fcntl(fd, F_GETFL, 0);
	//PRERR "Before FCNTL flags are " <<  fcntl(fd, F_GETFL, 0) ENDL;
	//PRERR "We are putting the flag " << request ENDL
	// if (flags == -1 || fcntl(fd, F_SETFL, flags | request) < 0)
	// {
	// 	PRERR "FAILED TO CALL FCNTL" ENDL
	// 	this->errval = fcntl_fail;
	// 	return (1);
	// }
	if (fcntl(fd, F_SETFL, request) < 0)
	{
		PRERR "FAILED TO CALL FCNTL" ENDL
		this->errval = fcntl_fail;
		return (1);
	}
	//PRERR "After FCNTL flags are " <<  fcntl(fd, F_GETFL, 0) ENDL;
	return (0);
}


int		Server::call_bind(int fd, ssock * addrptr, socklen_t addrlen)
{
	int inusewarning;
	long threedots;
	int wait;

	inusewarning = 1;
	threedots = 1;
	//PRINT "ATTEMPTING BIND ON FD " << fd << " AND PORT " << this->get_port() ENDL;
	while (true)
	{
		wait = 0;
		while (wait++ == -1);
		if (bind(fd, addrptr, addrlen) < 0)
		{
			if (errno != EADDRINUSE)
			{
				this->errval = bind_fail;
				return (1);
			}
			if (inusewarning)
			{
				PRERR "EADDRINUSE, RECONECTING..." ENDL;
				inusewarning = 0;
			}
			if (threedots % 10000000 == 0)
			{
				PRERR "..." ENDL;
				if (threedots == 50000000)
					PRERR "Did you know every \"...\" is 10000000 syscalls ?" ENDL;
				if (threedots == 80000000)
					PRERR "In case you are wondering, sleep() or usleep() are not allowed functions" ENDL;
				if (threedots == 140000000)
					PRERR "You don't need to close any netcat or IRSSI connections to restart, they timeout automatically. \n However it is faster to do so !" ENDL;
				if (threedots == 170000000)
					PRERR "Outstanding project pls <3" ENDL;
			}
			threedots++;
		}
		else
		{
			PRERR "SUCCESS BIND" ENDL
			return (0);
		}
	}

}

int		Server::call_listen(int fd, int backlog_hint)
{
	if (listen(fd, backlog_hint) < 0)
	{
		this->errval = listen_fail;
		return(1);
	}
	return (0);
}

int		Server::start()
{
	polling_loop();
	if (this->errval == server_restart)
		return (1);
	return (0);
}

static bool user_is_on_channel(Channel *chan, User *user)
{
	for (std::vector<User *>::const_iterator it = chan->get_ch_usr_list().begin(); it != chan->get_ch_usr_list().end(); it++)
	{
		if (*it == user)
			return (true);
	}
	return (false);
}

int		Server::polling_loop()
{
	// return (0);
	int pol_ret, fd_counter, fd_cursor, new_fd, recv_ret;
	char buffer[MAX_LINE_SIZE];

	fd_counter = 1;		// Attribut public: La classe a t'elle rencontre
		// Un pb ?
	fd_cursor = 0;
	new_fd = -1;
	recv_ret = 1;
	this->fds[0].fd = get_socketfd();
	this->fds[0].events = POLLIN;
	this->fds[0].revents = 0;
	unsigned int fakeaddr = sizeof((this->_address)); 
	(void)fakeaddr;
	pol_ret = 0;
	while(this->errval == 0 || this->errval == user_close)
	{
		PRERR "Polling..." ENDL;
		//PRINT this->_modt ENDL;
		pol_ret = poll(this->fds, fd_counter, DEFAULT_TIMEOUT);

		if (pol_ret < 0)
		{
			PRERR "POLL FAIL" ENDL
			this->errval = poll_fail;
			return (1);
		}
		else if (pol_ret == 0)
		{
			PRERR "TIMEOUT" ENDL;
			this->errval = timeout;
			break;
		}
		else
		{
			fd_cursor = 0;
			while (fd_cursor < fd_counter && this->errval != server_close && this->errval != server_restart)
			{
				if (DEBUG_MODE)
					PRERR "revents for fd " << fd_cursor << " out of " << fd_counter << " is " ENDL
				if (fds[fd_cursor].revents == 0)
				{
					if (DEBUG_MODE)
						PRERR "Doin a skippy on fd " << fd_cursor << " out of " << fd_counter ENDL
					fd_cursor++;
					continue;
				}
				if (fds[fd_cursor].fd == get_socketfd())
				{
					// On verifie si on est prets a accepter une nouvelle connection
					do
					{
						if (fd_counter < MAX_USERS)
						{
							new_fd = accept(get_socketfd(),0 , 0);
						}
						else
						{
							new_fd = accept(get_socketfd(),0 , 0);
							if (new_fd < 0)
							{
								if (errno != EWOULDBLOCK)
									this->errval = accept_fail;
								break;
							}
							send(new_fd, "Server is full.\n", sizeof(char) * 15, MSG_DONTWAIT);
							close(new_fd);
							new_fd = -1;
							break;
						}
						// Errors
						if (new_fd < 0)
						{
							if (errno != EWOULDBLOCK)
								this->errval = accept_fail;
						}
						else
						{
							fds[fd_counter].fd = new_fd;
							fds[fd_counter].events = POLLIN;
							fds[fd_counter].revents = 0;
							PRERR "\033[31mNEW CONNECTION\033[0m" ENDL;
							//send(fds[fd_counter].fd, this->_motd.c_str(), this->motd, 0);
							PRERR "\033[31mNew fd is now \033[0m" << new_fd << ". We are at " << fd_cursor << " Out of " << fd_counter << " total connections. Maximum being " << MAX_LINE_SIZE ENDL

							User	*u = new User(fds[fd_counter].fd);
							u->set_hostname("localhost");
							u->set_hostaddr("127.0.0.1");
							_usr_list.push_back(u);
							this->_buffers[fd_counter].clear();
							fd_counter++;
						}
					}
					while (new_fd != -1);
				}
				else
				{
					recv_ret = 0;
					std::string full_buffer = "";
					do
					{
						for (int i = 0; i < MAX_LINE_SIZE; i++)
							buffer[i] = 0;
						// MSG_DONTWAIT for nonblock sim
						recv_ret = recv(fds[fd_cursor].fd, buffer, sizeof(buffer), MSG_DONTWAIT);
						if (recv_ret <= 0 || find_user(fds[fd_cursor].fd)->get_kicked() == 1 || this->errval != 0)
						{
							// erreurs & close
							if (errno != EWOULDBLOCK || recv_ret == 0 || this->errval == server_close || this->errval == server_restart || this->errval == timeout || (this->errval == user_close && find_user(fds[fd_cursor].fd)->get_kicked() == 1))
							{
								send(fds[fd_cursor].fd, "The server has closed the connection.\n", sizeof(char) * 38, MSG_NOSIGNAL);
								close(fds[fd_cursor].fd);
								//this->errval = recv_fail;
								if (DEBUG_MODE)
									PRERR "ERREURS ET CLOSE" ENDL
								for (std::vector<User *>::iterator it = _usr_list.begin(); it != _usr_list.end(); it++)
								{
									// std::cerr << (*it)->get_fd() << " --- " << fds[fd_cursor].fd << std::endl;
									if ((*it)->get_fd() == fds[fd_cursor].fd)
									{
										User * usr = *it;
										for (std::vector<Channel *>::iterator it = _cha_list.begin(); it != _cha_list.end(); it++)
										{
											if (user_is_on_channel(*it, usr) == true)
												(*it)->del_user(usr);
										}
										_usr_list.erase(it);
										delete usr;
										break;
									}
								}
								if (this->errval == user_close)
								{
									PRERR "Successfully closed user " << fd_cursor << " With fd " << fds[fd_cursor].fd ENDL;
									this->errval = nothing;
								}
								fds[fd_cursor].fd = -1;
								fds[fd_cursor].events = 0;
								// CELIA PAR ICI (cf discord)
								int i = fd_cursor;
								while (i < fd_counter)
								{
									fds[i] = fds[i + 1];
									_buffers[i] = _buffers[i + 1];
									i++;
								}
								_buffers[i].clear();
								fds[i].fd = 0;
								fds[i].events = 0;
								fd_counter--;
								fd_cursor--;

							}
							break;
						}
						else
						{

							//if (errno == EWOULDBLOCK)
							//	PRERR "WOULD BLOCK" ENDL;
							if (DEBUG_MODE)
							{
								PRERR "\033[31mCurrent value of recv_ret\033[0m" << recv_ret ENDL
								PRERR "\033[31mReceived this :" << std::endl;
								PRERR "<<" << buffer << ">>\033[0m" ENDL;	
							}
						}
					} while (compilecommand(buffer, fd_cursor, fds[fd_cursor].fd));
					this->fds[fd_cursor].revents = 0;
				}
				fd_cursor++;
			}
		}
	}
	if (this->errval == server_close || this->errval == server_restart || this->errval == timeout)
	{
		fd_cursor = 1;
		while (fd_cursor < fd_counter)
		{
			send(fds[fd_cursor].fd, "The server has closed the connection.\n", sizeof(char) * 38, 0);
			close(fds[fd_cursor].fd);
			if (DEBUG_MODE)
				PRERR "ERREURS ET CLOSE" ENDL
			for (std::vector<User *>::iterator it = _usr_list.begin(); it != _usr_list.end(); it++)
			{
				// std::cerr << (*it)->get_fd() << " --- " << fds[fd_cursor].fd << std::endl;
				if ((*it)->get_fd() == fds[fd_cursor].fd)
				{
					User * usr = *it;
					_usr_list.erase(it);
					delete usr;
					break;
				}
			}

			fds[fd_cursor].fd = -1;
			fds[fd_cursor].events = 0;
			// CELIA PAR ICI (cf discord)
			int i = fd_cursor;
			while (i < fd_counter)
			{
				fds[i] = fds[i + 1];
				_buffers[i] = _buffers[i + 1];
				i++;
			}
			_buffers[i].clear();
			fds[i].fd = 0;
			fds[i].events = 0;
			fd_counter--;
		}
	}
	for (std::vector<Channel *>::iterator it = _cha_list.begin(); it != _cha_list.end();)
	{
		Channel *chan = *it;
		it++;
		if (chan)
			delete chan;
	}
	return (0);
}

int		Server::compilecommand(char *message, int fd, int realfd)
{
	this->_buffers[fd].append(message);
	if (DEBUG_MODE)
	{
		if (this->_buffers[fd].find("EVACWINCHESTER") != str::npos)
		{
			this->errval = server_restart;
			this->_buffers[fd].clear();
			return (1);
		}
		if (this->_buffers[fd].find("EVACBINGO") != str::npos)
		{
			this->errval = server_close;
			this->_buffers[fd].clear();
			return (1);
		}
		if (this->_buffers[fd].find("CLOSEME") != str::npos)
		{
			find_user(realfd)->set_kicked(1);
			//close(fd);
			this->errval = user_close;
			this->_buffers[fd].clear();
			return (1);
		}	
	}
	if (DEBUG_MODE)
		PRERR "Message current form  " << this->_buffers[fd] ENDL;
	if (this->_buffers[fd].find(CRLF) != str::npos && this->_buffers[fd].find_last_of(CRLF) + sizeof(CRLF) >= this->_buffers[fd].size())
	{
		if (DEBUG_MODE)
			PRERR "Correct message, going for the parse" ENDL;
		run_buffer(realfd, this->_buffers[fd].c_str());
		this->_buffers[fd].clear();
		return (0);
	}
	else
	{
		if (DEBUG_MODE)
			PRERR "Message not ready yet" ENDL;
		return (1);
	}
}

User	*Server::find_user(int fd)
{
	for (std::vector<User *>::iterator it = _usr_list.begin(); it != _usr_list.end(); it++)
	{
		if ((*it)->get_fd() == fd)
			return (*it);
	}
	return (NULL);
}

User	*Server::find_user_by_nickname(std::string nickname)
{
	for (std::vector<User *>::iterator it = _usr_list.begin(); it != _usr_list.end(); it++)
	{
		if ((*it)->get_nickname().compare(nickname) == 0)
			return (*it);
	}
	return (NULL);
}

Channel	*Server::find_channel(std::string channel_name)
{
	for (std::vector<Channel *>::iterator it = _cha_list.begin(); it != _cha_list.end(); it++)
	{
		if ((*it)->get_name().compare(channel_name) == 0)
			return (*it);
	}
	return (NULL);
}

void	Server::run_buffer(int fd, std::string buffer)
{
	User *user = find_user(fd);
	if (user == NULL)
		return ;
	std::vector<std::string>	line = pars_buffer(buffer);
	for (std::vector<std::string>::iterator it = line.begin(); it != line.end(); it++)
	{
		if (it->compare("") != 0)
		{
			std::cout << "\033[1;32m" << user->get_fd() << " <- \033[1;36m|\033[0m" << *it << "\033[1;36m|\033[0m" << std::endl;
			// push all rpls on file named log instead of cout
		}
	}
	for (std::vector<std::string>::iterator it = line.begin(); it != line.end(); it++)
	{
		if (it->compare("") != 0)
			run_line(user, *it);
	}
}

std::vector<std::string>	Server::pars_buffer(std::string &buffer)
{
	size_t						pos;
	std::string					line;
	std::vector<std::string>	lines;
	while (buffer.length() != 0)
	{
		pos = buffer.find('\n');
		if (pos == std::string::npos)
		{
			line = buffer.substr(0, buffer.length());
			buffer.erase(buffer.begin(), buffer.end());
		}
		else
		{
			line = buffer.substr(0, pos - 1); // -1 for last char
			buffer.erase(buffer.begin(), buffer.begin() + pos + 1);
		}
		lines.push_back(line);
	}
	return lines;
}

void	Server::run_line(User *user, std::string &line)
{
	std::vector<std::string>	args = pars_line(line);
	std::string					cmd = args[0];

	args.erase(args.begin());
	std::vector<Reply>			rpls = command(user, cmd, args);
	for (std::vector<Reply>::iterator it = rpls.begin(); it != rpls.end(); it++)
		send_message(user, it->get_message());
}

std::vector<std::string>	Server::pars_line(std::string &line)
{
	size_t						pos;
	std::string					word;
	std::vector<std::string>	args;
	while (line.length() != 0)
	{
		pos = line.find(' ');
		if (pos == std::string::npos)
		{
			word = line;
			line.erase(line.begin(), line.end());
		}
		else
		{
			word = line.substr(0, pos);
			line.erase(line.begin(), line.begin() + pos + 1);
		}
		args.push_back(word);
	}
	return args;
}

void	Server::send_message(User *user, std::string message)
{
	if (message.compare("") != 0)
	{
		send(user->get_fd(), message.c_str(), message.length(), MSG_NOSIGNAL);
		message.erase(message.begin() + message.size() - 1);
		std::cout << "\033[1;35m" << user->get_fd() << " -> \033[1;36m|\033[0m";
		std::cout << message << "\033[1;36m|\033[0m" << std::endl;
		// push all rpls on file named log instead of cout
	}
}

std::vector<Reply>	Server::command(User *user, std::string commandName, std::vector<std::string> args)
{
	t_command	t[] =
	{
		{"CAP", &Server::cap},
		{"PASS", &Server::pass},
		{"NICK", &Server::nick},
		{"USER", &Server::user},
		{"PING", &Server::ping},
		{"PONG", &Server::pong},
		{"OPER", &Server::oper},
		{"QUIT", &Server::quit},
		{"JOIN", &Server::join},
		{"PART", &Server::part},
		{"TOPIC", &Server::topic},
		{"NAMES", &Server::names},
		{"INVITE", &Server::invite},
		{"KICK", &Server::kick},
		{"MOTD", &Server::motd},
		{"VERSION", &Server::version},
		{"ADMIN", &Server::admin},
		{"CONNECT", &Server::connect},
		{"LUSERS", &Server::lusers},
		{"TIME", &Server::time},
		{"STATS", &Server::stats},
		{"HELP", &Server::help},
		{"INFO", &Server::info},
		{"MODE", &Server::mode},
		{"PRIVMSG", &Server::privmsg},
		{"NOTICE", &Server::notice},
		{"WHO", &Server::who},
		{"WHOIS", &Server::whois},
		{"WHOWAS", &Server::whowas},
		{"KILL", &Server::kill},
		{"REHASH", &Server::rehash},
		{"RESTART", &Server::restart},
		{"SQUIT", &Server::close_server},
		{"AWAY", &Server::away},
		{"LINKS", &Server::links},
		{"USERHOST", &Server::userhost},
		{"WALLOPS", &Server::wallops},
		{"CLOSE", &Server::close_server}
	};
	for (std::string::iterator it = commandName.begin(); it != commandName.end(); it++)
	{
		if (*it <= 'z' && *it >= 'a')
			*it += 'A' - 'a';
	}

	for (int i = 0; i < 39; i++)
	{
		if (t[i].commandName == commandName)
			return (this->*t[i].commands) (user, args);
	}
	std::vector<Reply>	reply;
	reply.push_back(ERR_UNKNOWNCOMMAND);
	reply[0].add_user(user);
	reply[0].add_arg(commandName, "command");
	reply[0].prep_to_send(1);
	return (reply);
}