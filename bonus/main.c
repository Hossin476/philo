#include "bonus_philo.h"

int main(int ac, char **av)
{
	t_data *data;
	sem_t *forks;
	t_philo **philo;

	if (!check_error(ac, av))
		return (0);
	data = malloc(sizeof(t_data));
	if (!data)
		return (0);
	init_data(data, av);
	forks = malloc(sizeof(sem_t) * data->num_of_philos);
	if (!forks)
		return (1);
	mutex_init(&forks, data);
	philo = philo_init(data, &forks);
	if (!philo)
		return (1);
	thread_monitoring(philo);
	free(forks);
	// free_alloc(philo, data->num_of_philos);
	return (0);
}