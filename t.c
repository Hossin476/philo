#include <pthread.h>
#include <semaphore.h>

typedef struct	s_info
{
	int				num_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nbr_of_times_each_philo_must_eat;
	sem_t			*fork_semaphore;
	sem_t			*meal_semaphore;
	long long		start_time;
}				t_info;

typedef struct	s_philo
{
	int				id;
	int				nbr_of_meals;
	long long		lst_time_eat;
	pthread_t		thread;
	pid_t			pid;
	t_info			*info;
	pthread_mutex_t	mutex;
}				t_philo;

void	ft_printf(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->mutex);
	printf("%lld %d %s", get_time() - philo->info->start_time, philo->id + 1, msg);
	pthread_mutex_unlock(&philo->mutex);
}

void	philo_sleeping(t_philo *philo)
{
	ft_printf(philo, "is sleeping\n");
	ft_usleep(philo->info->time_to_sleep);
}

void	philo_eating(t_philo *philo)
{
	sem_wait(philo->info->fork_semaphore);
	ft_printf(philo, "has taken a fork\n");
	sem_wait(philo->info->fork_semaphore);
	ft_printf(philo, "has taken a fork\n");
	ft_printf(philo, "is eating\n");
	ft_usleep(philo->info->time_to_eat);
	sem_wait(philo->info->meal_semaphore);
	philo->lst_time_eat = get_time();
	philo->nbr_of_meals++;
	sem_post(philo->info->meal_semaphore);
	sem_post(philo->info->fork_semaphore);
	sem_post(philo->info->fork_semaphore);
}

void	*routine(void *ph)
{
	t_philo	*philo;

	philo = ph;
	if (philo->id % 2)
		usleep(200);
	while (1)
	{
		pthread_mutex_lock(&philo->mutex);
		if (get_time() - philo->lst_time_eat > philo->info->time_to_die)
		{
			ft_printf(philo, "died\n");
			exit(0);
		}
		pthread_mutex_unlock(&philo->mutex);
		philo_eating(philo);
		philo_sleeping(philo);
		ft_printf(philo, "is thinking\n");
	}
}

void	philo_life(t_philo *philo)
{
	philo->lst_time_eat = get_time();
	pthread_create(&philo->thread, NULL, &routine, philo);
	pthread_detach(philo->thread);
}

void	death_checking(t_philo *philo)
{
	while (1)
	{
		pthread_mutex_lock(&philo->mutex);
		if (get_time() - philo->lst_time_eat > philo->info->time_to_die)
		{
			ft_printf(philo, "died\n");
			exit(0);
		}
		pthread_mutex_unlock(&philo->mutex);
		if (philo->info->nbr_of_times_each_philo_must_eat != -1 &&
			philo->nbr_of_meals == philo->info->nbr_of_times_each_philo_must_eat)
			exit(0);
	}
}

void	thread_monitoring(t_philo **philo)
{
	int			i;
	pthread_t	death_thread;

	pthread_mutex_init(&philo[0]->mutex, NULL);
	i = -1;
	while (++i < philo[0]->info->num_of_philos)
	{
		if (pthread_create(&philo[i]->thread, NULL, &routine, philo[i]) != 0)
			exit(1);
		pthread_detach(philo[i]->thread);
	}
	if (pthread_create(&death_thread, NULL, &death_checking, philo[0]) != 0)
		exit(1);
	pthread_join(death_thread, NULL);
}

int	main(int argc, char **argv)
{
	t_info		info;
	t_philo		**philo;

	if (argc < 5 || argc > 6)
{
printf("Error: invalid arguments\n");
return (1);
}
if (!init_info(argc, argv, &info))
return (1);
if (!(philo = init_philos(&info)))
return (1);
thread_monitoring(philo);
cleanup(philo, &info);
return (0);
}