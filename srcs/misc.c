/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorampon <lorampon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 13:21:46 by lorampon          #+#    #+#             */
/*   Updated: 2022/10/19 13:40:48 by lorampon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

size_t	get_time(void)
{
	static struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_usleep(int ms)
{
	size_t	end;

	end = get_time() + ms;
	usleep(ms * 1000 * 0.9);
	while (get_time() < end)
		usleep(1000);
}

int	ft_atoi(const char *string, size_t *dst)
{
	int	i;

	i = 0;
	if (string[i] == '\0')
		return (1);
	*dst = 0;
	while (string[i] && string[i] >= '0' && string[i] <= '9')
	{
		*dst = *dst * 10 + (string[i] - '0');
		i++;
	}
	if (string[i] != '\0')
		return (1);
	return (0);
}

int	drop_forks(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->instance->fork_mutex[philo->l_fork]);
	philo->instance->forks[philo->l_fork] = 0;
	pthread_mutex_unlock(&philo->instance->fork_mutex[philo->l_fork]);
	pthread_mutex_lock(&philo->instance->fork_mutex[philo->r_fork]);
	philo->instance->forks[philo->r_fork] = 0;
	pthread_mutex_unlock(&philo->instance->fork_mutex[philo->r_fork]);
	return (0);
}

int	eat(t_philosopher *philo)
{
	philo->last_meal = get_time();
	printf("%zu philo %d is eating\n",
		get_time() - philo->instance->start_time, philo->position + 1);
	philo->threshold = philo->last_meal + philo->instance->ttdie;
	ft_usleep(philo->instance->tteat);
	if (drop_forks(philo))
		return (1);
	return (0);
}
