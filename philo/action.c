/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumjo <sumjo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 04:06:34 by sumjo             #+#    #+#             */
/*   Updated: 2023/12/29 18:57:28 by sumjo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ph.h"

int	philo_eat(t_philo *philo)
{
	if (dead(philo) == DEAD)
		return (DEAD);
	philo->data->end_time = get_time();
	print(philo, "is eating");
	if (full_check(philo) == FULL)
	{
		drop_fork(philo);
		return (FULL);
	}
	catnap(philo, get_time(), philo->arg->time_to_eat * 1000,
		philo->arg->time_to_eat);
	drop_fork(philo);
	return (0);
}

int	philo_sleep(t_philo *philo)
{
	if (dead(philo) == DEAD)
		return (DEAD);
	print(philo, "is sleeping");
	catnap(philo, get_time(), philo->arg->time_to_sleep * 1000,
		philo->arg->time_to_sleep);
	return (0);
}

int philo_think(t_philo *philo)
{
	if (dead(philo) == DEAD)
		return (DEAD);
    print(philo, "is thinking");
    if ((philo->arg->time_to_eat > philo->arg->time_to_sleep)
        && (philo->arg->philo_num % 2 == 1))
        catnap(philo, get_time(), (philo->arg->time_to_eat - philo->arg->time_to_sleep) * 1000, philo->arg->time_to_eat);
    usleep(200);
    return (0);
}

void	catnap(t_philo *philo, int current_time, int t, int limit)
{
	usleep(t / 2);
	if (dead(philo) == DEAD)
		return ;
	while (1)
	{
		if (get_time() - current_time >= limit)
			return ;
		usleep(100);
		if (dead(philo) == DEAD)
			return ;
	}
}

void	drop_fork(t_philo *philo)
{
	pthread_mutex_lock (&(philo->mutex->fork_mutex[philo->data->right_fork]));
	philo->mutex->fork[philo->data->right_fork] = 1;
	pthread_mutex_unlock (&(philo->mutex->fork_mutex[philo->data->right_fork]));
	pthread_mutex_lock (&(philo->mutex->fork_mutex[philo->data->left_fork]));
	philo->mutex->fork[philo->data->left_fork] = 1;
	pthread_mutex_unlock (&(philo->mutex->fork_mutex[philo->data->left_fork]));
}
