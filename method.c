#include "philosophers.h"

int philo_sleeping(t_philo *philo)
{
    printf("%d ", philo->id);
    printf("is sleeping\n");
    // ft_usleep();
    return (1);
}

int philo_thinking(t_philo *philo)
{
    printf("%d ", philo->info->num_of_philos);
    printf("is thinking\n");
    (void)philo;
    return (1);
}

int philo_eating(t_philo *philo)
{
    printf("is eating\n");
    ft_usleep(philo->info->time_to_eat);
    return (1);
}

void start(t_data *data, char **av, int ac)
{
    int i;

    i = 0;
    data->num_of_philos = ft_atoi(av[1]);
    data->time_to_die = ft_atoi(av[2]);
    data->time_to_eat = ft_atoi(av[3]);
    data->time_to_sleep = ft_atoi(av[4]);
    if (ac == 6)
        data->num_of_eat = ft_atoi(av[5]);
    else
        data->num_of_eat = 0;
    data->philo = malloc(sizeof(t_philo) * data->num_of_philos);
    data->forks_mutex  = malloc(sizeof(pthread_mutex_t) * data->num_of_philos);
}