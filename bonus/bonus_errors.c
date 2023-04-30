#include "bonus_philo.h"

t_philo **philo_init(t_data *data, sem_t **forks)
{
    t_philo **philo;
    sem_t *fork;
    int i;

    fork = *forks;
    i = 0;
    philo = malloc(sizeof(t_philo *) * data->num_of_philos);
    if (!philo)
        return (0);
    while (i < data->num_of_philos)
    {
        philo[i] = malloc(sizeof(t_philo));
        if (!philo[i])
            free_alloc(philo, i);
        philo[i]->info = data;
        philo[i]->id = i + 1;
        philo[i]->fork_semaphore = &fork[i];
        philo[i]->next_fork_semaphore = &(fork[i + 1 % data->num_of_philos]);
        i++;
    }
    return (philo);
}


int	ft_isdigit_str(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}


int	check_error(char **av)
{
	int	i;
	int	len;

	i = 1;
	while (i <= 4)
	{
		len = ft_strlen(av[i]);
		if (!ft_isdigit_str(av[i]) || len == 0)
			return (1);
		i++;
	}
	if (av[5])
	{
		len = ft_strlen(av[5]);
		if (!ft_isdigit_str(av[5]) || len == 0)
			return (1);
	}
	return (0);
}
