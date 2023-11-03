/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumjo <sumjo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 21:33:01 by sumjo             #+#    #+#             */
/*   Updated: 2023/11/03 21:17:39 by sumjo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	create_philosophers(int id, t_philo *philo, pid_t *pid_list)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		return (FAIL);
	else if (pid == 0)
	{
		philo->id = id + 1;
		action(philo);
		exit(0);
	}
	else
		pid_list[id] = pid;
	return (0);
}

int	main(int ac, char **av)
{
	t_philo		*philo;
	pid_t		*pid_list;
	int			i;	

	philo = init_philo(&pid_list, ac, av);
	i = -1;
	while (++i < philo->arg->philo_num)
		create_philosophers(i, philo, pid_list);
	wait_child(pid_list, philo[0].arg->philo_num);
}
