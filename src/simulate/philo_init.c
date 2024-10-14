/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafleith <vafleith@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 17:59:04 by vafleith          #+#    #+#             */
/*   Updated: 2024/10/14 23:23:11 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_state(t_philosopher *table)
{
	table->state.is_dead = false;
	table->state.is_eating = false;
	table->state.last_meal = -1;
	table->state.meals_eaten = 0;
}

t_philosopher	*create_philo(t_rules rules)
{
	t_philosopher	*table;
	int				current_id;

	table = malloc(rules.nb_of_philo * sizeof(t_philosopher));
	if (!table)
		return (NULL);
	current_id = -1;
	while (++current_id < rules.nb_of_philo)
	{
		table[current_id].id = current_id;
		if (current_id % 2)
		{
			table[current_id].first_fork_id = current_id;
			table[current_id].second_fork_id = (current_id + 1)
				% rules.nb_of_philo;
		}
		else
		{
			table[current_id].second_fork_id = (current_id + 1)
				% rules.nb_of_philo;
			table[current_id].first_fork_id = current_id;
		}
	}
	init_state(table);
	return (table);
}
