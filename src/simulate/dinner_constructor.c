/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_constructor.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafleith <vafleith@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 17:59:04 by vafleith          #+#    #+#             */
/*   Updated: 2024/10/15 11:22:41 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_state(t_philosopher *philos)
{
	philos->state.is_dead = false;
	philos->state.is_eating = false;
	philos->state.last_meal = -1;
	philos->state.meals_eaten = 0;
}

static void init_forks_ids(t_philosopher *philos, int index, t_rules rules) {
	
		if (index % 2)
		{
			philos[index].first_fork_id = index;
			philos[index].second_fork_id = (index + 1)
				% rules.nb_of_philo;
		}
		else
		{
			philos[index].second_fork_id = (index + 1)
				% rules.nb_of_philo;
			philos[index].first_fork_id = index;
		}
}

static t_philosopher	*philos_constructor(t_rules rules)
{
	t_philosopher	*philos;
	int				current_id;

	philos = malloc(rules.nb_of_philo * sizeof(t_philosopher));
	if (!philos)
		return (NULL);
	current_id = 0;
	while (current_id < rules.nb_of_philo)
	{
		philos[current_id].id = current_id;
		init_forks_ids(philos, current_id, rules);
		init_state(philos + current_id);
		current_id++;
	}
	return (philos);
}

static t_mutex *forks_constructor(t_rules rules) {
	t_mutex *forks;

	forks = malloc(rules.nb_of_philo * sizeof(t_mutex));
	if (!forks)
		return NULL;
	int current_id = 0;
	while (current_id < rules.nb_of_philo) {
		if (pthread_mutex_init(forks + current_id, NULL) != SUCCESS) {
			printf("Mutex %d allocation failed.\n", current_id);
			return forks_destructor(forks, current_id);
		}
		current_id++;
	}
	return forks;
}

t_dinner set_the_table(t_rules rules) {
	t_dinner table;

	table.philos = philos_constructor(rules);
	if (!table.philos) {
		table.forks = NULL;
		return table;
	}
	table.rules = rules;
	table.forks = forks_constructor(rules);
	if (!table.forks) {
		free(table.philos);
		return table;
	}
	table.start_time = 0; // not sure
	return table;
}
