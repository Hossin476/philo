/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_method.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshail <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 19:22:24 by lshail            #+#    #+#             */
/*   Updated: 2023/05/02 19:22:26 by lshail           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus_philo.h"

int check_meal(t_philo *philo)
{

    int token;

    token = 0;
    if (philo->info->max_meals != -1)
    {
        if (philo->nbr_of_meals < philo->info->max_meals + 1)
            token = 1;
    }
    if (!token)
        return (1);
    return (0);
}

void death_checking(t_philo *philo)
{
    int all_philos_full;
    int i;
    
    all_philos_full = 1;
    i = -1;
    while (1)
    {
        usleep(200);
        sem_wait(philo->info->meal_semaphore);
        if (get_time() - philo->lst_time_eat > (unsigned long) philo->info->time_to_die)
        {
            sem_wait(philo->info->print_semaphore);
            printf("%llu %d died", get_time() - philo->info->start_time, philo->id);
            return;
        }
        if (check_meal(philo) && philo->info->max_meals != -1)
        {
            sem_post(philo->info->meal_semaphore);
            while (++i < philo->info->num_of_philos)
            {
                if (philo->nbr_of_meals < philo->info->max_meals)
                {
                    all_philos_full = 0;
                    break;
                }
            }
            if (all_philos_full)
                return;
            break;
        }
        sem_post(philo->info->meal_semaphore);
    }
}



void init_data(t_data *data, char **av)
{

    data->num_of_philos = ft_atoi(av[1]);
    data->time_to_die = ft_atoi(av[2]);
    data->time_to_eat = ft_atoi(av[3]);
    data->time_to_sleep = ft_atoi(av[4]);
    if (av[5])
        data->max_meals = ft_atoi(av[5]);
    else
        data->max_meals = -1;
    data->start_time = get_time();
    sem_unlink("/print_semaphore");
    sem_unlink("/meal_semaphore");
    sem_unlink("/fork_semaphore");
    data->meal_semaphore = sem_open("/meal_semaphore", O_CREAT, 0644, 1);
    data->print_semaphore = sem_open("/print_semaphore", O_CREAT, 0644, 1);
    data->fork_semaphore = sem_open("/fork_semaphore", O_CREAT, 0644, data->num_of_philos);
}

t_philo **philo_init(t_data *data)
{
    t_philo **philo;
    int i;

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
