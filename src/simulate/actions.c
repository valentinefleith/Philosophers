/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafleith <vafleith@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 17:59:02 by vafleith          #+#    #+#             */
/*   Updated: 2024/10/20 17:49:23 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void	print_philologs(char *log, t_philosopher *philo, bool dead)
{
	size_t	timestamp;
	
	if (has_to_stop(philo->dinner_table) && !dead)
		return;
	timestamp = get_current_time_ms() - philo->dinner_table->start_time;
	pthread_mutex_lock(&philo->dinner_table->print_guardian);
	if (dead)
		printf("\033[0;31m");
	else if (philo->id % 4 == 0)
		printf("\033[0;32m");
	else if (philo->id % 4 == 1)
		printf("\033[0;33m");
	else if (philo->id % 4 == 2)
		printf("\033[0;34m");
	else if (philo->id % 4== 3)
		printf("\033[0;35m");
	printf("%li ms \tphilo nb %i\t%s\n", timestamp, philo->id + 1, log);
	printf("\033[0m");
	pthread_mutex_unlock(&philo->dinner_table->print_guardian);
}

void	philo_miam(t_philosopher *philo)
{
	t_dinner	*table;

	table = philo->dinner_table;
	pthread_mutex_lock(&table->miam_guardian);
	pthread_mutex_lock(&table->forks[philo->first_fork_id]);
	print_philologs("has taken a fork", philo, false);
	pthread_mutex_lock(&table->forks[philo->second_fork_id]);
	print_philologs("has taken a fork", philo, false);
	pthread_mutex_lock(&table->status_guardian);
	philo->last_meal = get_current_time_ms();
	philo->meals_eaten++;
	pthread_mutex_unlock(&table->status_guardian);
	print_philologs("is eating", philo, false);
	sleep_boosted(table->rules->time_to_eat);
	pthread_mutex_unlock(&table->forks[philo->first_fork_id]);
	pthread_mutex_unlock(&table->forks[philo->second_fork_id]);
	pthread_mutex_unlock(&table->miam_guardian);
}

void	philo_zzz(t_philosopher *philo)
{
	print_philologs("is sleeping", philo, false);
	sleep_boosted(philo->dinner_table->rules->time_to_sleep);
}

void	philo_hmm(t_philosopher *philo)
{
	print_philologs("is thinking", philo, false);
	usleep(50);
}

void	philo_couic(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->dinner_table->death_guardian);
	philo->dinner_table->stop_simulation = true;
	philo->is_dead = true;
	pthread_mutex_unlock(&philo->dinner_table->death_guardian);
	pthread_mutex_lock(&philo->dinner_table->status_guardian);
	if (philo->meals_eaten != philo->dinner_table->rules->max_nb_meals)
		print_philologs("died", philo, true);
	pthread_mutex_unlock(&philo->dinner_table->status_guardian);
};
