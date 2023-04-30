#include "bonus_philo.h"

int	check_meal(t_philo **philo)
{
	int	i;
	int	token;

	i = 0;
	token = 0;
	if (philo[0]->info->max_meals != -1)
	{
		while (i < philo[0]->info->num_of_philos)
		{
			if (philo[i]->nbr_of_meals < philo[0]->info->max_meals)
				token = 1;
			i++;
		}
	}
	if (!token)
		return (1);
	return (0);
}

void death_checking(t_philo **philo)
{
    int i;

    while (1)
    {
        i = 0;
        while (i < philo[0]->info->num_of_philos)
        {
            if (get_time() - philo[i]->lst_time_eat > philo[i]->info->time_to_die && !philo[i]->info->death_flag)
            {
                philo[i]->info->death_flag = 1;
                ft_printf(philo[i], "died\n");
                return;
            }
            i++;
        }
        if (check_meal(philo))
            break;
    }
}


int	init_data(t_data *data, char **av)
{
	if (check_error(av))
		return (1);
	data->num_of_philos = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		data->num_of_meals = ft_atoi(av[5]);
	else
		data->num_of_meals = -1;
	data->start_time = get_time();
	data->death_flag = 0;
	sem_init(&data->print_semaphore, 0, 1);
	sem_init(&data->meal_semaphore, 0, data->num_of_philos);
	return (0);
}