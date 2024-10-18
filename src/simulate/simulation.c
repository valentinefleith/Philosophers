/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafleith <vafleith@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 23:30:28 by vafleith          #+#    #+#             */
/*   Updated: 2024/10/18 19:10:13 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	check_philo_life(t_dinner *dinner_table)
{
	t_philosopher	*philos;
	int				i;
	size_t			last_meal_time;
	bool			is_full;

	philos = dinner_table->philos;
	while (!dinner_table->someones_dead)
	{
		i = 0;
		while (i < dinner_table->rules.nb_of_philo)
		{
			pthread_mutex_lock(&dinner_table->status_guardian);
			last_meal_time = philos[i].state.last_meal;
			is_full = philos[i].state.is_full;
			pthread_mutex_unlock(&dinner_table->status_guardian);
			if (get_current_time_ms()
				- last_meal_time > (size_t)dinner_table->rules.time_to_die && !is_full && last_meal_time != 0)
				philo_couic(philos + i);
			i++;
		}
	}
}

static void	*routine(void *params)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)params;
	while (!philo->dinner_table->someones_dead)
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
		if (!philo->state.is_full) {
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
	check_philo_life(dinner_table);
	table_destructor(dinner_table, dinner_table->rules.nb_of_philo);
	return (0);
}
