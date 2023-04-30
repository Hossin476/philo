/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   method.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshail <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 14:59:16 by lshail            #+#    #+#             */
/*   Updated: 2023/04/30 15:18:19 by lshail           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	start_data(t_data *data, char **av, int ac)
{
	int	i;

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
	pthread_mutex_init(&data->meal_mutex, NULL);
	pthread_mutex_init(&data->print_mutex, NULL);
}

t_philo	**philo_init(t_data *data, pthread_mutex_t **forks)
{
	t_philo			**philo;
	pthread_mutex_t	*fork;
	int				i;

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
		philo[i]->fork_mutex = &fork[i];
		philo[i]->next_fork = &(fork[i + 1 % data->num_of_philos]);
		i++;
	}
	return (philo);
}

void	mutex_init(pthread_mutex_t *forks, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philos)
	{
		pthread_mutex_init(&forks[i++], NULL);
	}
}

void	thread_monitoring(t_philo **philo)
{
	int	i;

	i = -1;
	while (++i < philo[0]->info->num_of_philos)
		philo[i]->lst_time_eat = get_time();
	i = -1;
	while (++i < philo[0]->info->num_of_philos)
		pthread_create(&philo[i]->th, NULL, &philo_life, philo[i]);
	i = -1;
	while (++i < philo[0]->info->num_of_philos)
		pthread_detach(philo[i]->th);
	death_checking(philo);
}

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
