/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumjo <sumjo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 21:38:09 by sumjo             #+#    #+#             */
/*   Updated: 2023/11/03 21:36:59 by sumjo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	print(t_philo *philo, char *str)
{
	if (sem_wait(philo->semaphores->dead) == -1)
		exit(1);
	printf("%d %d %s\n", get_time() - philo->data->start_time,
		philo->id, str);
	sem_post(philo->semaphores->dead);
	return (0);
}
