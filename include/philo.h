/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafleith <vafleith@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 12:08:04 by vafleith          #+#    #+#             */
/*   Updated: 2024/10/17 16:17:06 by vafleith         ###   ########.fr       */
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

# define STR_I32_MAX "2147483647"

# define SUCCESS 0

typedef enum e_rules_idx
{
	NB_OF_PHILO_IDX = 1,
	TIME_DIE_IDX,
	TIME_EAT_IDX,
	TIME_SLEEP_IDX,
	MAX_NB_MEALS_IDX
}						t_rules_idx;

typedef struct s_rules
{
	int					nb_of_philo;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					max_nb_meals;
}						t_rules;

typedef struct s_state
{
	bool				is_eating;
	bool				is_dead;
	int					meals_eaten;
	int					last_meal;
}						t_state;

struct s_dinner;

typedef struct s_philosopher
{
	int					id;
	pthread_t			thread_id;
	t_state				state;
	int					first_fork_id;
	int					second_fork_id;
	struct s_dinner		*dinner_table;
}						t_philosopher;

typedef pthread_mutex_t	t_mutex;

typedef struct s_dinner
{
	t_philosopher		*philos;
	t_rules				rules;
	t_mutex				*forks;
	size_t				start_time;
	t_mutex				print_guardian;
}						t_dinner;

t_rules					parse_rules(int argc, char **argv);
void					set_the_table(t_rules rules, t_dinner *table);
size_t					get_current_time_ms(void);
int						start_dinner(t_dinner *dinner_table);
void					sleep_boosted(size_t duration_in_ms);

// DESTRUCTORS
t_mutex					*forks_destructor(t_mutex *forks, int total_nb);
int						table_destructor(t_dinner *dinner_table,
							int nb_threads);

// PRINT UTILS
void					ft_putchar_fd(char c, int fd);
void					ft_putstr_fd(char *s, int fd);
void					ft_putendl_fd(char *s, int fd);
void					argument_error(void);

// GENERAL UTILS
int						ft_strncmp(const char *s1, const char *s2, size_t n);
size_t					ft_strlen(const char *str);
int						ft_isdigit(int c);
char					*ft_strchr(const char *s, int c);
int						ft_atoi(const char *str);

#endif
