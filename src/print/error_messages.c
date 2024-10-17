/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_messages.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafleith <vafleith@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 22:16:19 by vafleith          #+#    #+#             */
/*   Updated: 2024/10/17 16:19:43 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	argument_error(void)
{
	ft_putstr_fd("Usage: ./philo nb_of_philo time_to_die time_to_eat ", 2);
	ft_putendl_fd("time_to_sleep [nb_of_times_each_philo_must_eat]", 2);
	exit(1);
}
