/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumjo <sumjo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 04:07:16 by sumjo             #+#    #+#             */
/*   Updated: 2023/10/04 20:29:30 by sumjo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"ph.h"

int	dead_and_full_check(t_philo *philo)
{
	pthread_mutex_lock(&(philo->mutex->dead_mutex));
	if (philo->full == DEAD || philo->mutex->dead == DEAD)
	{
		pthread_mutex_unlock(&(philo->mutex->dead_mutex));
		return (DEAD);
	}
	pthread_mutex_unlock(&(philo->mutex->dead_mutex));
	return (0);
}

int	dead(t_philo *philo)
{
	pthread_mutex_lock(&(philo->mutex->dead_mutex));

	if (philo->mutex->dead == DEAD)
	{
		pthread_mutex_unlock(&(philo->mutex->dead_mutex));
		return (DEAD);
	}
	if (get_time() - (philo->data->end_time) >= philo->arg->time_to_die)
	{
		philo->mutex->dead = DEAD;
		printf("%d %d died\n", get_time() - philo->data->start_time,
			philo->id);
		pthread_mutex_unlock(&(philo->mutex->dead_mutex));
		return (DEAD);
	}
	pthread_mutex_unlock(&(philo->mutex->dead_mutex));
	return (0);
}

void	*monitoring(void *a)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)a;
	while (1)
	{
		i = -1;
		while (++i < philo[0].arg->philo_num)
		{
			
			if (dead(&philo[i]) == DEAD)
				return (a);
		}
		usleep(100);
	}
	return (a);
}
