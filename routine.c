/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshail <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 15:05:41 by lshail            #+#    #+#             */
/*   Updated: 2023/04/30 15:17:26 by lshail           ###   ########.fr       */
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
	int		i;

	i = -1;
	ph = philo;
	if (ph->id % 2)
		usleep(200);
	while (1)
	{
		philo_eating(ph);
		philo_sleeping(ph);
		ft_printf(ph, "is thinking\n");
	}
	return (0);
}

void check_death(t_philo *philo)
{
    t_data *data = philo->info;
    if (get_time() - philo->lst_time_eat > (unsigned long long)data->time_to_die)
    {
        pthread_mutex_lock(&data->print_mutex);
        printf("%llu %d %s", get_time() - philo->info->start_time, philo->id, "\e[31m died\n");
        return;
    }
}

void check_meals(t_philo **philo)
{
    t_data *data = philo[0]->info;
    if (check_meal(philo) && data->max_meals != -1)
    {
        pthread_mutex_lock(&data->print_mutex);
        return;
    }
}



