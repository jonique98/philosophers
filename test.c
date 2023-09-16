/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumjo <sumjo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 18:53:05 by sumjo             #+#    #+#             */
/*   Updated: 2023/09/17 03:12:03 by sumjo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ph.h"

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

int	dead_check(t_philo *philo);

void	drop_fork(t_philo *philo)
{
	pthread_mutex_lock (&(philo->mutex->fork_mutex[philo->data->right_fork]));
	philo->mutex->fork[philo->data->right_fork] = 1;
	pthread_mutex_unlock (&(philo->mutex->fork_mutex[philo->data->right_fork]));
	pthread_mutex_lock (&(philo->mutex->fork_mutex[philo->data->left_fork]));
	philo->mutex->fork[philo->data->left_fork] = 1;
	pthread_mutex_unlock (&(philo->mutex->fork_mutex[philo->data->left_fork]));
}

long	get_time()
{
	struct timeval time;
	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}


void	catnap(int t, int limit)
{
	int				i;
	long			ms;

	i = 0;
	ms = get_time();
	while (i < 50)
	{
		if (get_time() - ms >= limit)
			return ;
		usleep(t / 50);
		i++;
	}
}

// int	dead(t_philo *philo)
// {
// 	pthread_mutex_lock(&(philo->arg->dead_mutex));
// 	if ((get_time() - philo->end_time > philo->arg->time_to_die) ||
// 		(philo->arg->must_eat != -1 && philo->eat_count >= philo->arg->must_eat))
// 	{
// 		printf("%ld %d died\n", get_time() - philo->arg->start_time, philo->id);
// 		philo->arg->dead = 1;
// 		pthread_mutex_unlock(&(philo->arg->dead_mutex));
// 		drop_fork(philo);
// 		return 1;
// 	}
// 	pthread_mutex_unlock(&(philo->arg->dead_mutex));
// 	return 0;
// }

int	dead_check(t_philo *philo)
{
	pthread_mutex_lock(&(philo->mutex->dead_mutex));
	if (philo->mutex->dead == DEAD)
	{
		pthread_mutex_unlock(&(philo->mutex->dead_mutex));
		return (DEAD);
	}
	pthread_mutex_unlock(&(philo->mutex->dead_mutex));
	return (0);
}

int	print(t_philo *philo, char *str)
{
	if (dead_check(philo) == DEAD)
		return (FAIL);
	printf("%ld %d %s", get_time() - philo->data->start_time, philo->id, str);
	return (0);
}

int	get_right_fork(t_philo *philo)
{
	while (1)
	{
		if (dead_check(philo) == DEAD)
			return (FAIL);
		pthread_mutex_lock (&(philo->mutex->fork_mutex[philo->data->right_fork]));
		if (philo->mutex->fork[philo->data->right_fork] == 1)
		{
			if (print(philo, "has taken a fork\n") == FAIL)
				return (DEAD);
			philo->mutex->fork[philo->data->right_fork] = 0;
			pthread_mutex_unlock(&(philo->mutex->fork_mutex[philo->data->right_fork]));
			break ;
		}
		else
		{
			pthread_mutex_unlock(&(philo->mutex->fork_mutex[philo->data->right_fork]));
			usleep(100);
		}
	}
	return 0;
}

int	get_left_fork(t_philo *philo)
{
	while (1)
	{
		if (dead_check(philo) == 1)
			return 1;
		pthread_mutex_lock (&(philo->mutex->fork_mutex[philo->data->left_fork]));
		if (philo->mutex->fork[philo->data->left_fork] == 1)
		{
			if (print(philo, "has taken a fork\n") == FAIL)
				return (DEAD);
			philo->mutex->fork[philo->data->left_fork] = 0;
			pthread_mutex_unlock(&(philo->mutex->fork_mutex[philo->data->left_fork]));
			break ;
		}
		else
		{
			pthread_mutex_unlock(&(philo->mutex->fork_mutex[philo->data->left_fork]));
			usleep(100);
		}
	}
	return 0;
}

int	spin_lock(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		if (get_left_fork(philo) == FAIL)
			return DEAD;
		if (get_right_fork(philo) == FAIL)
			return DEAD;
	}
	else
	{
		if (get_right_fork(philo) == FAIL)
			return DEAD;
		if (get_left_fork(philo) == FAIL)
			return DEAD;
	}
	return 0;
}

int	philo_eat(t_philo *philo)
{
	philo->data->end_time = get_time();
	if (print(philo, "is eating\n") == FAIL)
		return (DEAD);
	philo->data->eat_count++;
	catnap(philo->arg->time_to_eat * 1000, philo->arg->time_to_eat);
	drop_fork(philo);
	return (0);
}

int	philo_sleep(t_philo *philo)
{
	if (print(philo, "is sleeping\n") == FAIL)
		return (DEAD);
	catnap(philo->arg->time_to_sleep * 1000, philo->arg->time_to_sleep);
	return (0);
}

int	philo_think(t_philo *philo)
{
	if (print(philo, "is thinking\n") == FAIL)
		return (DEAD);
	usleep(100);
	return (0);
}

void	*do_something(void *a)
{
	t_philo *philo;

	philo = (t_philo *)a;
	while (1)
	{
		if (dead_check(philo) == DEAD)
			break;
		spin_lock(philo);
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	return (a);
}

void	philo_create_thread(t_philo *philo)
{
	pthread_t	ph[philo->arg->philo_num];
	int			i;

	i = -1;
	while (++i < philo->arg->philo_num)
		pthread_create(&ph[i], NULL, do_something, (void *)&philo[i]);
	i = -1;
	while (++i < philo->arg->philo_num)
		pthread_join(ph[i], NULL);
}

t_arg *init_arg(int ac, char **av)
{
	t_arg *arg;

	arg = malloc(sizeof(t_arg));
	if (arg == 0)
		return 0;
	if (ac == 5 || ac == 6)
	{
		arg->philo_num = ft_atoi(av[1]);
		if (arg->philo_num < 1)
		{
			printf("Error: Wrong number of philosophers\n");
			return (0);
		}
		arg->time_to_die = ft_atoi(av[2]);
		arg->time_to_eat = ft_atoi(av[3]);
		arg->time_to_sleep = ft_atoi(av[4]);
		if (ac == 6)
			arg->must_eat = ft_atoi(av[5]);
		else
			arg->must_eat = -1;
	}
	else
	{
		printf("Error: Wrong number of arguments\n");
		return (0);
	}
	return (arg);
}

void	ft_free(t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < philo[0].arg->philo_num + 1)
		pthread_mutex_destroy(&philo->mutex->fork_mutex[i]);
}

void	*monitoring(void *a)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)a;
	while (1)
	{
		i = -1;
		while (++i < philo[0].arg->philo_num)
		{
			pthread_mutex_lock(&(philo[i].mutex->dead_mutex));
			if (philo[i].mutex->dead == 1)
			{
				pthread_mutex_unlock(&(philo[i].mutex->dead_mutex));
				return (a);
			}
			if (get_time() - (philo[i].data->end_time) > philo[i].arg->time_to_die)
			{
				philo[i].mutex->dead = 1;
				pthread_mutex_unlock(&(philo[i].mutex->dead_mutex));
				printf ("%ld %d died\n", get_time() - philo[i].data->start_time, philo[i].id);
				return (a);
			}
			pthread_mutex_unlock(&(philo[i].mutex->dead_mutex));
		}
	}
	return a;
}

t_data	*init_data(t_arg *arg, int i)
{
	t_data	*data;
	long	ms;

	data = malloc(sizeof(t_data));
	if (data == 0)
		return (0);
	data->left_fork = i + 1;
	data->right_fork = (i + 1) % arg->philo_num + 1;
	data->eat_count = 0;
	ms = get_time();
	data->start_time = ms;
	data->end_time = ms;
	return (data);
}

t_mutex	*init_mutex(t_arg *arg)
{
	t_mutex	*mutex;
	int		i;

	mutex = malloc(sizeof(t_mutex));
	if (mutex == 0)
		return (0);
	mutex->dead = 0;
	pthread_mutex_init(&(mutex->dead_mutex), NULL);
	mutex->fork = malloc(sizeof(pthread_mutex_t) * (arg->philo_num + 1));
	if (mutex->fork == 0)
	{
		free(mutex);
		return (0);
	}
	mutex->fork_mutex = malloc(sizeof(pthread_mutex_t) * (arg->philo_num + 1));
	i = 0;
	while (++i < arg->philo_num + 1)
	{
		mutex->fork[i] = 1;
		pthread_mutex_init(&(mutex->fork_mutex[i]), NULL);
	}
	return (mutex);
}

int	init_philo(t_philo *philo, t_arg *arg, t_mutex *mutex)
{
	int	i;

	i = -1;
	while (++i < arg->philo_num)
	{
		philo[i].id = i + 1;
		philo[i].arg = arg;
		philo[i].mutex = mutex;
		philo[i].data = init_data(arg, i);
		if(philo[i].data == 0)
		{
			ft_free(philo);
			return (FAIL);
		}
	}
	return (0);
}

int	init(t_philo **philo, int ac, char **av)
{
	t_arg	*arg;
	t_mutex	*mutex;

	arg = init_arg(ac, av);
	if (arg == 0)
		return FAIL;
	mutex = init_mutex(arg);
	if (mutex == 0)
	{
		free(arg);
		return FAIL;
	}
	*philo = malloc(sizeof(t_philo) * arg->philo_num);
	if (*philo == 0)
		return FAIL;
	init_philo(*philo, arg, mutex);
	return 0;
}

void	monitor(t_philo *philo)
{
	pthread_t	thread;

	pthread_create(&thread, NULL, monitoring, (void *)philo);
	pthread_join(thread, NULL);
}


int main(int ac, char **av)
{
	t_philo		*philo;

	if (init(&philo, ac, av) == FAIL)
		return (1);
	philo_create_thread(philo);
	monitor(philo);
	ft_free(philo);
	return 0;
}
