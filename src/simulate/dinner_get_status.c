/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_get_status.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafleith <vafleith@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 12:20:34 by vafleith          #+#    #+#             */
/*   Updated: 2024/10/22 12:21:07 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	are_full(t_dinner *dinner_table, t_philosopher *philos)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&dinner_table->status_guardian);
	while (i < dinner_table->rules->nb_of_philo
		&& dinner_table->rules->max_nb_meals > 0
		&& philos[i].meals_eaten >= dinner_table->rules->max_nb_meals)
		i++;
	pthread_mutex_unlock(&dinner_table->status_guardian);
	return (i == dinner_table->rules->nb_of_philo);
}

bool	has_to_stop(t_dinner *dinner_table)
{
	bool	status;

	pthread_mutex_lock(&dinner_table->death_guardian);
	status = dinner_table->stop_simulation;
	pthread_mutex_unlock(&dinner_table->death_guardian);
	return (status);
}