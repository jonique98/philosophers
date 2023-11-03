/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumjo <sumjo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 21:35:06 by sumjo             #+#    #+#             */
/*   Updated: 2023/11/03 21:44:06 by sumjo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	get_left_fork(t_philo *philo)
{
	sem_wait(philo->semaphores->forks);
	print(philo, "has taken a fork");
}

void	get_right_fork(t_philo *philo)
{
	sem_wait(philo->semaphores->forks);
	print(philo, "has taken a fork");
}

void	drop_forks(t_philo *philo)
{
	sem_post(philo->semaphores->forks);
	sem_post(philo->semaphores->forks);
	usleep(100);
}
