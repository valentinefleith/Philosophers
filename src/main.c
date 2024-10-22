/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafleith <vafleith@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 12:09:30 by vafleith          #+#    #+#             */
/*   Updated: 2024/10/22 12:23:34 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_rules		rules;
	t_dinner	dinner_table;

	if (argc < 5 || argc > 6)
		argument_error();
	rules = parse_rules(argc, argv);
	set_the_table(&rules, &dinner_table);
	if (!dinner_table.philos || !dinner_table.forks)
		return (EXIT_FAILURE);
	if (start_dinner(&dinner_table) == 1)
		return (EXIT_FAILURE);
	return (0);
}
