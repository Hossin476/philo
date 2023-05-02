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

void death_checking(t_philo *philo)
{

    while (1)
    {
            sem_wait(philo->info->meal_semaphore);
            if (get_time() - philo->lst_time_eat > (unsigned long long)philo->info->time_to_die && !philo->info->death_flag)
            {
                philo->info->death_flag = 1;
                sem_wait(philo->info->print_semaphore);
                printf("%llu %d died\n", get_time() - philo->info->start_time, philo->id);
                return;
            }
            sem_post(philo->info->meal_semaphore);
    }
}

void init_data(t_data *data, char **av) 
{

    data->num_of_philos = ft_atoi(av[1]);
    data->time_to_die = ft_atoi(av[2]);
    data->time_to_eat = ft_atoi(av[3]);
    data->time_to_sleep = ft_atoi(av[4]);
    if (av[5])
        data->max_meals = ft_atoi(av[5]); 
	else
		data->max_meals = -1;
    data->start_time = get_time();
    data->death_flag = 0;
    sem_unlink("/print_semaphore");
    sem_unlink("/meal_semaphore");
    sem_unlink("/fork_semaphore");
    data->meal_semaphore = sem_open("/meal_semaphore", O_CREAT, 0644, 1);;
    data->print_semaphore = sem_open("/print_semaphore", O_CREAT, 0644, 1);;
    data->fork_semaphore = sem_open("/fork_semaphore", O_CREAT, 0644, data->num_of_philos);;
}

t_philo **philo_init(t_data *data)
{
    t_philo **philo;
    int i;

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
		i++;
    }
    return (philo);
}