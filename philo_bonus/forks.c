/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumjo <sumjo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 21:35:06 by sumjo             #+#    #+#             */
/*   Updated: 2023/11/03 21:26:42 by sumjo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	get_left_fork(t_philo *philo)
{
	sem_wait(philo->semaphores->forks);
	if (print(philo, "has taken a left fork") == FAIL)
	{
		sem_post(philo->semaphores->forks);
		exit (DEAD);
	}
}

void	get_right_fork(t_philo *philo)
{
	sem_wait(philo->semaphores->forks);
	if (print(philo, "has taken a right fork") == FAIL)
	{
		sem_post(philo->semaphores->forks);
		sem_post(philo->semaphores->forks);
		exit (DEAD);
	}
}

void	drop_forks(t_philo *philo)
{
	sem_post(philo->semaphores->forks);
	sem_post(philo->semaphores->forks);
	usleep(100);
}
