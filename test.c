/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumjo <sumjo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 18:53:05 by sumjo             #+#    #+#             */
/*   Updated: 2023/09/15 23:58:33 by sumjo            ###   ########.fr       */
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

void	drop_fork(t_philo *philo)
{
	pthread_mutex_lock (&(philo->arg->mutex[philo->right_fork]));
	philo->arg->fork[philo->right_fork] = 1;
	pthread_mutex_unlock (&(philo->arg->mutex[philo->right_fork]));
	pthread_mutex_lock (&(philo->arg->mutex[philo->left_fork]));
	philo->arg->fork[philo->left_fork] = 1;
	pthread_mutex_unlock (&(philo->arg->mutex[philo->left_fork]));
}

void	catnap(int t, int limit)
{
	struct timeval	time;
	int				i;
	long			ms;

	i = 0;
	gettimeofday(&time, NULL);
	ms = time.tv_sec * 1000 + time.tv_usec / 1000;
	while (i < 50)
	{
		gettimeofday(&time, NULL);
		if ((time.tv_sec * 1000 + time.tv_usec / 1000) - ms >= limit)
			return ;
		usleep(t / 60);
		i++;
	}
}

int	dead(t_philo *philo)
{
	struct timeval time;

	gettimeofday(&time, NULL);
	if ((time.tv_sec * 1000 + time.tv_usec / 1000 - philo->end_time > philo->arg->time_to_die) ||
		(philo->arg->must_eat != -1 && philo->eat_count >= philo->arg->must_eat))
	{
		philo->arg->dead = 1;
		drop_fork(philo);
		return 1;
	}
	return 0;
}

int	dead_check(t_philo *philo)
{
	if(philo->arg->dead == 1)
		return 1;
	return 0;
}


int	get_right_fork(t_philo *philo)
{
	while (1)
	{
		pthread_mutex_lock (&(philo->arg->mutex[philo->right_fork]));
		if(dead(philo) || dead_check(philo) == FAIL)
		{
			pthread_mutex_unlock(&(philo->arg->mutex[philo->right_fork]));
			return FAIL;
		}
		if (philo->arg->fork[philo->right_fork] == 1)
		{
			gettimeofday(&(philo->time), NULL);
			printf("%ld %d has taken a fork\n", (philo->time.tv_sec * 1000 + philo->time.tv_usec / 1000) - philo->start_time, philo->id);
			philo->arg->fork[philo->right_fork] = 0;
			pthread_mutex_unlock(&(philo->arg->mutex[philo->right_fork]));
			break ;
		}
		else
		{
			pthread_mutex_unlock(&(philo->arg->mutex[philo->right_fork]));
			usleep(100);
		}
	}
	return 0;
}

int	get_left_fork(t_philo *philo)
{
	while (1)
	{
		pthread_mutex_lock (&(philo->arg->mutex[philo->left_fork]));
		if(dead(philo) || dead_check(philo) == FAIL)
		{
			pthread_mutex_unlock(&(philo->arg->mutex[philo->right_fork]));
			return FAIL;
		}
		if (philo->arg->fork[philo->left_fork] == 1)
		{
			gettimeofday(&(philo->time), NULL);
			printf("%ld %d has taken a fork\n", (philo->time.tv_sec * 1000 + philo->time.tv_usec / 1000) - philo->start_time, philo->id);
			philo->arg->fork[philo->left_fork] = 0;
			pthread_mutex_unlock(&(philo->arg->mutex[philo->left_fork]));
			break ;
		}
		else
		{
			pthread_mutex_unlock(&(philo->arg->mutex[philo->left_fork]));
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
			return FAIL;
		if (get_right_fork(philo) == FAIL)
			return FAIL;
	}
	else
	{
		if (get_right_fork(philo) == FAIL)
			return FAIL;
		if (get_left_fork(philo) == FAIL)
			return FAIL;
	}
	return 0;
}

int	philo_eat(t_philo *philo)
{
	gettimeofday(&(philo->time), NULL);
	philo->end_time = philo->time.tv_sec * 1000 + philo->time.tv_usec / 1000;
	if(dead_check(philo) == FAIL)
		return FAIL;
	printf("%ld %d is eating\n", (philo->time.tv_sec * 1000 + philo->time.tv_usec / 1000) - philo->start_time, philo->id);
	philo->eat_count++;
	catnap(philo->arg->time_to_eat * 1000, philo->arg->time_to_eat);
	drop_fork(philo);
	return 0;
}

int	philo_sleep(t_philo *philo)
{
	gettimeofday(&(philo->time), NULL);
	if(dead_check(philo) == FAIL)
		return FAIL;
	printf("%ld %d is sleeping\n", (philo->time.tv_sec * 1000 + philo->time.tv_usec / 1000) - philo->start_time, philo->id);
	catnap(philo->arg->time_to_sleep * 1000, philo->arg->time_to_sleep);
	return 0;
}

int	philo_think(t_philo *philo)
{
	gettimeofday(&(philo->time), NULL);
	if(dead_check(philo) == FAIL)
		return FAIL;
	printf("%ld %d is thinking\n", (philo->time.tv_sec * 1000 + philo->time.tv_usec / 1000) - philo->start_time, philo->id);
	usleep(100);
	return 0;
}

void	*do_something(void *a)
{
	t_philo *philo = (t_philo *)a;
	while (1)
	{
		if (spin_lock(philo) == FAIL)
			return a;
		if (dead(philo) == FAIL)
			return a;
		if (philo_eat(philo) == FAIL)
			return a;
		if (philo_sleep(philo) == FAIL)
			return a;
		if (philo_think(philo) == FAIL)
			return a;
	}
	return a;
}

void	init_arg(t_arg *arg)
{
	int	i;

	arg->mutex = malloc(sizeof(pthread_mutex_t) * (arg->philo_num + 1));
	arg->fork = malloc(sizeof(int) * (arg->philo_num + 1));
	arg->dead = 0;
	i = -1;
	while (++i < arg->philo_num + 1)
		pthread_mutex_init(&arg->mutex[i], NULL);
	i = -1;
	while (++i < arg->philo_num + 1)
		arg->fork[i] = 1;
}

void	init_philo(t_philo *philo, t_arg *arg)
{
	int	i;
	struct timeval time;

	i = -1;
	gettimeofday(&time, NULL);
	while (++i < arg->philo_num)
	{
		philo[i].id = i + 1;
		philo[i].left_fork = philo[i].id;
		philo[i].right_fork = (philo[i].id % arg->philo_num) + 1;
		philo[i].arg = arg;
		philo[i].eat_count = 0;
		philo[i].start_time = time.tv_sec * 1000 + time.tv_usec / 1000;
		philo[i].end_time = time.tv_sec * 1000 + time.tv_usec / 1000;
	}
}

void	philo_create_thread(t_philo *philo, pthread_t *ph)
{
	int	i;

	i = -1;
	while (++i < philo->arg->philo_num)
		pthread_create(&ph[i], NULL, do_something, (void *)&philo[i]);
}

void	philo_thread_join(t_philo *philo, pthread_t *ph)
{
	int	i;

	i = -1;
	while (++i <= philo->arg->philo_num)
		pthread_join(ph[i], NULL);
}

void	parsing(t_arg *arg, int ac, char **av)
{
	if (ac == 5 || ac == 6)
	{
		arg->philo_num = ft_atoi(av[1]);
		if(arg->philo_num < 1)
		{
			printf("Error: Wrong number of philosophers\n");
			exit(1);
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
		exit(1);
	}
}

void	ft_free(t_philo *philo, pthread_t *ph, t_arg arg)
{
	int	i;

	i = -1;
	while (++i < arg.philo_num + 1)
		pthread_mutex_destroy(&arg.mutex[i]);
	free(arg.fork);
	free(philo);
	free(ph);
}

void	*monitoring(void *a)
{
	int		i;
	t_philo	*philo;
	struct timeval time;

	philo = (t_philo *)a;
	while (1)
	{
		i = -1;
		while (++i < philo->arg->philo_num)
		{
			if (philo[i].arg->dead == 1)
			{
				gettimeofday(&time, NULL);
				printf("%ld %d died\n", (time.tv_sec * 1000 + time.tv_usec / 1000) - philo->start_time, philo[i].id);
				return a;
			}
		}
	}
	return a;
}


int main(int ac, char **av)
{
	t_arg		arg;
	t_philo		*philo;
	pthread_t	*ph;
	pthread_t	monitor;

	parsing(&arg, ac, av);
	ph = malloc(sizeof(pthread_t) * (arg.philo_num + 1));
	philo = malloc(sizeof(t_philo) * arg.philo_num);
	if (philo == 0 || ph == 0)
		return (1);
	init_arg(&arg);
	init_philo(philo, &arg);
	pthread_create(&monitor, NULL, monitoring, (void *)philo);
	philo_create_thread(philo, ph);
	philo_thread_join(philo, ph);
	pthread_join(monitor, NULL);
	ft_free(philo, ph, arg);
}
