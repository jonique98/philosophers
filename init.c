/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumjo <sumjo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 04:08:31 by sumjo             #+#    #+#             */
/*   Updated: 2023/09/17 04:29:40 by sumjo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ph.h"

t_arg	*init_arg(int ac, char **av)
{
	t_arg	*arg;

	arg = malloc(sizeof(t_arg));
	if (arg == 0)
		return (0);
	if (ac == 5 || ac == 6)
	{
		arg->philo_num = ft_atoi(av[1]);
		if (arg->philo_num < 1)
		{
			printf("Error: Wrong number of philosophers\n");
			return (0);
		}
		arg->time_to_die = ft_atoi(av[2]);
		if (arg->time_to_die < 1)
		{
			printf("Error: Wrong time to die\n");
			return (0);
		}
		arg->time_to_eat = ft_atoi(av[3]);
		if (arg->time_to_eat < 1)
		{
			printf("Error: Wrong time to eat\n");
			return (0);
		}
		arg->time_to_sleep = ft_atoi(av[4]);
		if (arg->time_to_sleep < 1)
		{
			printf("Error: Wrong time to sleep\n");
			return (0);
		}
		if (ac == 6)
		{
			arg->must_eat = ft_atoi(av[5]);
			if(arg->must_eat < 1)
			{
				printf("Error: Wrong number of times each philosopher must eat\n");
				return (0);
			}
		}
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

t_data	*init_data(t_arg *arg, int i)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (data == 0)
		return (0);
	data->left_fork = i + 1;
	data->right_fork = (i + 1) % arg->philo_num + 1;
	data->eat_count = 0;
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
		if (philo[i].data == 0)
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
		return (FAIL);
	mutex = init_mutex(arg);
	if (mutex == 0)
	{
		free(arg);
		return (FAIL);
	}
	*philo = malloc(sizeof(t_philo) * arg->philo_num);
	if (*philo == 0)
		return (FAIL);
	init_philo(*philo, arg, mutex);
	return (0);
}
