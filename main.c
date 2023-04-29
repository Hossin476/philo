#include "philosophers.h"


int main(int ac, char **av)
{
    t_data *data;
    pthread_mutex_t *forks;
    t_philo **philo;

    check_error(ac, av);
    data = malloc(sizeof(t_data));
    if (!data)
        exit(0);
    start_data(data, av, ac);
    forks = malloc(sizeof(pthread_mutex_t) * data->num_of_philos);
    if (!forks) 
        return (free(data),1);
    philo = philo_init(data, &forks);
    if (!philo) 
        return (free(forks),free(data),1);
    mutex_init(forks, data);
    thread_monitoring(philo);
    free(data);
    free(forks);
    free_alloc(philo, data->num_of_philos);
    return (0);
}
