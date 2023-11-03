/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumjo <sumjo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 21:36:48 by sumjo             #+#    #+#             */
/*   Updated: 2023/11/03 21:38:55 by sumjo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	monitoring(t_philo *philo)
{
	int	time;

	while (1)
	{
		time = get_time();
		if (time - philo->data->end_time >= philo->arg->time_to_die)
		{
			sem_wait(philo->semaphores->dead);
			printf("%d %d %s\n",
				get_time() - philo->data->start_time, philo->id, "died");
			exit(1);
		}
		usleep(100);
	}
	return (0);
}
