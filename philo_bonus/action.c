/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumjo <sumjo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 21:33:56 by sumjo             #+#    #+#             */
/*   Updated: 2023/11/03 18:19:22 by sumjo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	philo_eat(t_philo *philo)
{
	philo->data->end_time = get_time();
	print(philo, "is eating");
	if (full_check(philo) == FULL)
	{
		drop_forks(philo);
		exit(0);
	}
	catnap(get_time(), philo->arg->time_to_eat * 1000,
		philo->arg->time_to_eat);
	drop_forks(philo);
}

void	philo_sleep(t_philo *philo)
{
	print(philo, "is sleeping");
	catnap(get_time(), philo->arg->time_to_sleep * 1000,
		philo->arg->time_to_sleep);
}

void	philo_think(t_philo *philo)
{
	print(philo, "is thinking");
	usleep(100);
}

void	action(t_philo *philo)
{
	pthread_t	monitor;

	pthread_create(&monitor, NULL, (void *)monitoring, philo);
	if (philo->id % 2 == 0)
		usleep(100);
	while (1)
	{
		get_left_fork(philo);
		get_right_fork(philo);
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
}
