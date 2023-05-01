#include "bonus_philo.h"

void philo_sleeping(t_philo *philo)
{
    ft_printf(philo, "is sleeping\n");
    ft_usleep(philo->info->time_to_sleep);
}

void philo_eating(t_philo *philo)
{
    sem_wait(philo->fork_semaphore);
    ft_printf(philo, "has taken a fork\n");
    ft_printf(philo, "is eating\n");
    ft_usleep(philo->info->time_to_eat);
    sem_wait(philo->info->meal_semaphore);
    philo->lst_time_eat = get_time();
    philo->nbr_of_meals++;
    sem_post(philo->info->meal_semaphore);
    sem_post(philo->fork_semaphore);
}

void	philo_life(t_philo *philo)
{
    t_philo	*ph;

    ph = philo;
	if (ph->id % 2)
		usleep(200);
	while (1)
	{
        philo_eating(philo);
        philo_sleeping(philo);
		ft_printf(philo, "is thinking\n");
		if (philo->info->death_flag)
			exit(0);
	}
}

void mutex_init(sem_t **forks, t_data *data) {
    int i;

    i = 0;
    while (i < data->num_of_philos) {
        sem_t *fork_sem = sem_open("fork_semaphore", O_CREAT, 0644, 1);
        if (fork_sem == SEM_FAILED)
            exit(1);
        forks[i++] = fork_sem;
    }
}


void thread_monitoring(t_philo **philo)
{
    int i;
    pid_t pid;

    i = -1;
    while (++i < philo[0]->info->num_of_philos)
        philo[i]->lst_time_eat = get_time();
    i = -1;
    while (++i < philo[0]->info->num_of_philos)
    {
        pid = fork();
        if (pid == -1)
            exit(EXIT_FAILURE);
        if (pid == 0)
            philo_life(philo[i]);
        else
            philo[i]->pid = pid;
    }
    death_checking(philo);
    i = 0;
    while (i < philo[0]->info->num_of_philos)
    {
        kill(philo[i]->pid, SIGKILL);
        i++;
    }
}