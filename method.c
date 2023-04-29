#include "philosophers.h"

int philo_sleeping(t_philo *philo)
{
    printf("%d ", philo->id);
    printf("is sleeping\n");
    return (1);
}

int philo_thinking(t_philo *philo)
{
    printf("%d ", philo->info->num_of_philos);
    printf("is thinking\n");
    return (1);
}

int philo_eating(t_philo *philo)
{
    printf("is eating\n");
    ft_usleep(philo->info->time_to_eat);
    return (1);
}

void start_data(t_data *data, char **av, int ac)
{
    int i;

    i = 0;
    data->num_of_philos = ft_atoi(av[1]);
    data->time_to_die = ft_atoi(av[2]);
    data->time_to_eat = ft_atoi(av[3]);
    data->time_to_sleep = ft_atoi(av[4]);
    if (ac == 6)
        data->max_meals = ft_atoi(av[5]);
    else
        data->max_meals = -1;
    data->start_time = get_time();
    pthread_mutex_init(data->meal_mutex, NULL);
    pthread_mutex_init(data->print_mutex, NULL);
}

void free_alloc(t_philo **philo, int number)
{
    int i;
    i = 0;
    while (i < number)
    {
        free(philo[i]);
        i++;
    }
}

t_philo **philo_init(t_data *data, pthread_mutex_t **forks)
{
    t_philo **philo;
    pthread_mutex_t *fork;

    fork = *forks;
    philo = malloc(sizeof(t_philo *) * data->num_of_philos);
    if (!philo)
        return (NULL);
    int i = 0;
    while (i < data->num_of_philos)
    {
        philo[i] = malloc(sizeof(t_philo));
        if (!philo[i])
            free_alloc(philo, i);
        philo->info = data;
        philo->id = i + 1;
        philo->fork_mutex = &fork[i];
        philo->next_fork = &(fork[i + 1] % data->num_of_philos);
        i++;
    }
    return (philo);
}

void mutex_init(pthread_mutex_t **forks, t_data *data)
{
    int i;
    i = 0;

    while (i < data->num_of_philos)
    {
        pthread_mutex_init(&forks[i], NULL);
        i++;
    }
}