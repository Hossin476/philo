#include "bonus_philo.h"


int main(int ac, char **av)
{
    t_data *data;
    sem_t **forks;
    sem_t *print_sem;
    t_philo **philo;
    int i;

    data = malloc(sizeof(t_data));
    if (!data)
        return (1);
    start_data(data, av, ac);
    forks = malloc(sizeof(sem_t *) * data->num_of_philos);
    if (!forks)
        return (free(data), 1);
    print_sem = sem_open("print_sem", O_CREAT | O_EXCL, 0644, 1);
    if (print_sem == SEM_FAILED)
        return (free(data), free(forks), 1);
    i = 0;
    while (i < data->num_of_philos)
    {
        forks[i] = sem_open(ft_atoi(i), 0);
        if (forks[i] == SEM_FAILED)
            return (free(data), free(forks), 1);
        i++;
    }
    philo = philo_init(data, forks, print_sem);
    if (!philo)
        return (free(data), free(forks), sem_close(print_sem), 1);
    i = 0;
    while (i < data->num_of_philos)
    {
        if (forks[i] == SEM_FAILED)
            return (free(data), free(forks), sem_close(print_sem), free_alloc(philo, data->num_of_philos), 1);
        i++;
    }
    death_checking(philo);
    return (0);
}