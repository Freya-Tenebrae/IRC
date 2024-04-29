# ft_irc

Ce repository contiens ma solution au projet `ft_irc` de 42.

Il à été réaliser avec [Maximilien Mercorelli](https://github.com/mmercore) et [Pierre Marie Lam](https://github.com/Askeladd42)

This repository contains my solution to the project `ft_irc` of 42.

It was made with [Maximilien Mercorelli](https://github.com/mmercore) and [Pierre Marie Lam](https://github.com/Askeladd42)

## Description 

Ce projet a pour but de reproduire un serveur IRC (Internet Relay Chat) compatible avec un client de notre choix ([IRSSI](https://irssi.org/))

This project aims to create an IRC server (Internet Relay Chat) compatible with a client of our choice ([IRSSI](https://irssi.org/))

## Using ft_irc

### Cloning

```shell
git clone https://github.com/Freya-Tenebrae/ft_irc.git
```

### Compilation

```
make
```

### Using

```
./ft_irc <port> <password>
# for example `./ft_irc 32001 Pass`
```

Puis en se connectant via [IRSSI](https://irssi.org/) ou NC (netcat)

Then by connecting with [IRSSI](https://irssi.org/) or NC (netcat)

## Bonus part : a bot

Un bot rudimentaire a également été créer pour se connecter a ce serveur IRC.

A rudimentary bot was also created to connect to this IRC server.

### compilation

```
make bonus
```

### Using

```
./bot <bot_name> <port> <password> <id admin> <password admin>
```
