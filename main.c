/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumjo <sumjo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 18:53:05 by sumjo             #+#    #+#             */
/*   Updated: 2023/09/17 04:12:17 by sumjo            ###   ########.fr       */
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
	philo_create_thread(philo, &thread);
	pthread_create(&monitor_thread, NULL, monitoring, (void *)philo);
	philo_pthread_join(philo, thread, &monitor_thread);
	ft_free(philo);
	return (0);
}
