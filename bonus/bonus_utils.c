#include "bonus_philo.h"

unsigned long long get_time(void)
{
    struct timeval tv;
    unsigned long long time_in_ms;

    gettimeofday(&tv, NULL);
    time_in_ms = tv.tv_sec * 1000 + tv.tv_usec / 1000;
    return (time_in_ms);
}

void ft_usleep(int ms)
{
    long long tm;

    tm = get_time();
    while ((get_time() - tm) <= ms)
        usleep(100);
}

int ft_strlen(const char *s)
{
    int i;

    i = 0;
    while (s[i])
        i++;
    return (i);
}

void	ft_printf(t_philo *philo, char *str)
{
	sem_wait(&philo->info->print_semaphore);
	printf("%llu %d %s", get_time() - philo->info->start_time, philo->id, str);
	fflush(stdout);
	sem_post(&philo->info->print_semaphore);
}