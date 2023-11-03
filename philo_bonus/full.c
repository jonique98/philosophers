/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   full.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumjo <sumjo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 18:08:07 by sumjo             #+#    #+#             */
/*   Updated: 2023/11/03 18:21:28 by sumjo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	full_check(t_philo *philo)
{
	if (philo->arg->must_eat != -1)
		philo->data->eat_count++;
	if (philo->data->eat_count == philo->arg->must_eat)
		return (FULL);
	return (0);
}
