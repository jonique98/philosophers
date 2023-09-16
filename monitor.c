/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumjo <sumjo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 04:07:16 by sumjo             #+#    #+#             */
/*   Updated: 2023/09/17 04:34:47 by sumjo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"ph.h"

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
				return (a);
			pthread_mutex_lock(&(philo[i].mutex->dead_mutex));
			if ((philo[i].arg->must_eat != -1 && philo[i].data->eat_count == philo[i].arg->must_eat) ||
			 get_time() - (philo[i].data->end_time) > philo[i].arg->time_to_die)
			{
				philo[i].mutex->dead = 1;
				printf("%d %d died\n", get_time() - philo[i].data->start_time, philo[i].id);
				pthread_mutex_unlock(&(philo[i].mutex->dead_mutex));
				return (a);
			}
			pthread_mutex_unlock(&(philo[i].mutex->dead_mutex));
			usleep(100);
		}
	}
	return (a);
}
