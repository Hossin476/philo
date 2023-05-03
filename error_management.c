/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshail <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 14:52:37 by lshail            #+#    #+#             */
/*   Updated: 2023/04/30 15:20:40 by lshail           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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


int check_positive_nonnull(int num)
{
    if (num < 1)
    {
        printf("Error: Arguments must be positive integers non null\n");
        return 0;
    }
    return 1;
}

int	check_error(int argc, char **argv)
{
	int i;

	i = 1;
    if (argc < 5 || argc > 6)
    {
        printf("Error: Invalid number of arguments\n");
        return 0;
    }
    while ( i < argc)
    {
        if (!is_integer(argv[i]))
        {
            printf("Error: Arguments must be integers\n");
            return 0;
        }
        int temp = ft_atoi(argv[i]);
        if (!check_positive_nonnull(temp))
            return (0);
		i++;
    }
    return (1);
}