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

void ft_putstr_fd(char *s, int fd)
{
    if (!s)
        return;
    write(fd, s, strlen(s));
}

void ft_putnbr_fd(int n, int fd)
{
    char c;

    if (n == -2147483648)
    {
        ft_putstr_fd("-2147483648", fd);
        return;
    }
    if (n < 0)
    {
        write(fd, "-", 1);
        n = -n;
    }
    if (n >= 10)
    {
        ft_putnbr_fd(n / 10, fd);
        ft_putnbr_fd(n % 10, fd);
    }
    else
    {
        c = n + '0';
        write(fd, &c, 1);
    }
}

void ft_putchar_fd(char c, int fd)
{
    write(fd, &c, 1);
}

int ft_strlen(const char *s)
{
    int i;

    i = 0;
    while (s[i])
        i++;
    return (i);
}


static int	num_length(long nb)
{
	int	l;

	l = 0;
	if (nb == 0)
		l++;
	else if (nb < 0)
	{
		nb = -nb;
		l++;
	}
	while (nb > 0)
	{
		nb = nb / 10;
		l++;
	}
	return (l);
}

char	*ft_itoa(int n)
{
	long	nb;
	char	*ptr;
	int		i;

	nb = n;
	i = num_length(nb);
	ptr = (char *)malloc ((num_length(nb) + 1));
	if (!ptr)
		return (NULL);
	ptr[i--] = '\0';
	if (nb == 0)
		ptr[0] = '0';
	if (nb < 0)
	{
		ptr[0] = '-';
		nb = -nb;
	}
	while (nb > 0)
	{
		ptr[i--] = (nb % 10) + '0';
		nb = nb / 10;
	}
	return (ptr);
}