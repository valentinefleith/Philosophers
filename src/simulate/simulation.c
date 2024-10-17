/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafleith <vafleith@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 23:30:28 by vafleith          #+#    #+#             */
/*   Updated: 2024/10/17 16:18:21 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

static void	print_philologs(char *log, t_philosopher *philo)
{
	size_t	timestamp;

	timestamp = get_current_time_ms() - philo->dinner_table->start_time;
	pthread_mutex_lock(&philo->dinner_table->print_guardian);
	printf("at %li ms \tphilo nb %i\t%s\n", timestamp, philo->id, log);
	pthread_mutex_unlock(&philo->dinner_table->print_guardian);
}

static void	philo_miam(t_philosopher *philo)
{
	t_dinner	*table;
	char		message[30];

	table = philo->dinner_table;
	pthread_mutex_lock(&table->forks[philo->first_fork_id]);
	sprintf(message, "has taken fork %i", philo->first_fork_id);
	print_philologs(message, philo);
	pthread_mutex_lock(&table->forks[philo->second_fork_id]);
	sprintf(message, "has taken fork %i", philo->second_fork_id);
	print_philologs(message, philo);
	print_philologs("is eating", philo);
	sleep_boosted(table->rules.time_to_eat);
	pthread_mutex_unlock(&table->forks[philo->first_fork_id]);
	pthread_mutex_unlock(&table->forks[philo->second_fork_id]);
}

static void	*routine(void *params)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)params;
	philo_miam(philo);
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
		if (pthread_create(&dinner_table->philos[i].thread_id, NULL, routine,
				&(dinner_table->philos[i])))
			return (1);
		i++;
	}
	table_destructor(dinner_table, dinner_table->rules.nb_of_philo);
	return (0);
}
