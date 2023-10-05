/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josumin <josumin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 04:11:41 by sumjo             #+#    #+#             */
/*   Updated: 2023/10/05 21:53:08 by josumin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ph.h"

void	*philosophers(void *a)
{
	t_philo	*philo;

	philo = (t_philo *)a;
	while (1)
	{
		if (dead_and_full_check(philo) == DEAD)
			break ;
		spin_lock(philo);
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
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

void	philo_pthread_join(t_philo *philo, pthread_t *thread,
pthread_t *monitor_thread)
{
	int	i;

	pthread_join(*monitor_thread, NULL);
	i = -1;
	while (++i < philo[0].arg->philo_num)
		pthread_join(thread[i], NULL);
}
