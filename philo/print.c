/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josumin <josumin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 04:10:25 by sumjo             #+#    #+#             */
/*   Updated: 2023/10/05 21:58:11 by josumin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ph.h"

int	print(t_philo *philo, char *str)
{
	if (dead_and_full_check(philo) == 0)
		printf("%d %d %s\n", get_time() - philo->data->start_time,
			philo->id, str);
	else
		return (FAIL);
	pthread_mutex_unlock(&(philo->mutex->dead_mutex));
	return (0);
}
