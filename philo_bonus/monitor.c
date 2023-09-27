/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumjo <sumjo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 21:36:48 by sumjo             #+#    #+#             */
/*   Updated: 2023/09/27 21:52:56 by sumjo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	monitoring(t_philo *philo)
{
	while (1)
	{
		sem_wait(philo->semaphores->dead);
		if (philo->data->end_time != 0
			&& get_time() - philo->data->end_time >= philo->arg->time_to_die)
		{
			printf("%d %d %s\n",
				get_time() - philo->data->start_time, philo->id, "died");
			exit (DEAD);
		}
		else if (philo->arg->must_eat != -1
			&& philo->data->eat_count >= philo->arg->must_eat)
		{
			printf("%d %d %s\n",
				get_time() - philo->data->start_time, philo->id, "died");
			exit (DEAD);
		}
		sem_post(philo->semaphores->dead);
		sleep(100);
	}
	return (0);
}
