/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_destructor.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafleith <vafleith@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 11:10:02 by vafleith          #+#    #+#             */
/*   Updated: 2024/10/15 16:35:16 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_mutex	*forks_destructor(t_mutex *forks, int total_nb)
{
	int	i;

	i = 0;
	while (i < total_nb)
	{
		pthread_mutex_destroy(forks + i);
		i++;
	}
	free(forks);
	return (NULL);
}

int	table_destructor(t_dinner dinner_table, int nb_threads)
{
	int	i;

	forks_destructor(dinner_table.forks, dinner_table.rules.nb_of_philo);
	i = 0;
	while (i < nb_threads)
	{
		if (pthread_join(dinner_table.philos[i].thread_id, NULL) != SUCCESS)
		{
			printf("Error joining thread %d\n", i);
			free(dinner_table.philos);
			return (1);
		}
		printf("Thread %d has finished.\n", i);
		i++;
	}
	free(dinner_table.philos);
	return (1);
}
