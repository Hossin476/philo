#include "philosophers.h"

int main(int ac, char **av)
{

    t_data *data;

// printf("%lld\n", get_time());
    check_error(ac, av);
    data = malloc(sizeof(t_data));
    start(data, av, ac);
    philo_thinking(data->philo[0]);
    // philo_sleeping(data->philo[0]);
    return 0;
}
