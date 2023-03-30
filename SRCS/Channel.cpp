/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaginot <cmaginot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 16:37:57 by plam              #+#    #+#             */
/*   Updated: 2023/02/27 19:16:13 by cmaginot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCL/Channel.hpp"

Channel::Channel() { }
Channel::Channel(const Channel &other) {
	*this = other;
}

Channel::~Channel() { }			// `a voir comment supprimer les différents éléments de la classe channel

Channel	&Channel::operator=(const Channel &other) {
	if (this != &other) {		// PEUT ETRE À ENLEVER (je l'ai juste mis pour que ca compile - MAX)
		this->_name = other._name;
	}							//copy function for Channel ?
	return *this;
}

void	Channel::add(User &user) {
	(void)user;
	// use epoll(epfd, EPOLL_CTL_ADD, fd, *event) for this function ?
}

void	Channel::del(User &user) {
	(void)user;
	// use epoll(epfd, EPOLL_CTL_DEL, fd, *event) for this function ?
}