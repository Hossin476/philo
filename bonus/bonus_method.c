#include "bonus_philo.h"


int check_meal(t_philo **philo)
{
    int i;

    i = 0;
    while (i < philo[0]->info->num_of_philos)
    {
        if (philo[i]->nbr_of_meals < philo[0]->info->max_meals || philo[0]->info->max_meals == -1)
            return (0);
        i++;
    }
    return (1);
}

void death_checking(t_philo **philo)
{
    int i;

    while (1)
    {
        i = 0;
        while (i < philo[0]->info->num_of_philos)
        {
            if (get_time() - philo[i]->lst_time_eat > (unsigned long long)philo[0]->info->time_to_die)
            {
                ft_printf(philo[i], "died\n");
                exit(1);
            }
            if (check_meal(philo))
                exit(0);
            i++;
        }
    }
}

void ft_printf(t_philo *philo, char *str)
{
    sem_wait(philo->print_sem);
    ft_putnbr_fd((int)(get_time() - philo->info->start_time), 1);
    ft_putstr_fd(" ", 1);
    ft_putnbr_fd(philo->id, 1);
    ft_putstr_fd(str, 1);
    sem_post(philo->print_sem);
}


void start_data(t_data *data, char **av, int ac)
{
    data->num_of_philos = atoi(av[1]);
    data->time_to_die = atoi(av[2]);
    data->time_to_eat = atoi(av[3]);
    data->time_to_sleep = atoi(av[4]);
    if (ac == 6)
        data->max_meals = atoi(av[5]);
    else
        data->max_meals = -1;
    data->start_time = get_time();
}