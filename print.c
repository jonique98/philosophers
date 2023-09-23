/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumjo <sumjo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 04:10:25 by sumjo             #+#    #+#             */
/*   Updated: 2023/09/23 21:56:18 by sumjo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ph.h"

int	print(t_philo *philo, char *str)
{
	if (dead_check(philo) == DEAD)
		return (FAIL);
	printf("%d %d %s", get_time() - philo->data->start_time, philo->id, str);
	return (0);
}
