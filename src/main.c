/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafleith <vafleith@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 12:09:30 by vafleith          #+#    #+#             */
/*   Updated: 2024/10/15 15:31:51 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_rules		rules;
	t_dinner	dinner_table;

	// t_philosopher	*philo_table;
	if (argc < 5 || argc > 6)
		argument_error();
	rules = parse_rules(argc, argv);
	// philo_table = create_philo(rules);
	dinner_table = set_the_table(rules);
	if (!dinner_table.philos || !dinner_table.forks)
		return (EXIT_FAILURE);
	if (start_dinner(dinner_table) == 1)
		return (EXIT_FAILURE);
	table_destructor(dinner_table, dinner_table.rules.nb_of_philo);
	// printf("current time: %li\n", get_current_time_ms());
	// free(philo_table);
}
