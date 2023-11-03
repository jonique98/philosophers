/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumjo <sumjo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 04:07:16 by sumjo             #+#    #+#             */
/*   Updated: 2023/11/03 19:36:19 by sumjo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"ph.h"

int	dead_check(t_philo *philo)
{
	if (philo->mutex->dead == DEAD)
		return (DEAD);
	return (0);
}

int	full_check(t_philo *philo)
{
	if (philo->arg->must_eat != -1)
	{
		philo->data->eat_count++;
		if (philo->data->eat_count == philo->arg->must_eat)
			return (FULL);
	}
	return (0);
}

int	dead(t_philo *philo)
{
	pthread_mutex_lock(&(philo->mutex->dead_mutex));
	if (philo->mutex->dead != DEAD
		&& get_time() - (philo->data->end_time) >= philo->arg->time_to_die)
	{
		philo->mutex->dead = 1;
		printf("%d %d died\n", get_time() - philo->data->start_time,
			philo->id);
		pthread_mutex_unlock(&(philo->mutex->dead_mutex));
		return (DEAD);
	}
	pthread_mutex_unlock(&(philo->mutex->dead_mutex));
	return (0);
}
