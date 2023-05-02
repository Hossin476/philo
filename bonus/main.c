/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshail <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 19:22:00 by lshail            #+#    #+#             */
/*   Updated: 2023/05/02 19:22:04 by lshail           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus_philo.h"

int main(int ac, char **av)
{
	t_data *data;
	t_philo **philo;

	if (!check_error(ac, av))
		return (0);
	data = malloc(sizeof(t_data));
	if (!data)
		return (0);
	init_data(data, av);
	philo = philo_init(data);
	if (!philo)
		return (1);
	thread_monitoring(philo);
	free_alloc(philo, data->num_of_philos);
	return (0);
}
