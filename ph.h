/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumjo <sumjo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 18:47:41 by sumjo             #+#    #+#             */
/*   Updated: 2023/09/11 23:07:15 by sumjo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PH_H
#define PH_H

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>

// struct timeval 
// {
//     time_t      tv_sec;
//     suseconds_t tv_usec;
// };

typedef struct s_arg
{
	int *fork;
	int	philo_num;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	pthread_mutex_t *mutex;
}				t_arg;

typedef struct s_philo
{
	int					id;
	int					left_fork;
	int					right_fork;
	long				end_time;
	pthread_mutex_t		**mutex;
	t_arg				*arg;
}				t_philo;



#endif