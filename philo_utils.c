#include "philosophers.h"

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
