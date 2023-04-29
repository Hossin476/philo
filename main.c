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
        return(free(data), 1);
    philo = philo_init(data, &forks);
    mutex_init(forks, data);
    thread_monitoring(philo);
    return 0;
}