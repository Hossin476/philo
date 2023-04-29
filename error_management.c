#include "philosophers.h"

long check_range(long num, long sign)
{
    if (num > 2147483647 || num < -2147483648)
    {
        printf("Error\n");
        return (0);
    }
    else
        return (num * sign);
}

long ft_atoi(const char *str)
{
    long i;
    long sign;
    long num;

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

int ft_strlen(char *s)
{
    int i;

    i = 0;
    while (s[i] != '\0')
        i++;
    return (i);
}

void check_error(int argc, char **argv)
{
    int i;
    int j;
    int temp;

    if (argc < 5 || argc > 6)
    {
        printf("Error\n");
    }
    i = 0;
    while (++i < argc)
    {
        j = -1;
        while (argv[i][++j] != '\0')
            if (argv[i][j] > 57 || argv[i][j] < 48)
            {
                printf("Error\n");
            }
        temp = ft_atoi(argv[i]);
        if (temp < 1)
        {
            printf("Error\n");
        }
    }
}

void check_data(t_philo *philo)
{
    if (philo->info->num_of_philos == 1 || philo->info->time_to_die == 0
     || philo->info->time_to_eat == 0 || philo->info->time_to_sleep == 0)
    {
        printf("Error\n");
        free(philo);
    }
}