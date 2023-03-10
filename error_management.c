#include "philosophers.h"

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
        exit(1);
    }
    i = 0;
    while (++i < argc)
    {
        j = -1;
        while (argv[i][++j] != '\0')
            if (argv[i][j] > 57 || argv[i][j] < 48)
            {
                printf("Error\n");
                exit(1);
            }
        temp = ft_atoi(argv[i]);
        if (temp < 1)
        {
            printf("Error\n");
            exit(1);
        }
    }
}