/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumjo <sumjo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 21:33:01 by sumjo             #+#    #+#             */
/*   Updated: 2023/09/27 21:50:07 by sumjo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	create_philosophers(t_philo *philo, pid_t *pid_list)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		return (FAIL);
	else if (pid == 0)
	{
		init_data(philo);
		action(philo);
		exit(0);
	}
	else
		pid_list[philo->id - 1] = pid;
	return (0);
}

int	main(int ac, char **av)
{
	t_philo		*philo;
	pid_t		*pid_list;
	int			i;	

	init_philo(&philo, &pid_list, ac, av);
	i = -1;
	while (++i < philo[0].arg->philo_num)
		create_philosophers(&philo[i], pid_list);
	wait_child(pid_list, philo[0].arg->philo_num);
}
