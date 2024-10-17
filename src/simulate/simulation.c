/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafleith <vafleith@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 23:30:28 by vafleith          #+#    #+#             */
/*   Updated: 2024/10/17 15:25:21 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	print_philologs(char *log, t_philosopher *philo)
{
	size_t timestamp;
	timestamp = get_current_time_ms() - philo->dinner_table->start_time;
	pthread_mutex_lock(&philo->dinner_table->print_guardian);
	printf("%li\t%i\t%s\n", timestamp, philo->id, log);
	pthread_mutex_unlock(&philo->dinner_table->print_guardian);
}

static void	*routine(void *params)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)params;
	print_philologs("is sleeping", philo);
	return (NULL);
}

int	start_dinner(t_dinner *dinner_table)
{
	int	i;

	i = 0;
	dinner_table->start_time = get_current_time_ms();
	while (i < dinner_table->rules.nb_of_philo)
	{
		dinner_table->philos[i].state.last_meal = get_current_time_ms();
		if (pthread_create(&dinner_table->philos[i].thread_id,
				NULL, routine, &(dinner_table->philos[i])))
			return (1);
		i++;
	}
	table_destructor(dinner_table, dinner_table->rules.nb_of_philo);
	return (0);
}
