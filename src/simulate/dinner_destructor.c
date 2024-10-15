/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_destructor.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafleith <vafleith@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 11:10:02 by vafleith          #+#    #+#             */
/*   Updated: 2024/10/15 11:22:49 by vafleith         ###   ########.fr       */
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


