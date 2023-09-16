/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumjo <sumjo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 18:47:41 by sumjo             #+#    #+#             */
/*   Updated: 2023/09/17 03:52:26 by sumjo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PH_H
#define PH_H

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>\

#define FAIL 1
#define DEAD 1

// struct timeval 
// {
//     time_t      tv_sec;
//     suseconds_t tv_usec;
// };


typedef struct s_mutex
{
	int				*fork;
	pthread_mutex_t	*fork_mutex;
	int 			dead;
	pthread_mutex_t	dead_mutex;
}				t_mutex;

typedef struct s_arg
{
	int	philo_num;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	must_eat;
}				t_arg;

typedef struct s_data
{
	int					left_fork;
	int					right_fork;
	int					eat_count;
	int				start_time;
	int				end_time;
}				t_data;

typedef struct s_philo
{
	int					id;
	t_arg				*arg;
	t_data				*data;
	t_mutex				*mutex;
}				t_philo;




#endif