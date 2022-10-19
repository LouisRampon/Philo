/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorampon <lorampon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 13:58:51 by lorampon          #+#    #+#             */
/*   Updated: 2022/10/19 12:07:06 by lorampon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	take_forks_help(t_philosopher *philo)
{
	while (1)
	{
		if (is_dead(philo))
			return (1);
		pthread_mutex_lock(&philo->instance->fork_mutex[philo->r_fork]);
		if (!philo->instance->forks[philo->r_fork])
		{
			printf("%zu philo %d has taken a fork\n",
				get_time() - philo->instance->start_time, philo->position + 1);
			philo->instance->forks[philo->r_fork] = 1;
			break ;
		}
		pthread_mutex_unlock(&philo->instance->fork_mutex[philo->r_fork]);
		usleep(100);
	}
	pthread_mutex_unlock(&philo->instance->fork_mutex[philo->r_fork]);
	return (0);
}

int	take_forks(t_philosopher *philo)
{
	while (1)
	{
		if (is_dead(philo))
			return (1);
		pthread_mutex_lock(&philo->instance->fork_mutex[philo->l_fork]);
		if (!philo->instance->forks[philo->l_fork])
		{
			printf("%zu philo %d has taken a fork\n",
				get_time() - philo->instance->start_time, philo->position + 1);
			philo->instance->forks[philo->l_fork] = 1;
			break ;
		}
		pthread_mutex_unlock(&philo->instance->fork_mutex[philo->l_fork]);
		usleep(100);
	}
	pthread_mutex_unlock(&philo->instance->fork_mutex[philo->l_fork]);
	if (take_forks_help(philo))
		return (1);
	return (0);
}

void	*philo_life(void *temp)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)temp;
	philo->last_meal = get_time();
	philo->threshold = philo->last_meal + philo->instance->ttdie;
	if (philo->position % 2)
		usleep(100);
	if (philo->instance->nbr_meals == 0)
	{
		while (1)
		{
			if (take_forks(philo))
				break ;
			if (eat(philo))
				break ;
			if (sleep_think(philo))
				break ;
		}
	}
	else
		philo_life_help(philo);
	return (NULL);
}

void	philo_life_help(t_philosopher *philo)
{
	while (1)
	{
		if (take_forks(philo))
			break ;
		if (eat(philo))
			break ;
		if (sleep_think(philo))
			break ;
		if (philo->meals == philo->instance->nbr_meals)
		{
			pthread_mutex_lock(&philo->instance->full_mutex);
			philo->instance->full++;
			pthread_mutex_unlock(&philo->instance->full_mutex);
		}
		pthread_mutex_lock(&philo->instance->full_mutex);
		if (philo->instance->full >= philo->instance->amount)
		{
			pthread_mutex_unlock(&philo->instance->full_mutex);
			return ;
		}
		pthread_mutex_unlock(&philo->instance->full_mutex);
		philo->meals++;
	}	
}

int	ft_exec(t_main *instance)
{
	size_t		i;

	i = 0;
	instance->start_time = get_time();
	while (i < instance->amount)
	{
		if (pthread_create(&instance->philosophers[i].tid,
				NULL, &philo_life, (void *)&instance->philosophers[i]))
			return (1);
		i++;
	}
	i = 0;
	while (i < instance->amount)
	{
		pthread_join(instance->philosophers[i].tid, NULL);
		i++;
	}
	return (0);
}
