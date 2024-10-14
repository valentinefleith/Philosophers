/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafleith <vafleith@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 12:09:30 by vafleith          #+#    #+#             */
/*   Updated: 2024/10/14 11:43:09 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_philosopher *create_philo(t_rules rules) {
	t_philosopher *table;

	table = malloc(rules.nb_of_philo * sizeof(t_philosopher));
	if (!table)
		return NULL;
	int current_id;
	current_id = 0;
	while (current_id < rules.nb_of_philo) {
		table[current_id].id = current_id;
		current_id++;
	}
	return table;
}

int	main(int argc, char **argv)
{
	t_rules	rules;

	if (argc < 5 || argc > 6)
		argument_error();
	rules = parse_rules(argc, argv);
	t_philosopher *table;
	table = create_philo(rules);
	for (int i = 0; i < rules.nb_of_philo; i++) {
		printf("%i\n", table[i].id);
	}
}
