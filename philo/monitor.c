/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumjo <sumjo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 04:07:16 by sumjo             #+#    #+#             */
/*   Updated: 2023/10/04 18:48:28 by sumjo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"ph.h"

int	dead_check(t_philo *philo)
{
	pthread_mutex_lock(&(philo->mutex->dead_mutex));
	if (philo->mutex->dead == DEAD
		|| ((philo->arg->must_eat != -1
				&& philo->data->eat_count == philo->arg->must_eat)
			|| get_time() - (philo->data->end_time) >= philo->arg->time_to_die))
	{
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
			if (dead_check(&philo[i]) == DEAD)
			{
				philo[i].mutex->dead = 1;
				printf("%d %d died\n", get_time() - philo[i].data->start_time,
					philo[i].id);
				return (a);
			}
			pthread_mutex_unlock(&(philo[i].mutex->dead_mutex));
			usleep(100);
		}
	}
	return (a);
}
