/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumjo <sumjo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 04:04:39 by sumjo             #+#    #+#             */
/*   Updated: 2023/09/23 21:51:31 by sumjo            ###   ########.fr       */
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

int	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	free_philo(t_philo *philo, int index)
{
	int	i;

	i = -1;
	pthread_mutex_destroy(&philo[0].mutex->dead_mutex);
	while (++i < index)
	{
		pthread_mutex_destroy(&philo[0].mutex->fork_mutex[i]);
		free(philo[i].data);
	}
	ft_free(philo[0].mutex->fork, philo[0].mutex->fork_mutex, philo[0].mutex);
	free(philo[0].arg);
	free(philo);
	system("leaks philo");
	return (0);
}

void	ft_free(void *ptr1, void *ptr2, void *ptr3)
{
	if (ptr1)
		free(ptr1);
	if (ptr2)
		free(ptr2);
	if (ptr3)
		free(ptr3);
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
