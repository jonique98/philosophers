/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumjo <sumjo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 21:33:56 by sumjo             #+#    #+#             */
/*   Updated: 2023/09/27 21:48:36 by sumjo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	philo_eat(t_philo *philo)
{
	philo->data->end_time = get_time();
	if (print(philo, "is eating") == FAIL)
		exit (DEAD);
	philo->data->eat_count++;
	catnap(get_time(), philo->arg->time_to_eat * 1000,
		philo->arg->time_to_eat);
}

void	philo_sleep(t_philo *philo)
{
	if (print(philo, "is sleeping") == FAIL)
		exit (DEAD);
	catnap(get_time(), philo->arg->time_to_sleep * 1000,
		philo->arg->time_to_sleep);
}

void	philo_think(t_philo *philo)
{
	if (print(philo, "is thinking") == FAIL)
		exit (DEAD);
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
		drop_forks(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
}
