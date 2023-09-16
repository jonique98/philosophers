/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dead_and_print.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumjo <sumjo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 04:10:25 by sumjo             #+#    #+#             */
/*   Updated: 2023/09/17 04:10:29 by sumjo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ph.h"

int	dead_check(t_philo *philo)
{
	pthread_mutex_lock(&(philo->mutex->dead_mutex));
	if (philo->mutex->dead == DEAD)
	{
		pthread_mutex_unlock(&(philo->mutex->dead_mutex));
		return (DEAD);
	}
	pthread_mutex_unlock(&(philo->mutex->dead_mutex));
	return (0);
}

int	print(t_philo *philo, char *str)
{
	if (dead_check(philo) == DEAD)
		return (FAIL);
	printf("%d %d %s", get_time() - philo->data->start_time, philo->id, str);
	return (0);
}
