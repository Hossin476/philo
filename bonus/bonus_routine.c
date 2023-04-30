#include "bonus_philo.h"

void philo_sleeping(t_philo *philo)
{
    ft_printf(philo, "is sleeping\n");
    ft_usleep(philo->info->time_to_sleep);
}

void philo_eating(t_philo *philo)
{
    sem_wait(philo->fork_sem);
    ft_printf(philo, "has taken a fork\n");
    sem_wait(philo->fork_sem);
    ft_printf(philo, "has taken a fork\n");
    ft_printf(philo, "is eating\n");
    ft_usleep(philo->info->time_to_eat);
    sem_post(philo->fork_sem);
    sem_post(philo->fork_sem);
    sem_wait(philo->print_sem);
    philo->lst_time_eat = get_time();
    philo->nbr_of_meals++;
    sem_post(philo->print_sem);
}

void *philo_life(void *philo)
{
    t_philo *ph;

    ph = philo;
    if (ph->id % 2)
        usleep(200);
    while (1)
    {
        philo_eating(ph);
        philo_sleeping(ph);
        ft_printf(ph, "is thinking\n");
    }
    return;
}

void mutex_init(sem_t **forks, t_data *data)
{
    int i;

    i = 0;
    while (i < data->num_of_philos)
    {
        sem_unlink(ft_itoa(i));
        forks[i] = sem_open(ft_itoa(i), O_CREAT | O_EXCL, 0644, 1);
        i++;
    }
}