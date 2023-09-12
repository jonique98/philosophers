/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumjo <sumjo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 18:53:05 by sumjo             #+#    #+#             */
/*   Updated: 2023/09/12 22:28:21 by sumjo            ###   ########.fr       */
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

void	get_right_fork(t_philo *philo)
{
	while (1)
	{
		pthread_mutex_lock (&(philo->arg->mutex[philo->right_fork]));
		if (philo->arg->fork[philo->right_fork] == 1)
		{
			printf("%d has taken a fork\n", philo->id);
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
	return ;
}

void	get_left_fork(t_philo *philo)
{
	while (1)
	{
		pthread_mutex_lock (&(philo->arg->mutex[philo->left_fork]));
		if (philo->arg->fork[philo->left_fork] == 1)
		{
			printf("%d has taken a fork\n", philo->id);
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
	return ;
}

void	*do_something(void *a)
{
	struct timeval time;
	t_philo *philo = (t_philo *)a;
	int	left_fork = philo->left_fork;
	int	right_fork = philo->right_fork;
	while (1)
	{
		if (philo->id % 2 == 0)
		{
			get_left_fork(philo);
			get_right_fork(philo);
		}
		else
		{
			get_right_fork(philo);
			get_left_fork(philo); 
		}
		gettimeofday(&time, NULL);
		if ((time.tv_sec * 1000 + time.tv_usec / 1000) - philo->end_time > philo->arg->time_to_die)
		{
			printf("%d died\n", philo->id);
			philo->arg->fork[left_fork] = 1;
			philo->arg->fork[right_fork] = 1;
			pthread_mutex_unlock (&(philo->arg->mutex[right_fork]));
			pthread_mutex_unlock (&(philo->arg->mutex[left_fork]));
			return a;
		}
		philo->end_time = time.tv_sec * 1000 + time.tv_usec / 1000;
		printf("%d번 철학자 %ld타임 is eating\n", philo->id, (time.tv_sec * 1000 + time.tv_usec / 1000) - philo->end_time);
		usleep(philo->arg->time_to_eat * 1000);
		pthread_mutex_unlock (&(philo->arg->mutex[right_fork]));
		pthread_mutex_unlock (&(philo->arg->mutex[left_fork]));
		philo->arg->fork[left_fork] = 1;
		philo->arg->fork[right_fork] = 1;
		printf("%d is sleeping\n", philo->id);
		usleep(philo->arg->time_to_sleep * 100);
	}
	return	a;
}

int main(int ac, char **av)
{
	ac = 0;
	t_arg		arg;
	t_philo		*philo;
	pthread_t	*ph;

	ph = malloc(sizeof(ph) * arg.philo_num);
	arg.philo_num = ft_atoi(av[1]);
	arg.time_to_die = ft_atoi(av[2]);
	arg.time_to_eat = ft_atoi(av[3]);
	arg.time_to_sleep = ft_atoi(av[4]);

	philo = malloc(sizeof(t_philo) * arg.philo_num + 1000);
	arg.mutex = malloc(sizeof(pthread_mutex_t) * (arg.philo_num));
	int i = -1;
	while (++i < arg.philo_num + 1)
		pthread_mutex_init(&arg.mutex[i], NULL);
	arg.fork = malloc(sizeof(int) * (arg.philo_num + 1));
	i = -1;
	while (++i < arg.philo_num + 1)
		arg.fork[i] = 1;
	i = -1;
	while (++i < arg.philo_num)
	{
		philo[i].id = i + 1;
		philo[i].left_fork = philo[i].id;
		philo[i].right_fork = (philo[i].id % arg.philo_num) + 1;
		philo[i].arg = &arg;
	}
	struct timeval time;

	gettimeofday(&time, NULL);
	i = -1;
	while (++i < arg.philo_num)
	{
		philo[i].end_time = time.tv_sec * 1000 + time.tv_usec / 1000;
		pthread_create(&ph[i], NULL, do_something, &philo[i]);
	}
	i = 0;
	while (i < arg.philo_num)
	{
		pthread_join(ph[i], NULL);
		i++;
	}
}

// pthread_mutex_t g_mutex;
// int g_cnt;

// void *count(void *arg)
// {
// 	char *name;
// 	int i = 0;

// 	name = (char *)arg;
// 	pthread_mutex_lock(&g_mutex);
// 	g_cnt = 0;
// 	while (i < 13)
// 	{
// 		printf("%s cnt : %d\n", name, g_cnt);
// 		g_cnt++;
// 		usleep(20000);
// 		i++;
// 	}
// 	pthread_mutex_unlock(&g_mutex);
// 	return ((void *)arg);
// }

// int main()
// {
// 	pthread_t pth1 = 0;
// 	pthread_t pth2 = 0;
// 	pthread_t pth3 = 0;

// 	pthread_mutex_init(&g_mutex, NULL);
// 	pthread_create(&pth1, NULL, count, (void *)"thread1");
// 	pthread_create(&pth2, NULL, count, (void *)"thread2");
// 	pthread_create(&pth3, NULL, count, (void *)"thread3");
// 	pthread_join(pth1, NULL);
// 	pthread_join(pth2, NULL);
// 	pthread_join(pth3, NULL);
// 	pthread_mutex_destroy(&g_mutex);
// }
