/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshail <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 19:22:51 by lshail            #+#    #+#             */
/*   Updated: 2023/05/03 15:59:46 by lshail           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus_philo.h"

long long	get_time(void)
{
	struct timeval		tv;
	unsigned long long	time_in_ms;

	gettimeofday(&tv, NULL);
	time_in_ms = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (time_in_ms);
}

void	ft_usleep(int ms)
{
	long long	tm;

	tm = get_time();
	while (get_time() - tm < ms)
		usleep(100);
}

void	ft_printf(t_philo *philo, char *str)
{
	sem_wait(philo->info->print_semaphore);
	printf("%lld %d %s", get_time() - philo->info->start_time, philo->id, str);
	sem_post(philo->info->print_semaphore);
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


t_philo	**philo_init(t_data *data)
{
	t_philo	**philo;
	int		i;

	i = 0;
	philo = malloc(sizeof(t_philo *) * data->num_of_philos);
	if (!philo)
		return (0);
	while (i < data->num_of_philos)
	{
		philo[i] = malloc(sizeof(t_philo));
		if (!philo[i])
			free_alloc(philo, i);
		philo[i]->info = data;
		philo[i]->id = i + 1;
		i++;
	}
	return (philo);
}