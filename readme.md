# server.cpp :
- supprimer la commande error sur server.cpp et server.hpp
- ajouter les ping a intervale reguliser sur tous les utilisateurs
- check au bout d'un certain temps si tous les user ont eu un pong de reponse, deconnecter ceux qui ont depasser le temps
- ajouter un vercteur de pointeur de channel
- ???

# channel :
- ???

# commandes :
## que l'on peut faire maintenant :
- fix ping.cpp (au niveau du pong reply) (derniers details)
- fix pong.cpp (et mettre a jour les donnees) (derniers details)

## complexe :
- faire kill.cpp
- faire restart.cpp (voir a faire des modif sur la classe server.cpp)

## commandes avec channel :
- faire invite.cpp (une fois la classe channel.cpp finie)
- faire join.cpp (une fois la classe channel.cpp finie)
- faire kick.cpp (une fois la classe channel.cpp finie)
- faire list.cpp (une fois la classe channel.cpp finie)
- finir mode.cpp pour les channel (une fois la classe channel.cpp finie)
- faire names.cpp (une fois la classe channel.cpp finie)
- faire privmsg.cpp (une fois la classe channel.cpp finie)
- faire notice.cpp (une fois la classe channel.cpp finie) (une fois privmsg.cpp fini)
- faire part.cpp (une fois la classe channel.cpp finie)
- faire topic.cpp (une fois le lien delete sur server.cpp)