/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafleith <vafleith@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 22:57:18 by vafleith          #+#    #+#             */
/*   Updated: 2024/06/25 22:58:52 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

char	*ft_strchr(const char *s, int c)
{
	while (*s && *s != (unsigned char)c)
		s++;
	if (*s == (unsigned char)c)
		return ((char *)s);
	return (NULL);
}

static unsigned int	ft_atoui(const char *str)
{
	int	output;

	output = 0;
	while (ft_isdigit(*str))
	{
		output = output * 10 + (*str - '0');
		str++;
	}
	return (output);
}

int	ft_atoi(const char *str)
{
	if (!*str)
		return (0);
	while (ft_strchr(" \t\n\r\v\f", *str))
		str++;
	if (*str == '-')
	{
		str++;
		return (-ft_atoui(str));
	}
	if (*str == '+')
		str++;
	return (ft_atoui(str));
}
