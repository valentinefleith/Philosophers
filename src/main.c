/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafleith <vafleith@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 12:09:30 by vafleith          #+#    #+#             */
/*   Updated: 2024/06/25 22:47:31 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv, char **env)
{
	t_rules rules;
	if (argc < 5 || argc > 6)
		argument_error();
	rules = parse_rules(argc, argv);
	printf("%i\n", rules.nb_of_philo);
	(void)argc;
	(void)argv;
	(void)env;
	// printf("hello!\n");
}
