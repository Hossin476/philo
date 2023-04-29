#include "philosophers.h"

long long	get_time(void)
{
	struct timeval	tv;
    gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000ll) + (tv.tv_usec / 1000ll));
}

void	ft_usleep(int ms)
{
	long long	tm;
	tm = get_time();
	while (get_time() - tm <= ms)
		usleep(200);
}

void ft_printf(t_philo *philo, char *str)
{
    pthread_mutex_lock(&philo->info->print_mutex);
    printf("%llu %d %s", get_time() - philo->info->start_time, philo->id, str);
    pthread_mutex_unlock(&philo->info->print_mutex);
}

void free_alloc(t_philo **philo, int number)
{
    int i;
    i = 0;
    while (i < number)
    {
        free(philo[i]);
        i++;
    }
    free(philo);
}