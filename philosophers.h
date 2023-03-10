#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>

typedef struct s_philo
{
    int				id;
    // int				eat_count;
    // long long		last_eat;
	struct s_data	*info;
}				t_philo;
typedef struct s_data
{
    int            num_of_philos;
    int            time_to_die;
    int            time_to_eat;
    int            time_to_sleep;
    int            num_of_eat;
                *next_fork;
    pthread_mutex_t *forks_mutex;
    // pthread_mutex_t *print_mutex;
    // pthread_mutex_t *dead_mutex;
    pthread_t		*threads;
	t_philo			**philo;

}				t_data;

long	ft_atoi(const char *str);
void	check_error(int argc, char **argv);
long long	get_time(void);
void	start(t_data *data, char **av, int ac);
int		philo_sleeping(t_philo *philo);
int		philo_thinking(t_philo *philo);
int		philo_eating(t_philo *philo);
void	ft_usleep(int ms);

#endif
