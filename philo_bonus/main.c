#include "philo_bonus.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <semaphore.h>

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
	
	printf("%d %d %s\n", get_time() - philo->data->start_time, philo->id, str);
	return (0);
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


void	philosophers(t_arg *arg, int id, sem_t *forks, sem_t *binarysemaphore)
{
	t_philo	philo;

	philo.id = id + 1;
	philo.arg = arg;
	philo.data = malloc(sizeof(t_data));
	philo.data->eat_count = 0;
	philo.data->start_time = get_time();
	philo.data->end_time = get_time();

	while (1)
	{
		sem_wait(binarysemaphore);
		sem_wait(forks);
		sem_wait(forks);
		philo_eat(&philo);
		sem_post(binarysemaphore);
		sem_post(forks);
		sem_post(forks);
		philo_sleep(&philo);
		philo_think(&philo);
	}
}


int	create_philosophers(t_arg *arg, int i, sem_t *forks, sem_t *binarysemaphore)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		return (FAIL);
	else if (pid == 0)
	{
		philosophers(arg, i, forks, binarysemaphore);
		exit(0);
	}
	return (0);
}

int main(int ac, char **av)
{
	sem_t *forks;
	sem_t *binarysemaphore;
	t_arg	*arg;
	int	i;	

	arg = malloc(sizeof(t_arg));

	arg = init_arg(ac, av);
	if (arg == 0)
		return (FAIL);

	forks = sem_open("forks", O_CREAT, 0644, arg->philo_num);
	binarysemaphore = sem_open("binarysemaphore", O_CREAT, 0644, 1);

	i = -1;
	while (++i < arg->philo_num)
		create_philosophers(arg, i, forks, binarysemaphore);

	i = -1;
	while (++i < arg->philo_num)
		wait(NULL);
}
