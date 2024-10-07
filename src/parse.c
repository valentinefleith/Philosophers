/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafleith <vafleith@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 22:35:52 by vafleith          #+#    #+#             */
/*   Updated: 2024/10/07 12:23:38 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	is_only_digits(char *arg)
{
	while (*arg)
	{
		if (!ft_isdigit(*arg))
			return (false);
		arg++;
	}
	return (true);
}

static bool	is_overflowing(char *arg)
{
	size_t	len_arg;

	len_arg = ft_strlen(arg);
	if (len_arg < ft_strlen(STR_U32_MAX))
		return (false);
	if (len_arg > ft_strlen(STR_U32_MAX))
		return (true);
	return (ft_strncmp(arg, STR_U32_MAX, ft_strlen(STR_U32_MAX)) > 0);
}

t_rules	parse_rules(int argc, char **argv)
{
	t_rules	rules;
	int		i;

	i = 1;
	while (argv[i])
	{
		if (!is_only_digits(argv[i]) || is_overflowing(argv[i]))
			argument_error();
		i++;
	}
	rules.nb_of_philo = ft_atoi(argv[NB_OF_PHILO_IDX]);
	rules.time_to_die = ft_atoi(argv[TIME_DIE_IDX]);
	rules.time_to_eat = ft_atoi(argv[TIME_EAT_IDX]);
	rules.time_to_sleep = ft_atoi(argv[TIME_SLEEP_IDX]);
	if (argc == 6)
		rules.nb_of_time_each_philo_must_eat = ft_atoi(argv[5]);
	else
		rules.nb_of_time_each_philo_must_eat = -1;
	return (rules);
}
