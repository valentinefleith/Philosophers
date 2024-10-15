/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafleith <vafleith@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 23:30:28 by vafleith          #+#    #+#             */
/*   Updated: 2024/10/15 16:38:02 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*routine(void *args)
{
	t_philosopher	*dinner_table;

	dinner_table = (t_philosopher *)args;
	printf("Hello from philo %d\n", dinner_table->id + 1);
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
