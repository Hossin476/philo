#include "bonus_philo.h"

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

void mutex_init(sem_t **forks, t_data *data)
{
    int i;

    i = 0;
    while (i < data->num_of_philos)
    {
        sem_unlink(ft_atoi(i));
        forks[i] = sem_open(ft_atoi(i), O_CREAT | O_EXCL, 0644, 1);
        i++;
    }
}

