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

void	ft_putnbr(long long n)
{
	char	c;

	if (n >= 10)
		ft_putnbr(n / 10);
	c = '0' + n % 10;
	write(1, &c, 1);
}

void	ft_putstr(char *str)
{
	while (*str)
		write(1, str++, 1);
}

void	ft_print_time(t_philo *philo)
{
	long long	time;
	char		s[20];
	int			i;

	time = get_time() - philo->info->start_time;
	i = 0;
	while (time > 0)
	{
		s[i++] = (time % 10) + '0';
		time /= 10;
	}
	while (i < 10)
		s[i++] = ' ';
	s[i] = '\0';
	ft_putstr(s);
}

void	ft_printf(t_philo *philo, char *str)
{
	sem_wait(&philo->info->print_semaphore);
	ft_print_time(philo);
	write(1, " ", 1);
	ft_putnbr(philo->id);
	write(1, " ", 1);
	ft_putstr(str);
	sem_post(&philo->info->print_semaphore);
}