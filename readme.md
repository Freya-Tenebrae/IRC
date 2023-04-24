# chose a check :
- join after an invite
- faire des test sur pirvmsg (apres avoir join pour un channel, et avec /MSG pour les mp (et /windows 1/2/3 pour changer entre les channel)) normalement ca marche

# choses a faire obligatoire:
## organisation :
- déplacer des fonction static des commande en util.cpp (et les supprimer)

## commandes :
- faire RPL_AWAY sur client et privmsg
- revoir tous les Reply sur privmsg
- faire notice.cpp
- faire kill.cpp
- faire restart.cpp (voir a faire des modif sur la classe server.cpp)
- faire invite.cpp
- faire kick.cpp
- finir mode.cpp (pour les channel)

# chose a faire en option :
## server.cpp :
- ajouter les ping a intervale reguliser sur tous les utilisateurs
- check au bout d'un certain temps si tous les user ont eu un pong de reponse, deconnecter ceux qui ont depasser le temps

## commandes :
- fix ping.cpp (au niveau du pong reply) (derniers details) // option
- fix pong.cpp (et mettre a jour les donnees) (derniers details)

## commandes avec channel :
- faire list.cpp
- faire topic.cpp
- faire names.cpp
- faire part.cpp

# autres
- check a faire une commande ban ?