#include "philo_bonus.h"

int	ft_atoi(const char *str)
{
	int					i;
	int					minus;
	unsigned long long	num;

	i = 0;
	minus = 1;
	num = 0;
	while ((9 <= str[i] && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			minus = -1;
		i++;
	}
	if (!('0' <= str[i] && str[i] <= '9'))
		return (num);
	while ('0' <= str[i] && str[i] <= '9')
	{
		num *= 10;
		num += str[i] - '0';
		i++;
	}
	return (num * minus);
}

int	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	print(t_philo *philo, char *str)
{
	if (sem_wait(philo->semaphores->dead) != -1)
		printf("%d %d %s\n", get_time() - philo->data->start_time, philo->id, str);
	else
		return (FAIL);
	return (0);
}

void	drop_forks(t_philo *philo)
{
	sem_post(philo->semaphores->forks);
	sem_post(philo->semaphores->forks);
}

void	catnap(int current_time, int t, int limit)
{
	usleep(t / 2);
	while (1)
	{
		if (get_time() - current_time >= limit)
			return ;
		usleep(100);
	}
}

int	parsing(char **av, t_arg *arg)
{
	arg->philo_num = ft_atoi(av[1]);
	arg->time_to_die = ft_atoi(av[2]);
	arg->time_to_eat = ft_atoi(av[3]);
	arg->time_to_sleep = ft_atoi(av[4]);
	if (arg->philo_num < 1 || arg->time_to_die < 1 || arg->time_to_eat < 1
		|| arg->time_to_sleep < 1)
	{
		printf("Error: Wrong arguments\n");
		return (FAIL);
	}
	if (av[5])
	{
		arg->must_eat = ft_atoi(av[5]);
		if (arg->must_eat < 1)
		{
			printf("Error: Wrong arguments\n");
			return (FAIL);
		}
	}
	else
		arg->must_eat = -1;
	return (0);
}

t_arg	*init_arg(int ac, char **av)
{
	t_arg	*arg;

	arg = malloc(sizeof(t_arg));
	if (arg == 0)
		return (0);
	if (ac != 5 && ac != 6)
	{
		printf("Error: Wrong number of arguments\n");
		return (0);
	}
	if (parsing(av, arg) == FAIL)
		return (0);
	return (arg);
}

int	philo_eat(t_philo *philo)
{
	philo->data->end_time = get_time();
	if (print(philo, "is eating") == FAIL)
		return (DEAD);
	philo->data->eat_count++;
	catnap(get_time(), philo->arg->time_to_eat * 1000, philo->arg->time_to_eat);
	return (0);
}

int	philo_sleep(t_philo *philo)
{
	if (print(philo, "is sleeping") == FAIL)
		return (DEAD);
	catnap(get_time(), philo->arg->time_to_sleep * 1000, philo->arg->time_to_sleep);
	return (0);
}

int	philo_think(t_philo *philo)
{
	if (print(philo, "is thinking") == FAIL)
		return (DEAD);
	usleep(1000);
	return (0);
}

void	get_left_fork(t_philo *philo)
{
	sem_wait(philo->semaphores->forks);
	if (print(philo, "has taken a fork") == FAIL)
		exit (1);
}

void	get_right_fork(t_philo *philo)
{
	sem_wait(philo->semaphores->forks);
	if (print(philo, "has taken a fork") == FAIL)
		exit (1);
}

int	dead_check(t_philo *philo)
{
	if (get_time() - philo->data->end_time >= philo->arg->time_to_die)
	{
		if (print(philo, "died") == FAIL)
			return (FAIL);
		return (DEAD);
	}
	return (0);
}

void	action(t_philo *philo)
{
	if (philo->id % 2 == 0)
		usleep(1000);
	while (1)
	{
		if (dead_check(philo) == DEAD)
			exit(0);
		get_left_fork(philo);
		get_right_fork(philo);
		philo_eat(philo);
		drop_forks(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
}

void	init_data(t_philo *philo)
{
	philo->data = malloc(sizeof(t_data));
	if (philo->data == 0)
		exit (1);
	philo->data->start_time = get_time();
	philo->data->end_time = 0;
	philo->data->eat_count = 0;
}

int	create_philosophers(t_philo *philo)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		return (FAIL);
	else if (pid == 0)
	{
		init_data(philo);
		action(philo);
		exit(0);
	}
	return (0);
}

t_semaphores *init_semaphores(t_arg *arg)
{
	t_semaphores	*semaphores;

	semaphores = malloc(sizeof(t_semaphores));
	if (semaphores == 0)
		exit (1);
	sem_unlink("/forks");
	sem_unlink("/dead");
	semaphores->forks = sem_open("/forks", O_CREAT, 0644, arg->philo_num);
	semaphores->dead = sem_open("/dead", O_CREAT, 0644, 1);
	return (semaphores);
}

void	init_philo(t_philo **philo, int ac, char **av)
{
	t_arg			*arg;
	t_semaphores	*semaphores;
	int				i;

	arg = init_arg(ac, av);
	semaphores = init_semaphores(arg);
	*philo = malloc(sizeof(t_philo) * arg->philo_num);
	if (*philo == 0)
		exit (1);
	i = -1;
	while (++i < arg->philo_num)
	{
		(*philo)[i].id = i + 1;
		(*philo)[i].arg = arg;
		(*philo)[i].semaphores = semaphores;
	}
}

void	*monitor_death(void *param)
{
	sem_t *dead;
	dead = (sem_t)param;

	sem_wait(dead);
	exit(0);
}

int main(int ac, char **av)
{
	t_philo	*philo;
	pthread_t	monitor;
	int		i;	

	init_philo(&philo, ac, av);
	pthread_create(&monitor, NULL, monitor_death, philo->semaphores->dead);
	i = -1;
	while (++i < philo[0].arg->philo_num)
		create_philosophers(&philo[i]);
	i = -1;
	while (++i < philo[0].arg->philo_num)
		wait(NULL);
}
