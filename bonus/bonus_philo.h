/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_philo.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshail <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 19:22:34 by lshail            #+#    #+#             */
/*   Updated: 2023/05/03 16:04:14 by lshail           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BONUS_PHILO_H
# define BONUS_PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/wait.h>
# include <sys/time.h>
# include <fcntl.h>
# include <signal.h>
# include <pthread.h>
# include <semaphore.h>

typedef struct s_data
{
	int				num_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				max_meals;
	sem_t			*print_semaphore;
	sem_t			*meal_semaphore;
	sem_t			*fork_semaphore;
	unsigned long	start_time;
}	t_data;

typedef struct s_philo
{
	pid_t			pid;
	int				id;
	t_data			*info;
	pthread_t		thread;
	unsigned long	lst_time_eat;
	int				nbr_of_meals;
}	t_philo;

long		ft_atoi(const char *str);
int			check_error(int argc, char **argv);
int			ft_strlen(char *s);
long		check_range(long num, long sign);
long long	get_time(void);
void		init_data(t_data *data, char **av);
void		free_alloc(t_philo **philo, int number);
void		philo_sleeping(t_philo *philo);
void		philo_eating(t_philo *philo);
void		ft_usleep(int ms);
t_philo		**philo_init(t_data *data);
void		philo_life(t_philo *philo);
void		ft_printf(t_philo *philo, char *str);
void		thread_monitoring(t_philo **philo);
void		death_checking(t_philo *philo);
int			check_meal(t_philo *philo);

#endif
