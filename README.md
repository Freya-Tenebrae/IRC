# ft_irc

This Repositorie contains my solution to the project `ft_irc` of 42 (Paris).

[![cmaginot's 42 stats](https://badge42.vercel.app/api/v2/cl1s5sord008509mlo7xr33zy/stats?cursusId=21&coalitionId=45)](https://github.com/JaeSeoKim/badge42)

[![cmaginot's 42 cub3d Score](https://badge42.vercel.app/api/v2/cl1s5sord008509mlo7xr33zy/project/2580204)](https://github.com/JaeSeoKim/badge42)

## Description

...

## Cloning

```shell
git clone --recurse-submodules https://github.com/Freya-Tenebrae/ft_irc.git
```

## Compilation

```shell
make
```

## Launch

```shell

```

## Documentation

> https://www.rfc-editor.org/rfc/rfc1459

> https://www.rfc-editor.org/rfc/rfc2810

> https://www.rfc-editor.org/rfc/rfc2812

> https://www.rfc-editor.org/rfc/rfc2813

> https://www.rfc-editor.org/rfc/rfc2811

> https://www.rfc-editor.org/rfc/rfc7194

## TODO

### server.cpp :
- ajouter les ping a intervale reguliser sur tous les utilisateurs
- check au bout d'un certain temps si tous les user ont eu un pong de reponse, deconnecter ceux qui ont depasser le temps
- ajouter un vercteur de pointeur de channel

- autre fix a faire / fonctionnalites a add ?

- check si il n'y a aucun leak

### channel :
- a implementer

### commandes :
#### que l'on peut faire maintenant :
- finir ping.cpp (au niveau du pong reply)
- finir pong.cpp (et mettre a jour les donnees)

#### complexe :
- faire quit.cpp
- faire kill.cpp
- faire restart.cpp (voir a faire des modif sur la classe server.cpp)

#### commandes avec channel :
- faire invite.cpp (une fois la classe channel.cpp finie)
- faire join.cpp (une fois la classe channel.cpp finie)
- faire kick.cpp (une fois la classe channel.cpp finie)
- faire list.cpp (une fois la classe channel.cpp finie)
- faire names.cpp (une fois la classe channel.cpp finie)
- faire part.cpp (une fois la classe channel.cpp finie)
- faire topic.cpp (une fois le lien delete sur server.cpp)
- faire privmsg.cpp (une fois la classe channel.cpp finie)
- faire notice.cpp (une fois la classe channel.cpp finie) (une fois privmsg.cpp fini)
- finir mode.cpp pour les channel (une fois la classe channel.cpp finie)
