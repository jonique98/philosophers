/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumjo <sumjo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 18:53:05 by sumjo             #+#    #+#             */
/*   Updated: 2023/10/04 18:40:51 by sumjo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ph.h"

int	main(int ac, char **av)
{
	t_philo		*philo;
	pthread_t	*thread;
	pthread_t	monitor_thread;

	if (init(&philo, ac, av) == FAIL)
		return (1);
	if (philo_create_thread(philo, &thread) == 0)
		return (free_philo(philo, philo[0].arg->philo_num));
	pthread_create(&monitor_thread, NULL, monitoring, (void *)philo);
	philo_pthread_join(philo, thread, &monitor_thread);
	free_philo(philo, philo[0].arg->philo_num);
	return (0);
}
