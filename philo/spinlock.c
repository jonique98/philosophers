/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spinlock.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumjo <sumjo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 04:05:45 by sumjo             #+#    #+#             */
/*   Updated: 2023/09/26 21:38:28 by sumjo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ph.h"

int	get_right_fork(t_philo *philo)
{
	while (1)
	{
		if (dead_check(philo) == DEAD)
			return (FAIL);
		pthread_mutex_lock(&philo->mutex->fork_mutex[philo->data->right_fork]);
		if (philo->mutex->fork[philo->data->right_fork] == 1)
		{
			if (print(philo, "has taken a fork") == FAIL)
				return (DEAD);
			philo->mutex->fork[philo->data->right_fork] = 0;
			pthread_mutex_unlock
			(&philo->mutex->fork_mutex[philo->data->right_fork]);
			break ;
		}
		else
		{
			pthread_mutex_unlock
			(&philo->mutex->fork_mutex[philo->data->right_fork]);
			usleep(100);
		}
	}
	return (0);
}

int	get_left_fork(t_philo *philo)
{
	while (1)
	{
		if (dead_check(philo) == DEAD)
			return (FAIL);
		pthread_mutex_lock (&philo->mutex->fork_mutex[philo->data->left_fork]);
		if (philo->mutex->fork[philo->data->left_fork] == 1)
		{
			if (print(philo, "has taken a fork") == FAIL)
				return (DEAD);
			philo->mutex->fork[philo->data->left_fork] = 0;
			pthread_mutex_unlock
			(&philo->mutex->fork_mutex[philo->data->left_fork]);
			break ;
		}
		else
		{
			pthread_mutex_unlock
			(&philo->mutex->fork_mutex[philo->data->left_fork]);
			usleep(100);
		}
	}
	return (0);
}

int	spin_lock(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		if (get_left_fork(philo) == FAIL)
			return (DEAD);
		if (get_right_fork(philo) == FAIL)
			return (DEAD);
	}
	else
	{
		if (get_right_fork(philo) == FAIL)
			return (DEAD);
		if (get_left_fork(philo) == FAIL)
			return (DEAD);
	}
	return (0);
}
