/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josumin <josumin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 18:47:41 by sumjo             #+#    #+#             */
/*   Updated: 2023/09/26 10:29:26 by josumin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PH_H
# define PH_H

# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>

# define FAIL 1
# define DEAD 1

typedef struct s_mutex
{
	int				*fork;
	pthread_mutex_t	*fork_mutex;
	int				dead;
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
	int				left_fork;
	int				right_fork;
	int				eat_count;
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

int			ft_atoi(const char *str);
int			get_time(void);
int			free_philo(t_philo *philo, int i);
void		ft_free(void *ptr1, void *ptr2, void *ptr3);
int			parsing(char **av, t_arg *arg);

void		*philosophers(void *a);
pthread_t	*philo_create_thread(t_philo *philo, pthread_t **thread);
void		philo_pthread_join(t_philo *philo, pthread_t *thread,
				pthread_t *monitor_thread);

int			get_right_fork(t_philo *philo);
int			get_left_fork(t_philo *philo);
int			spin_lock(t_philo *philo);

void		*monitoring(void *a);

t_arg		*init_arg(int ac, char **av);
t_data		*init_data(t_arg *arg, int i);
t_mutex		*init_mutex(t_arg *arg);
int			init_philo(t_philo *philo, t_arg *arg, t_mutex *mutex);
int			init(t_philo **philo, int ac, char **av);

int			dead_check(t_philo *philo);
int			print(t_philo *philo, char *str);

int			philo_eat(t_philo *philo);
int			philo_sleep(t_philo *philo);
int			philo_think(t_philo *philo);
void		catnap(int t, int limit);
void		drop_fork(t_philo *philo);

#endif