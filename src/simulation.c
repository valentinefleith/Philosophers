/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafleith <vafleith@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 23:30:28 by vafleith          #+#    #+#             */
/*   Updated: 2024/10/14 23:45:26 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void *routine(void *ptr) {
	printf("coucou\n");
	return NULL;
}

static int explosion(t_rules *rules, t_philosopher *table) {
	int i = 0;
	while (i < rules->nb_of_philo) {
		pthread_join(table[i].thread_id, NULL);
		i++;
	}
	free(table);
	return 1;
}

int start_dinner(t_rules *rules, t_philosopher *table) {
	int i = 0;
	while (i < rules->nb_of_philo) {
		if (pthread_create(&table[i].thread_id, NULL, routine, table + i) != 0)
			return explosion(rules, table);
		i++;
	}
	explosion(rules, table);
	return 0;
}
