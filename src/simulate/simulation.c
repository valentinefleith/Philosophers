/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafleith <vafleith@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 23:30:28 by vafleith          #+#    #+#             */
/*   Updated: 2024/10/15 17:07:07 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*routine(void *args)
{
	t_philosopher	*plato;

	plato = (t_philosopher *)args;
	t_dinner *table = plato->dinner_table;
	pthread_mutex_lock(&table->print_guardian);
	printf("Hello from philo %d\n", plato->id + 1);
	pthread_mutex_unlock(&table->print_guardian);
	return (NULL);
}

int	start_dinner(t_dinner dinner_table)
{
	int	i;

	i = 0;
	while (i < dinner_table.rules.nb_of_philo)
	{
		if (pthread_create(&dinner_table.philos[i].thread_id, NULL, routine,
				&dinner_table.philos[i]) != 0)
			return (table_destructor(dinner_table, i + 1));
		i++;
	}
	return (0);
}
