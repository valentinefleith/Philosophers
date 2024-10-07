/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafleith <vafleith@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 12:08:04 by vafleith          #+#    #+#             */
/*   Updated: 2024/10/07 12:23:08 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define STR_U32_MAX "2147483647"

# define NB_OF_PHILO_IDX 1
# define TIME_DIE_IDX 2
# define TIME_EAT_IDX 3
# define TIME_SLEEP_IDX 4

typedef struct s_rules
{
	int			nb_of_philo;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			nb_of_time_each_philo_must_eat;
}				t_rules;

typedef struct s_philosopher
{
	int			id;
	pthread_t	thread_id;

}				t_philosopher;

t_rules			parse_rules(int argc, char **argv);

// PRINT UTILS
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char *s, int fd);
void			ft_putendl_fd(char *s, int fd);
void			argument_error(void);

// GENERAL UTILS
int				ft_strncmp(const char *s1, const char *s2, size_t n);
size_t			ft_strlen(const char *str);
int				ft_isdigit(int c);
char			*ft_strchr(const char *s, int c);
int				ft_atoi(const char *str);

#endif
