/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafleith <vafleith@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 23:30:28 by vafleith          #+#    #+#             */
/*   Updated: 2024/10/20 14:30:10 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	are_full(t_dinner *dinner_table, t_philosopher *philos)
{
	int	i;

	i = 0;
	while (i < dinner_table->rules->nb_of_philo
		&& dinner_table->rules->max_nb_meals > 0
		&& philos[i].meals_eaten >= dinner_table->rules->max_nb_meals)
		i++;
	return (i == dinner_table->rules->nb_of_philo);
}


static int check_philo_life(t_dinner *dinner_table, t_philosopher *philos) {
	int i;
	size_t last_meal_time;
	size_t actual_time;

	while (1) {
		i = 0;
		while (i < dinner_table->rules->nb_of_philo) {
			if (are_full(dinner_table, philos))
				return 1;
			last_meal_time = philos[i].last_meal;
			actual_time = get_current_time_ms();
			if (actual_time - last_meal_time > (size_t)dinner_table->rules->time_to_die)
			{
				philo_couic(&philos[i]);
				return 1;
			}
		}
	}
	return 0;
}

static bool has_to_stop(t_dinner *dinner_table) {
	pthread_mutex_lock(&dinner_table->death_guardian);
	bool status = dinner_table->stop_simulation;
	pthread_mutex_unlock(&dinner_table->death_guardian);
	return status;
}

static void	*routine(void *params)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)params;
	while (!has_to_stop(philo->dinner_table) && (philo->meals_eaten != philo->dinner_table->rules->max_nb_meals || philo->dinner_table->rules->max_nb_meals == 0))
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
		dinner_table->philos[i].last_meal = 0;
		if (pthread_create(&dinner_table->philos[i].thread_id, NULL, routine,
				&(dinner_table->philos[i])))
		{
			free(dinner_table->philos);
			free(dinner_table->forks);
			return (1);
		}
		usleep(100);
		i++;
	}
	check_philo_life(dinner_table, dinner_table->philos);
	table_destructor(dinner_table, dinner_table->rules->nb_of_philo);
	return (0);
}
