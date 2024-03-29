/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshail <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 15:10:29 by lshail            #+#    #+#             */
/*   Updated: 2023/05/05 16:21:10 by lshail           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>

typedef struct s_data
{
	int				num_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				max_meals;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	meal_mutex;
	unsigned long	start_time;
}	t_data;

typedef struct s_philo
{
	pthread_t		th;
	int				id;
	t_data			*info;
	pthread_mutex_t	*next_fork;
	pthread_mutex_t	*fork_mutex;
	unsigned long	lst_time_eat;
	int				nbr_of_meals;
}	t_philo;

long		ft_atoi(const char *str);
void		destroy_mutexes(t_data *data, t_philo **philo);
int			check_error(int argc, char **argv);
long long	get_time(void);
int			check_positive_nonnull(int num);
int			is_integer(char *arg);
int			check_death(t_philo *philo);
void		start_data(t_data *data, char **av, int ac);
void		free_alloc(t_philo **philo, int number);
void		philo_sleeping(t_philo *philo);
void		philo_eating(t_philo *philo);
void		ft_usleep(int ms);
t_philo		**philo_init(t_data *data, pthread_mutex_t **forks);
void		mutex_init(pthread_mutex_t *forks, t_data *data);
void		thread_monitoring(t_philo **philo);
void		*philo_life(void *philo);
void		ft_printf(t_philo *philo, char *str);
void		thread_monitoring(t_philo **philo);
void		death_checking(t_philo **philo);
int			check_meal(t_philo **philo);
#endif
