/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaginot <cmaginot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 16:33:48 by mmercore          #+#    #+#             */
/*   Updated: 2023/03/22 16:28:17 by cmaginot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCL/ft_irc.hpp"

void	ft_memset(void *a, char c, size_t l)
{
	size_t i;

	i = 0;
	if (l == 0)
	{
		while(((char *)a)[i] != '\0' || ((char *)a)[i] != c)
		{
			((char *)a)[i] = c;
			i++;
		}
	}
	else
	{
		while(i < l)
		{
			((char *)a)[i] = c;
			i++;
		}
	}
}

void	ft_bzero(void *a, size_t l)
{
	ft_memset(a, '\0', l);
}

std::string	convert_int_to_string(int val)
{
	std::stringstream strstr;
	strstr << val;
	std::string str = strstr.str();
	return (str);
}
