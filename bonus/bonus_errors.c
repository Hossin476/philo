#include "bonus_philo.h"


t_philo **philo_init(t_data *data, sem_t **forks, sem_t *print_sem)
{
    t_philo **philo;
    sem_t *fork_sem;
    int i;

    philo = malloc(sizeof(t_philo *) * data->num_of_philos);
    if (!philo)
        return (NULL);
    i = 0;
    while (i < data->num_of_philos)
    {
        philo[i] = malloc(sizeof(t_philo));
        if (!philo[i])
            return (NULL);
        philo[i]->info = data;
        philo[i]->id = i + 1;
        philo[i]->fork_sem = &forks[i];
        philo[i]->print_sem = print_sem;
        philo[i]->lst_time_eat = get_time();
        philo[i]->nbr_of_meals = 0;
        i++;
    }
    return (philo);
}



