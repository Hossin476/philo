/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshail <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 15:05:41 by lshail            #+#    #+#             */
/*   Updated: 2023/05/06 18:08:34 by lshail           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philo_sleeping(t_philo *philo)
{
	ft_printf(philo, "is sleeping\n");
	ft_usleep(philo->info->time_to_sleep);
}

void	philo_eating(t_philo *philo)
{
	pthread_mutex_lock(philo->fork_mutex);
	ft_printf(philo, "has taken a fork\n");
	pthread_mutex_lock(philo->next_fork);
	ft_printf(philo, "has taken a fork\n");
	ft_printf(philo, "is eating\n");
	ft_usleep(philo->info->time_to_eat);
	pthread_mutex_lock(&philo->info->meal_mutex);
	philo->lst_time_eat = get_time();
	philo->nbr_of_meals++;
	pthread_mutex_unlock(&philo->info->meal_mutex);
	pthread_mutex_unlock(philo->fork_mutex);
	pthread_mutex_unlock(philo->next_fork);
}

void	*philo_life(void *philo)
{
	t_philo	*ph;

	ph = philo;
	if (ph->id % 2 == 0)
		usleep(500);
	while (1)
	{
		philo_eating(ph);
		philo_sleeping(ph);
		ft_printf(ph, "is thinking\n");
	}
	return (0);
}

int	check_meal(t_philo **philo)
{
	int	i;
	int	token;

	i = 0;
	token = 0;
	if (philo[0]->info->max_meals != -1)
	{
		while (i < philo[0]->info->num_of_philos)
		{
			if (philo[i]->nbr_of_meals < philo[0]->info->max_meals)
				token = 1;
			i++;
		}
	}
	if (!token)
		return (1);
	return (0);
}

int	check_death(t_philo *philo)
{
	t_data	*data;

	data = philo->info;
	if (get_time() - philo->lst_time_eat
		> (unsigned long long)data->time_to_die)
	{
		pthread_mutex_lock(&data->print_mutex);
		printf("%llu %d %s", get_time() - philo->info->start_time,
			philo->id, "\033[31;1mDied \033[0m \n");
		return (1);
	}
	return (0);
}
