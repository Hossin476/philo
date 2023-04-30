
#ifndef BONUS_PHILO_H
# define BONUS_PHILO_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <fcntl.h>
#include <semaphore.h>

typedef struct		s_data
{
    int				num_of_philos;
    int				time_to_die;
    int				time_to_eat;
    int				time_to_sleep;
    int				max_meals;
    unsigned long long	start_time;
}					t_data;

typedef struct		s_philo
{
    t_data			*info;
    int				id;
    sem_t			*fork_sem;
    sem_t			*print_sem;
    unsigned long long	lst_time_eat;
    int				nbr_of_meals;
}					t_philo;


#endif