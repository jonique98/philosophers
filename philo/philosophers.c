/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumjo <sumjo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 04:11:41 by sumjo             #+#    #+#             */
/*   Updated: 2023/12/25 19:39:20 by sumjo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ph.h"

void	*philosophers(void *a)
{
	t_philo	*philo;

	philo = (t_philo *)a;
	if (philo->id % 2 == 0)
		usleep(200);
	while (1)
	{
		if (spin_lock(philo) == FAIL)
			break ;
		if (philo_eat(philo) == FULL)
			break ;
		philo_sleep(philo);
		philo_think(philo);
		if (dead_check(philo) == DEAD)
			break ;
	}
	return (a);
}

pthread_t	*philo_create_thread(t_philo *philo, pthread_t **thread)
{
	int			i;
	int			ms;

	*thread = malloc(sizeof(pthread_t) * philo->arg->philo_num);
	if (!*thread)
		return (0);
	i = -1;
	while (++i < philo[0].arg->philo_num)
	{
		ms = get_time();
		philo[i].data->start_time = ms;
		philo[i].data->end_time = ms;
		pthread_create(&(*thread)[i], NULL, philosophers, (void *)&philo[i]);
	}
	return (*thread);
}

void	philo_pthread_join(t_philo *philo, pthread_t *thread)
{
	int	i;

	i = -1;
	while (++i < philo[0].arg->philo_num)
		pthread_join(thread[i], NULL);
}
