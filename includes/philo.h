/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorampon <lorampon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 16:59:02 by lorampon          #+#    #+#             */
/*   Updated: 2022/10/18 17:03:08 by lorampon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <unistd.h>
# include <string.h>

struct	s_main;

typedef struct s_philosopher
{
	pthread_t		tid;
	int				position;
	int				l_fork;
	int				r_fork;
	size_t			meals;
	size_t			eating;
	size_t			last_meal;
	size_t			threshold;
	struct s_main	*instance;
}				t_philosopher;

typedef struct s_main
{
	size_t			start_time;
	size_t			amount;
	size_t			tteat;
	size_t			ttdie;
	size_t			ttsleep;
	size_t			nbr_meals;
	size_t			finished;
	t_philosopher	*philosophers;
	int				*forks;
	int				dead[1];
	size_t			full;
	pthread_mutex_t	full_mutex;
	pthread_mutex_t	*fork_mutex;
	pthread_mutex_t	die_mutex;
}				t_main;

size_t	get_time(void);
void	ft_usleep(int ms);
int		ft_atoi(const char *string, size_t *dst);
int		ft_exec(t_main *instance);
void	*philo_life(void *temp);
int		take_forks(t_philosopher *philo);
int		is_dead(t_philosopher *philo);
int		eat(t_philosopher *philo);
int		drop_forks(t_philosopher *philo);
int		init_args(t_main *instance, int argc, char **argv);
int		init_philo(t_main *instance);
int		init_mutexes(t_main *instance);
int		sleep_think(t_philosopher *philo);
void	philo_life_help(t_philosopher *philo);

#endif