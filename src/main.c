/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafleith <vafleith@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 12:09:30 by vafleith          #+#    #+#             */
/*   Updated: 2024/10/14 17:59:33 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_rules			rules;
	t_philosopher	*philo_table;

	if (argc < 5 || argc > 6)
		argument_error();
	rules = parse_rules(argc, argv);
	philo_table = create_philo(rules);
	if (!philo_table)
		return (1);
	for (int i = 0; i < rules.nb_of_philo; i++)
	{
		printf("%i\n", philo_table[i].id);
	}
	free(philo_table);
}
