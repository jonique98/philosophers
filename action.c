/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josumin <josumin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 04:06:34 by sumjo             #+#    #+#             */
/*   Updated: 2023/09/26 10:28:33 by josumin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ph.h"

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

void	catnap(int t, int limit)
{
	int	i;
	int	ms;

	i = 0;
	ms = get_time();
	while (i < 100)
	{
		usleep(t / 100);
		if (get_time() - ms >= limit)
			return ;
		i++;
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
