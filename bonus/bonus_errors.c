#include "bonus_philo.h"

t_philo **philo_init(t_data *data, sem_t **forks)
{
    t_philo **philo;
    sem_t *fork;
    int i;

    fork = *forks;
    i = 0;
    philo = malloc(sizeof(t_philo *) * data->num_of_philos);
    if (!philo)
        return (0);
    while (i < data->num_of_philos)
    {
        philo[i] = malloc(sizeof(t_philo));
        // if (!philo[i])
        //     free_alloc(philo, i);
        philo[i]->info = data;
        philo[i]->id = i + 1;
        philo[i]->fork_semaphore = &fork[i];
        philo[i]->next_fork_semaphore = &(fork[i + 1 % data->num_of_philos]);
        i++;
    }
    return (philo);
}


long	check_range(long num, long sign)
{
	if (num > 2147483647 || num < -2147483648)
	{
		printf("Error\n");
		return (0);
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
	return (check_range(num, sign));
}

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

int	check_error(int argc, char **argv)
{
	int	i;
	int	j;
	int	temp;

	i = 0;
	if (argc < 5 || argc > 6)
	{
		printf("Error: Invalid number of arguments\n");
		return (0);
	}
	while (++i < argc)
	{
		j = -1;
		while (argv[i][++j] != '\0')
		{
			if (argv[i][j] > '9' || argv[i][j] < '0')
			{
				printf("Error: Arguments must be integers\n");
				return (0);
			}
		}
		temp = ft_atoi(argv[i]);
		if (temp < 1)
		{
			printf("Error: Arguments must be positive integers non null\n");
			return (0);
		}
	}
	return (1);
}
