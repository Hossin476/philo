/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshail <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 19:22:41 by lshail            #+#    #+#             */
/*   Updated: 2023/05/02 19:22:42 by lshail           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus_philo.h"

void philo_sleeping(t_philo *philo)
{
    ft_printf(philo, "is sleeping\n");
    ft_usleep(philo->info->time_to_sleep);
}

void philo_eating(t_philo *philo)
{
    sem_wait(philo->info->fork_semaphore);
    ft_printf(philo, "has taken a fork\n");
    sem_wait(philo->info->fork_semaphore);
    ft_printf(philo, "has taken a fork\n");
    ft_printf(philo, "is eating\n");
    ft_usleep(philo->info->time_to_eat);
    sem_wait(philo->info->meal_semaphore);
    philo->lst_time_eat = get_time();
    philo->nbr_of_meals++;
    sem_post(philo->info->meal_semaphore);
    sem_post(philo->info->fork_semaphore);
    sem_post(philo->info->fork_semaphore);
}

void *routine(void *ph)
{
    t_philo* philo;
    
    philo = ph;
	if (philo->id % 2)
		usleep(200);
	while (1)
	{
        philo_eating(philo);
        philo_sleeping(philo);
		ft_printf(philo, "is thinking\n");
	}   
}

void	philo_life(t_philo *philo)
{

    philo->lst_time_eat = get_time();
    pthread_create(&philo->thread, NULL, &routine, philo);
    pthread_detach(philo->thread);
    death_checking(philo);
}

void thread_monitoring(t_philo **philo)
{
    int i;
    pid_t pid;

    i = -1;
    while (++i < philo[0]->info->num_of_philos)
    {
        pid = fork();
        if (pid == -1)
            exit(1);
        if (pid == 0)
        {
            philo_life(philo[i]);
            exit(0);
        }
        else
            philo[i]->pid = pid;
    }
    i = 0;
    waitpid(-1, NULL, 0);
    kill(0,SIGINT);
}