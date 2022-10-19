/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorampon <lorampon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 13:58:13 by lorampon          #+#    #+#             */
/*   Updated: 2022/10/19 13:40:22 by lorampon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	init_mutexes(t_main *instance)
{
	size_t	i;

	instance->fork_mutex = malloc(sizeof(pthread_mutex_t) * instance->amount);
	if (!instance->fork_mutex)
		return (0);
	i = 0;
	while (i < instance->amount)
	{
		pthread_mutex_init(&instance->fork_mutex[i], NULL);
		i++;
	}
	pthread_mutex_init(&instance->die_mutex, NULL);
	pthread_mutex_init(&instance->full_mutex, NULL);
	return (1);
}

int	init_philo(t_main *instance)
{
	size_t	i;

	instance->philosophers = malloc(sizeof(t_philosopher) * instance->amount);
	instance->forks = malloc(sizeof(int) * instance->amount);
	if (!instance->philosophers || !instance->forks)
		return (0);
	i = 0;
	while (i < instance->amount)
	{
		instance->forks[i] = 0;
		instance->philosophers[i].position = i;
		instance->philosophers[i].l_fork = i;
		instance->philosophers[i].r_fork = (i + 1) % instance->amount;
		instance->philosophers[i].meals = 0;
		instance->philosophers[i].eating = 0;
		instance->philosophers[i].instance = instance;
		i++;
	}
	return (1);
}

int	init_args(t_main *instance, int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (1);
	if (ft_atoi(argv[1], &instance->amount) || instance->amount == 0
		|| ft_atoi(argv[2], &instance->ttdie) || instance->ttdie == 0
		|| ft_atoi(argv[3], &instance->tteat) || instance->tteat == 0
		|| ft_atoi(argv[4], &instance->ttsleep) || instance->ttsleep == 0)
		return (0);
	if (argc == 6 && (ft_atoi(argv[5], &instance->nbr_meals)
			|| instance->nbr_meals == 0))
		return (0);
	else if (!instance->nbr_meals)
		instance->nbr_meals = 0;
	instance->dead[0] = 1;
	instance->finished = 0;
	instance->full = 0;
	return (1);
}
