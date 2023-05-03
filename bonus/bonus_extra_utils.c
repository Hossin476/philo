/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_extra_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshail <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 18:44:57 by lshail            #+#    #+#             */
/*   Updated: 2023/05/03 18:45:00 by lshail           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus_philo.h"

void check_for_death(t_philo *philo)
{
    if (get_time() - philo->lst_time_eat
        > (unsigned long) philo->info->time_to_die)
    {
        sem_wait(philo->info->print_semaphore);
        printf("%llu %d died", get_time() - philo->info->start_time,
            philo->id);
        return;
    }
}

int check_if_all_philos_full(t_philo *philo)
{
    int all_philos_full;
int i;
i = 0;
	all_philos_full = 1;
    while (i < philo->info->num_of_philos)
    {
        if (philo->nbr_of_meals < philo->info->max_meals)
        {
            all_philos_full = 0;
            break;
        }
		i++;
    }
    return all_philos_full;
}


int is_valid_argument(char *arg)
{
    int i = 0;
    while (arg[i] != '\0')
    {
        if (arg[i] < '0' || arg[i] > '9')
            return 0;
        i++;
    }
    return 1;
}
