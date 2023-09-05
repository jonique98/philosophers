/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumjo <sumjo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 18:47:41 by sumjo             #+#    #+#             */
/*   Updated: 2023/09/05 21:03:50 by sumjo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PH_H
#define PH_H

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>


typedef struct arg
{
	int	philo_num;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
}				t_arg;

typedef struct s_philo
{
	int	id;
	int	*left_fork;
	int	*right_fork;
}				t_philo;


#endif