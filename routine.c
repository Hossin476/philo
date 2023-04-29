#include "philosophers.h"

void philo_sleeping(t_philo *philo)
{
    ft_printf(philo, "is sleeping\n");
    ft_usleep(philo->info->time_to_sleep * 1000);
}

void philo_eating(t_philo *philo)
{
    pthread_mutex_lock(philo->fork_mutex);
    ft_printf(philo, "has taken a fork\n");
    pthread_mutex_lock(philo->next_fork);
    ft_printf(philo, "has taken a fork\n");
    ft_printf(philo, "is eating\n");
    ft_usleep(philo->info->time_to_eat * 1000);
    pthread_mutex_unlock(philo->fork_mutex);
    pthread_mutex_unlock(philo->next_fork);
    pthread_mutex_lock(&philo->info->meal_mutex);
    philo->lst_time_eat = get_time();
    philo->nbr_of_meals++;
    pthread_mutex_unlock(&philo->info->meal_mutex);
}

void *philo_life(void *philo)
{
    t_philo *ph = philo;

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

void death_checking(t_philo **philo)
{
    int i;
    i = 0;
    t_data *data = philo[0]->info;
    while (1)
    {
    pthread_mutex_lock(&data->meal_mutex);
        if (i == data->num_of_philos)
            i = 0;
        if (get_time() - philo[i]->lst_time_eat > (unsigned long long)data->time_to_die)
        {
            pthread_mutex_lock(&data->print_mutex);
            printf("%llu %d %s", get_time() - philo[i]->info->start_time, philo[i]->id, "died\n");
            return;
        }
        if (check_meal(philo) && data->max_meals != -1)
        {
            pthread_mutex_lock(&data->print_mutex);
            return;
        }
        i++;
    pthread_mutex_unlock(&data->meal_mutex);
    }
}