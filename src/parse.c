/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafleith <vafleith@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 22:35:52 by vafleith          #+#    #+#             */
/*   Updated: 2024/06/25 22:58:14 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int is_valid(char *arg)
{
	while(*arg)
	{
		if (!ft_isdigit(*arg))
			return 0;
		arg++;
	}
	return 1;
}

t_rules parse_rules(int argc, char **argv)
{
	t_rules rules;
	int i;

	i = 1;
	while (argv[i])
	{
		if (!is_valid(argv[i]))
			argument_error();
		i++;
	}
	rules.nb_of_philo = ft_atoi(argv[1]);
	rules.time_to_die = ft_atoi(argv[2]);
	rules.time_to_eat = ft_atoi(argv[3]);
	rules.time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		rules.nb_of_time_each_philo_must_eat = ft_atoi(argv[5]);
	else 
		rules.nb_of_time_each_philo_must_eat = -1;
	return rules;
}
