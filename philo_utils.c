/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshail <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 15:04:02 by lshail            #+#    #+#             */
/*   Updated: 2023/04/30 15:05:30 by lshail           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000ll) + (tv.tv_usec / 1000ll));
}

void	ft_usleep(int ms)
{
	long long	tm;

	tm = get_time();
	while (get_time() - tm < ms)
		usleep(200);
}

void	ft_printf(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->info->print_mutex);
	printf("%llu %d %s", get_time() - philo->info->start_time, philo->id, str);
	pthread_mutex_unlock(&philo->info->print_mutex);
}

void	free_alloc(t_philo **philo, int number)
{
	int	i;

	i = 0;
	while (i < number)
	{
		free(philo[i]);
		i++;
	}
	free(philo);
}

int is_integer(char *arg)
{
    for (int i = 0; arg[i] != '\0'; i++)
    {
        if (arg[i] < '0' || arg[i] > '9')
            return 0;
    }
    return 1;
}