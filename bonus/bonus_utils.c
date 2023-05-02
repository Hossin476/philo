/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshail <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 19:22:51 by lshail            #+#    #+#             */
/*   Updated: 2023/05/02 19:22:53 by lshail           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus_philo.h"

long long get_time(void)
{
    struct timeval tv;
    unsigned long long time_in_ms;

    gettimeofday(&tv, NULL);
    time_in_ms = tv.tv_sec * 1000 + tv.tv_usec / 1000;
    return (time_in_ms);
}

void ft_usleep(int ms)
{
    long long tm;

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