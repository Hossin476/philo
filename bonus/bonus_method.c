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