/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumjo <sumjo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 21:36:48 by sumjo             #+#    #+#             */
/*   Updated: 2023/10/04 20:08:53 by sumjo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	monitoring(t_philo *philo)
{
	while (1)
	{
		sem_wait(philo->semaphores->dead);
		if (get_time() - philo->data->end_time >= philo->arg->time_to_die)
		{
			printf("%d %d %s\n",
				get_time() - philo->data->start_time, philo->id, "died");
			exit (DEAD);
		}
		else if (philo->arg->must_eat != -1
			&& philo->data->eat_count >= philo->arg->must_eat)
			exit (DEAD);
		sem_post(philo->semaphores->dead);
		usleep(50);
	}
	return (0);
}
