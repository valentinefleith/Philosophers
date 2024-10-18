/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafleith <vafleith@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 23:30:28 by vafleith          #+#    #+#             */
/*   Updated: 2024/10/19 00:33:37 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	update_full(t_dinner *dinner_table, t_philosopher *philos)
{
	int	i;

	i = 0;
	while (i < dinner_table->rules.nb_of_philo
		&& dinner_table->rules.max_nb_meals > 0
		&& philos[i].state.meals_eaten >= dinner_table->rules.max_nb_meals)
		i++;
	return (i == dinner_table->rules.nb_of_philo);
}

static void	check_philo_life(t_dinner *dinner_table, t_philosopher *philos)
{
	int		i;
	size_t	last_meal_time;

	while (!dinner_table->everyones_full)
	{
		i = 0;
		while (i < dinner_table->rules.nb_of_philo
			&& !dinner_table->stop_simulation)
		{
			pthread_mutex_lock(&dinner_table->status_guardian);
			last_meal_time = philos[i].state.last_meal;
			if (get_current_time_ms()
				- last_meal_time > (size_t)dinner_table->rules.time_to_die
				&& last_meal_time != 0)
			{
				philo_couic(philos + i);
			}
			pthread_mutex_unlock(&dinner_table->status_guardian);
			i++;
		}
		if (dinner_table->stop_simulation)
			break;
		dinner_table->everyones_full = update_full(dinner_table, philos);
	}
}

static void	*routine(void *params)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)params;
	while (!philo->dinner_table->stop_simulation)
	{
		philo_miam(philo);
		if (philo->state.meals_eaten == philo->dinner_table->rules.max_nb_meals
			&& philo->dinner_table->rules.max_nb_meals > 0)
		{
			pthread_mutex_lock(&philo->dinner_table->status_guardian);
			philo->state.is_full = true;
			pthread_mutex_unlock(&philo->dinner_table->status_guardian);
			break ;
		}
		if (!philo->state.is_full)
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
	while (i < dinner_table->rules.nb_of_philo)
	{
		dinner_table->philos[i].state.last_meal = 0;
		if (pthread_create(&dinner_table->philos[i].thread_id, NULL, routine,
				&(dinner_table->philos[i])))
			return (1);
		i++;
	}
	check_philo_life(dinner_table, dinner_table->philos);
	table_destructor(dinner_table, dinner_table->rules.nb_of_philo);
	return (0);
}
