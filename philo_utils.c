#include "philosophers.h"

long check_range(long num , long sign){
    if ( num > 2147483647 || num < -2147483648)
    {
        printf("Error\n");
        exit(1);
    }
    else
        return (num * sign);
}

long	ft_atoi(const char *str)
{
	long	i;
	long	sign;
	long	num;

	i = 0;
	sign = 1;
	num = 0;
	if (str[i] == '\0')
		return (i);
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + (str[i] - 48);
		i++;
	}
	return check_range(num, sign);
}

long long	get_time(void)
{
	struct timeval	tv;
    gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000ll) + (tv.tv_usec / 1000ll));
}

void	ft_usleep(int ms)
{
	int	tm;
	tm = get_time();
	while (get_time() - tm < ms)
		usleep(100);
}
