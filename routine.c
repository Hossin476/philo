#include "philosophers.h"


void philo_sleeping(t_philo *philo)
{
    ft_printf(philo, "is sleeping\n");
    ft_usleep(philo->info->time_to_sleep);
}

void philo_eating(t_philo *philo)
{
    pthread_mutex_lock(philo->fork_mutex);
    ft_printf(philo, "has taken a fork\n");
    pthread_mutex_lock(philo->next_fork);
    ft_printf(philo, "has taken a fork\n");
    ft_printf(philo, "is eating\n");
    ft_usleep(philo->info->time_to_eat);
    pthread_mutex_unlock(philo->fork_mutex);
    pthread_mutex_unlock(philo->next_fork);
    pthread_mutex_lock(philo->info->meal_mutex);
    philo->lst_time_eat = get_time();
    philo->nbr_of_meals++;
    pthread_mutex_unlock(philo->info->meal_mutex);
}

void *philo_life(void *philo)
{
    t_philo *ph = philo;
    // t_data *data = ph->info;

    if (ph->id % 2)
        usleep(200);
    while (1)
    {
        philo_eating(ph);
        philo_sleeping(ph);
        ft_printf(ph, "is thinking\n");
    }
    return (NULL);
}