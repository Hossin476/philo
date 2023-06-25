/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshail <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 14:57:52 by lshail            #+#    #+#             */
/*   Updated: 2023/05/05 16:03:16 by lshail           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	destroy_mutexes(t_data *data, t_philo **philo)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->meal_mutex);
	while (i < data->num_of_philos)
	{
		pthread_mutex_destroy(&philo[0]->fork_mutex[i]);
		i++;
	}
}

int	main(int ac, char **av)
{
	t_data			*data;
	pthread_mutex_t	*forks;
	t_philo			**philo;

	if (!check_error(ac, av))
		return (0);
	data = malloc(sizeof(t_data));
	if (!data)
		return (0);
	start_data(data, av, ac);
	forks = malloc(sizeof(pthread_mutex_t) * data->num_of_philos);
	if (!forks)
		return (free(data), 1);
	philo = philo_init(data, &forks);
	if (!philo)
		return (free(forks), free(data), 1);
	mutex_init(forks, data);
	thread_monitoring(philo);
	free_alloc(philo, data->num_of_philos);
	destroy_mutexes(data, philo);
	return (0);
}
