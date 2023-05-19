/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmercore <mmercore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 19:46:40 by cmaginot          #+#    #+#             */
/*   Updated: 2023/05/18 19:49:44 by mmercore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __server_HPP__
# define __server_HPP__

# include "ft_irc.hpp"	
// Dans un vrai serveur, ces defines seraient un fichier de configuration.
// Par securite
# define DEFAULT_PORT 8080
# define DEFAULT_PWD "abc"
# define DEFAULT_OPER_ID "admin"
# define DEFAULT_OPER_PWD "admin"
# define DEFAULT_TIMEOUT 5*60*1000 // Expressed in ms, minimum 500
# define MAX_LINE_SIZE 210 // Minimum 50
# define NEW_CONNECTION_MESSAGE "You have connected to FT_IRC\n"
# define VERSION "0.3"
# define CRLF "\r\n"
# define MAX_USERS 5 // The server also counts as a user, minimum 1
# define DEBUG_MODE 0 // If set to 1 activates remote close/restart of the server
// These are a security risk as they bypass Oper
// See Server.cpp 518

// This structure contains the necessary parameters to configure a socket server
// And modify flags
typedef struct	e_sock_conf {
//					socket_params;
	int				domain;
	int				type;
	int				protocol;
//					socket_opts;
	int				level;
	int				optname;
	int				optname2;
	int				optvalobj;
	const void		*optval;
	socklen_t		optlen;
}				t_sock_conf;

// Les differentes erreurs qui pourraient necessiter de fermer des FDs
// Que le serveur gere de maniere safe
// On l'utilise egalement pour connaitre l'etat de fin du programme
// cf main.cpp
typedef enum e_serv_error {
	nothing = 0,
	bad_param,
	bad_param_port,
	bad_param_pwd,
	syscall_fail,
	socket_fail,
	sock_opt_fail,
	fcntl_fail,
	bind_fail,
	listen_fail,
	poll_fail,
	timeout,
	accept_fail,
	recv_fail,
	server_close,
	server_restart,
	user_close
}							t_serv_error;

// 		Domain:
// Pour l'instant AF_LOCAL (alias pour AF_UNIX)
// Pour le vrai projet il faudra passer sur AF_INET (IPV4)
// >man socket
//		Type:
// Pour l'instant SOCK_STREAM
// J'ai pas trop test les autres
//		Protocol:
// Il n'y a qu'un type de protocol pour SOCK_STREAM
// 0 le choisit par defaut

//		Level:
// Specifie comme SOL_SOCKET selon la dock.
// Si on veut set des options pour des protocoles
// En particulier il faudra trouver leur level avec getprotoent
//		Optname:
// On set SO_REUSEADDR et SO_REUSEPORT
// Le premier permet de reutiliser la meme addr/port en cas de pb
// Pourquoi ? Si le pb crashem la socket va rentrer
// Dans un state appele TIME_WAIT ou elle va attendre
// Que tous les packets soient arrives a leur destination,
// Si on relance le programme elle ne sera pas utilisable
// Avec cette option, si. 
// Le deuxieme permet a plusieures socket de bind
// Avec la meme addresse/port
//		Optval:
// Doit etre un pointeur sur un int qui allume ou eteint l'option
//		Optlen:
// La len de ce que pointe opval

//https://www.gta.ufrj.br/ensino/eel878/sockets/sockaddr_inman.html
// Equivalent a struct sockaddr* en cast, supporte plus d'implementations
typedef struct sockaddr_in	ssocki;
typedef struct sockaddr		ssock;
typedef	struct pollfd		spollfd;

// 
# define	DEFAULT_SC	(t_sock_conf){		\
	.domain=AF_INET,						\
	.type=SOCK_STREAM,						\
	.protocol=0,							\
	.level=SOL_SOCKET,						\
	.optname=SO_REUSEADDR | SO_REUSEPORT,	\
	.optname2=O_NONBLOCK,					\
	.optvalobj=1,							\
	.optval=(const void *)(sizeof(t_sock_conf) - sizeof(socklen_t) - sizeof(const void *)),				\
	.optlen=sizeof(int)			\
	}

class Server {
	public:
		// Attribut public: La classe a t'elle rencontre
		// Un pb ?
		t_serv_error	errval;

		Server(int port=DEFAULT_PORT, str password=DEFAULT_PWD, t_sock_conf sock_conf=DEFAULT_SC);
		~Server();

		str			get_errval(t_serv_error errval) const;

		str			get_password() const;
		void		set_password(str password=DEFAULT_PWD);

		int			get_port() const;
		void		set_port(int port=DEFAULT_PORT);
		
		int			get_socketfd() const;
		void		set_socketfd(int socketfd=-1, t_sock_conf sock_conf=DEFAULT_SC);

		std::string	get_name();
		void		set_name(std::string name);

		std::string	get_version();
		void		set_version(std::string version);

		int			set_sockopt(int level, int optname, const void *optval, socklen_t optlen);
		
		int			call_fcntl(int fd, int request);
		
		int			call_bind(int fd, ssock * addrptr, socklen_t addrlen);

		int			call_listen(int fd, int backlog_hint=SOMAXCONN);
		
		int			start();

		int			polling_loop();

		int			compilecommand(char *message, int fd);

		User						*find_user(int fd);
		User						*find_user_by_nickname(std::string nickname);
		Channel						*find_channel(std::string channel_name);
		void						run_buffer(int fd, std::string buffer);
		std::vector<std::string>	pars_buffer(std::string &buffer);
		void						run_line(User *user, std::string &line);
		std::vector<std::string>	pars_line(std::string &line);
		void						send_message(User *user, std::string message);
		std::vector<Reply>			command(User *user, std::string commandName, std::vector<std::string> args);
		

	private:
		std::string					_name;
		std::string					_version;
		std::string					_password;
		std::string					_oper_id;
		std::string					_oper_password;
		int							_port;
		int							_socketfd;
		std::vector<User *>			_usr_list;
		std::vector<Channel *>		_cha_list;
		std::vector<std::string>	_modt;
		std::vector<std::string>	_info;

		bool						is_nickname_valid(std::string nickname);
		bool						is_nickname_free(std::string nickname);
		int							check_number_user_with_specific_mod(char mod);

		std::vector<Reply>			cap(User *user, std::vector<std::string> args);
		std::vector<Reply>			pass(User *user, std::vector<std::string> args);
		std::vector<Reply>			nick(User *user, std::vector<std::string> args);
		std::vector<Reply>			user(User *user, std::vector<std::string> args);
		std::vector<Reply>			ping(User *user, std::vector<std::string> args);
		std::vector<Reply>			pong(User *user, std::vector<std::string> args);
		std::vector<Reply>			oper(User *user, std::vector<std::string> args);
		std::vector<Reply>			quit(User *user, std::vector<std::string> args);
		std::vector<Reply>			join(User *user, std::vector<std::string> args);
		std::vector<Reply>			try_to_join(User *user, std::string channel_name, std::string channel_key);
		std::vector<Reply>			part(User *user, std::vector<std::string> args);
		std::vector<Reply>			topic(User *user, std::vector<std::string> args);
		std::vector<Reply>			names(User *user, std::vector<std::string> args);
		std::vector<Reply>			invite(User *user, std::vector<std::string> args);
		std::vector<Reply>			kick(User *user, std::vector<std::string> args);
		std::vector<Reply>			motd(User *user, std::vector<std::string> args);
		std::vector<Reply>			version(User *user, std::vector<std::string> args);
		std::vector<Reply>			admin(User *user, std::vector<std::string> args);
		std::vector<Reply>			connect(User *user, std::vector<std::string> args);
		std::vector<Reply>			lusers(User *user, std::vector<std::string> args);
		std::vector<Reply>			time(User *user, std::vector<std::string> args);
		std::vector<Reply>			stats(User *user, std::vector<std::string> args);
		std::vector<Reply>			help(User *user, std::vector<std::string> args);
		std::vector<Reply>			info(User *user, std::vector<std::string> args);
		std::vector<Reply>			mode(User *user, std::vector<std::string> args);
		std::vector<Reply>			privmsg(User *user, std::vector<std::string> args);
		std::vector<Reply>			privmsg_channel(User *user, std::vector<std::string> &args, std::string &message);
		std::vector<Reply>			privmsg_user(User *user, User *target, std::string &message);
		std::vector<Reply>			notice(User *user, std::vector<std::string> args);
		void 						notice_channel(User *user, std::vector<std::string> &args, std::string &message);
		void 						notice_user(User *user, User *target, std::string &message);
		std::vector<Reply>			who(User *user, std::vector<std::string> args);
		std::vector<Reply>			whois(User *user, std::vector<std::string> args);
		std::vector<Reply>			whowas(User *user, std::vector<std::string> args);
		std::vector<Reply>			kill(User *user, std::vector<std::string> args);
		std::vector<Reply>			rehash(User *user, std::vector<std::string> args);
		std::vector<Reply>			restart(User *user, std::vector<std::string> args);
		std::vector<Reply>			squit(User *user, std::vector<std::string> args);
		std::vector<Reply>			away(User *user, std::vector<std::string> args);
		std::vector<Reply>			links(User *user, std::vector<std::string> args);
		std::vector<Reply>			userhost(User *user, std::vector<std::string> args);
		std::vector<Reply>			wallops(User *user, std::vector<std::string> args);
		std::vector<Reply>			close_server(User *user, std::vector<std::string> args);


		//https://www.gta.ufrj.br/ensino/eel878/sockets/sockaddr_inman.html
		// Equivalent a struct sockaddr* en cast, supporte plus d'implementations
		ssocki	_address;
		
		// +3 Car le serveur a un fd, les deux autres pour padder des struct vides
		// au debut et a la fin
		spollfd	fds[MAX_USERS + 3];
		str		_buffers[MAX_USERS + 3];
		
};

typedef struct	s_command
{
	std::string	commandName;
	std::vector<Reply>	(Server::*commands)(User *user, std::vector<std::string> args);
}				t_command;

#endif