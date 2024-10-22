/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_start.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafleith <vafleith@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 23:30:28 by vafleith          #+#    #+#             */
/*   Updated: 2024/10/22 12:29:43 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	monitoring(t_dinner *dinner_table, t_philosopher *philos)
{
	int		i;
	size_t	last_meal_time;

	if (dinner_table->rules->nb_of_philo == 1)
		return (0);
	while (1)
	{
		i = 0;
		while (i < dinner_table->rules->nb_of_philo)
		{
			if (are_full(dinner_table, philos))
				return (1);
			pthread_mutex_lock(&dinner_table->status_guardian);
			last_meal_time = philos[i].last_meal;
			pthread_mutex_unlock(&dinner_table->status_guardian);
			if (get_current_time_ms()
				- last_meal_time >= (size_t)dinner_table->rules->time_to_die)
				return (philo_couic(&philos[i]));
			i++;
		}
		usleep(50);
	}
	return (0);
}

static void	*lonely_philo(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->dinner_table->forks[0]);
	print_philologs("has taken the first fork", philo, false);
	sleep_boosted(philo->dinner_table->rules->time_to_die);
	pthread_mutex_unlock(&philo->dinner_table->forks[0]);
	print_philologs("died", philo, true);
	return (NULL);
}

static void	*routine(void *params)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)params;
	if (philo->dinner_table->rules->nb_of_philo == 1)
		return (lonely_philo(philo));
	while (!has_to_stop(philo->dinner_table)
		&& (philo->meals_eaten != philo->dinner_table->rules->max_nb_meals
			|| philo->dinner_table->rules->max_nb_meals == 0))
	{
		philo_miam(philo);
		if (!has_to_stop(philo->dinner_table))
		{
			philo_zzz(philo);
			philo_hmm(philo);
		}
	}
	return (NULL);
}

int	start_dinner(t_dinner *dinner_table)
{
	int	i;

	i = 0;
	dinner_table->start_time = get_current_time_ms();
	while (i < dinner_table->rules->nb_of_philo)
	{
		if (pthread_create(&dinner_table->philos[i].thread_id, NULL, routine,
				&(dinner_table->philos[i])))
		{
			free(dinner_table->philos);
			free(dinner_table->forks);
			return (1);
		}
		pthread_mutex_lock(&dinner_table->status_guardian);
		dinner_table->philos[i].last_meal = dinner_table->start_time;
		pthread_mutex_unlock(&dinner_table->status_guardian);
		usleep(100);
		i++;
	}
	monitoring(dinner_table, dinner_table->philos);
	table_destructor(dinner_table, dinner_table->rules->nb_of_philo);
	return (0);
}
