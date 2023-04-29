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

unsigned long long	get_time(void)
{
    struct timeval	tv;
    unsigned long long	time_in_ms;

    gettimeofday(&tv, NULL);
    time_in_ms = tv.tv_sec * 1000 + tv.tv_usec / 1000;
    return (time_in_ms);
}

void	ft_usleep(int ms)
{
    long long	tm;

    tm = get_time();
    while ((get_time() - tm) <= ms)
        usleep(100);
}

void	ft_putstr_fd(char *s, int fd)
{
    if (!s)
        return ;
    write(fd, s, strlen(s));
}

void	ft_putnbr_fd(int n, int fd)
{
    char	c;

    if (n == -2147483648)
    {
        ft_putstr_fd("-2147483648", fd);
        return ;
    }
    if (n < 0)
    {
        write(fd, "-", 1);
        n = -n;
    }
    if (n >= 10)
    {
        ft_putnbr_fd(n / 10, fd);
        ft_putnbr_fd(n % 10, fd);
    }
    else
    {
        c = n + '0';
        write(fd, &c, 1);
    }
}

void	ft_putchar_fd(char c, int fd)
{
    write(fd, &c, 1);
}

int		ft_strlen(const char *s)
{
    int	i;

    i = 0;
    while (s[i])
        i++;
    return (i);
}

void	ft_printf(t_philo *philo, char *str)
{
    sem_wait(philo->print_sem);
    ft_putnbr_fd((int)(get_time() - philo->info->start_time), 1);
    ft_putstr_fd(" ", 1);
    ft_putnbr_fd(philo->id, 1);
    ft_putstr_fd(str, 1);
    sem_post(philo->print_sem);
}

void	start_data(t_data *data, char **av, int ac)
{
    data->num_of_philos = atoi(av[1]);
    data->time_to_die = atoi(av[2]);
    data->time_to_eat = atoi(av[3]);
    data->time_to_sleep = atoi(av[4]);
    if (ac == 6)
        data->max_meals = atoi(av[5]);
    else
        data->max_meals = -1;
    data->start_time = get_time();
}

t_philo	**philo_init(t_data *data, sem_t **forks, sem_t *print_sem)
{
    t_philo	**philo;
    sem_t	*fork_sem;
    int		i;

    philo = malloc(sizeof(t_philo *) * data->num_of_philos);
    if (!philo)
        return (NULL);
    i = 0;
    while (i < data->num_of_philos)
    {
        philo[i] = malloc(sizeof(t_philo));
        if (!philo[i])
            return (NULL);
        philo[i]->info = data;
        philo[i]->id = i + 1;
        philo[i]->fork_sem = &forks[i];
        philo[i]->print_sem = print_sem;
        philo[i]->lst_time_eat = get_time();
        philo[i]->nbr_of_meals = 0;
        i++;
    }
    return (philo);
}

void	mutex_init(sem_t **forks, t_data *data)
{
    int	i;

    i = 0;
    while (i < data->num_of_philos)
    {
        sem_unlink(ft_itoa(i));
        forks[i] = sem_open(ft_itoa(i), O_CREAT | O_EXCL, 0644, 1);
    i++;
}
}

void	philo_sleeping(t_philo *philo)
{
ft_printf(philo, "is sleeping\n");
ft_usleep(philo->info->time_to_sleep);
}

void	philo_eating(t_philo *philo)
{
sem_wait(philo->fork_sem);
ft_printf(philo, "has taken a fork\n");
sem_wait(philo->fork_sem);
ft_printf(philo, "has taken a fork\n");
ft_printf(philo, "is eating\n");
ft_usleep(philo->info->time_to_eat);
sem_post(philo->fork_sem);
sem_post(philo->fork_sem);
sem_wait(philo->print_sem);
philo->lst_time_eat = get_time();
philo->nbr_of_meals++;
sem_post(philo->print_sem);
}

void	*philo_life(void *philo)
{
t_philo	*ph;

ph = philo;
if (ph->id % 2)
    ft_usleep(200);
while (1)
{
    philo_eating(ph);
    philo_sleeping(ph);
    ft_printf(ph, "is thinking\n");
}
return (NULL);
}

int     check_meal(t_philo **philo)
{
int i;

i = 0;
while (i < philo[0]->info->num_of_philos)
{
    if (philo[i]->nbr_of_meals < philo[0]->info->max_meals || philo[0]->info->max_meals == -1)
        return (0);
    i++;
}
return (1);
}

void	death_checking(t_philo **philo)
{
int	i;

while (1)
{
    i = 0;
    while (i < philo[0]->info->num_of_philos)
    {
        if (get_time() - philo[i]->lst_time_eat > (unsigned long long)philo[0]->info->time_to_die)
        {
            ft_printf(philo[i], "died\n");
            exit(1);
        }
        if (check_meal(philo))
            exit(0);
        i++;
    }
}
}

int	main(int ac, char **av)
{
t_data	*data;
sem_t	**forks;
sem_t	*print_sem;
t_philo	**philo;
int		i;

if (ac != 5 && ac != 6)
    return (printf("Error: invalid number of arguments\n"), 1);
data = malloc(sizeof(t_data));
if (!data)
    return (1);
start_data(data, av, ac);
forks = malloc(sizeof(sem_t *) * data->num_of_philos);
if (!forks)
    return (free(data), 1);
print_sem = sem_open("print_sem", O_CREAT | O_EXCL, 0644, 1);
if (print_sem == SEM_FAILED)
    return (free(data), free(forks), 1);
i = 0;
while (i < data->num_of_philos)
{
    forks[i] = sem_open(ft_itoa(i), 0);
    if (forks[i] == SEM_FAILED)
        return (free(data), free(forks), 1);
    i++;
}
philo = philo_init(data, forks, print_sem);
if (!philo)
    return (free(data), free(forks), sem_close(print_sem), 1);
i = 0;
while (i < data->num_of_philos)
{
    if (forks[i] == SEM_FAILED)
        return (free(data), free(forks), sem_close(print_sem), free_alloc(philo, data->num_of_philos), 1);
    i++;
}
death_checking(philo);
return (0);
}

