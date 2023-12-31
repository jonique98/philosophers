/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumjo <sumjo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 21:35:23 by sumjo             #+#    #+#             */
/*   Updated: 2023/11/03 21:17:55 by sumjo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

t_semaphores	*init_semaphores(t_arg *arg)
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

t_philo	*init_philo(pid_t **pid_list, int ac, char **av)
{
	t_arg			*arg;
	t_semaphores	*semaphores;
	t_philo			*philo;

	arg = init_arg(ac, av);
	semaphores = init_semaphores(arg);
	*pid_list = malloc(sizeof(pid_t) * arg->philo_num);
	if (pid_list == 0)
		exit (1);
	philo = malloc(sizeof(t_philo));
	if (philo == 0)
		exit (1);
	init_data(philo);
	philo->arg = arg;
	philo->semaphores = semaphores;
	return (philo);
}

void	init_data(t_philo *philo)
{
	int	time;

	philo->data = malloc(sizeof(t_data));
	if (philo->data == 0)
		exit (1);
	time = get_time();
	philo->data->start_time = time;
	philo->data->end_time = time;
	philo->data->eat_count = 0;
}

t_arg	*init_arg(int ac, char **av)
{
	t_arg	*arg;

	arg = malloc(sizeof(t_arg));
	if (arg == 0)
		exit(1);
	if (ac != 5 && ac != 6)
	{
		printf("Error: Wrong number of arguments\n");
		exit(1);
	}
	parsing(av, arg);
	return (arg);
}

void	parsing(char **av, t_arg *arg)
{
	arg->philo_num = ft_atoi(av[1]);
	arg->time_to_die = ft_atoi(av[2]);
	arg->time_to_eat = ft_atoi(av[3]);
	arg->time_to_sleep = ft_atoi(av[4]);
	if (arg->philo_num < 1 || arg->time_to_die < 1 || arg->time_to_eat < 1
		|| arg->time_to_sleep < 1)
	{
		printf("Error: Wrong arguments\n");
		exit(1);
	}
	if (av[5])
	{
		arg->must_eat = ft_atoi(av[5]);
		if (arg->must_eat < 1)
		{
			printf("Error: Wrong arguments\n");
			exit(1);
		}
	}
	else
		arg->must_eat = -1;
}
