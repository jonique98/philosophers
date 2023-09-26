/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumjo <sumjo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 04:10:25 by sumjo             #+#    #+#             */
/*   Updated: 2023/09/26 22:09:29 by sumjo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ph.h"

int	print(t_philo *philo, char *str)
{
	pthread_mutex_lock(&(philo->mutex->dead_mutex));
	if (philo->mutex->dead != DEAD)
		printf("%d %d %s\n", get_time() - philo->data->start_time, philo->id, str);
	else
	{
		pthread_mutex_unlock(&(philo->mutex->dead_mutex));
		return (FAIL);
	}
	pthread_mutex_unlock(&(philo->mutex->dead_mutex));
	return (0);
}
