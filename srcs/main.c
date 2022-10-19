/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorampon <lorampon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 13:15:59 by lorampon          #+#    #+#             */
/*   Updated: 2022/10/19 13:37:24 by lorampon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_free(t_main *instance)
{
	size_t	i;

	i = 0;
	while (i < instance->amount)
	{
		pthread_mutex_destroy(&instance->fork_mutex[i]);
		i++;
	}
	pthread_mutex_destroy(&instance->die_mutex);
	if (!instance->philosophers || !instance->forks)
		return (0);
	if (!instance->fork_mutex)
		return (0);
	free(instance->fork_mutex);
	free(instance->philosophers);
	free(instance->forks);
	return (0);
}

int	sleep_think(t_philosopher *philo)
{
	if (is_dead(philo))
		return (1);
	printf("%zu philo %d is sleeping\n",
		get_time() - philo->instance->start_time, philo->position + 1);
	ft_usleep(philo->instance->ttsleep);
	if (is_dead(philo))
		return (1);
	printf("%zu philo %d is thinking\n",
		get_time() - philo->instance->start_time, philo->position + 1);
	return (0);
}

int	is_dead(t_philosopher *philo)
{
	if (!philo->instance->dead[0])
		return (1);
	if (!philo->eating && get_time() > philo->threshold)
	{
		pthread_mutex_lock(&philo->instance->die_mutex);
		if (philo->instance->dead[0])
		{
			memset(philo->instance->dead, 0, 1);
			usleep(1000);
			printf("%zu philo %d is dead\n",
			get_time() - philo->instance->start_time, philo->position + 1);
			pthread_mutex_unlock(&philo->instance->die_mutex);
			return (1);
		}
		pthread_mutex_unlock(&philo->instance->die_mutex);
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_main	instance;

	if (!init_args(&instance, argc, argv))
		return (1);
	if (!init_philo(&instance))
	{
		free(instance.philosophers);
		free(instance.forks);
		return (1);
	}
	if (!init_mutexes(&instance))
	{
		ft_free(&instance);
		return (1);
	}
	ft_exec(&instance);
	ft_free(&instance);
	return (0);
}
