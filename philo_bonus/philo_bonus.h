/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumjo <sumjo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 21:47:17 by sumjo             #+#    #+#             */
/*   Updated: 2023/11/03 18:08:54 by sumjo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <semaphore.h>
# include <pthread.h>
# include <signal.h>

# define FAIL 1
# define DEAD 1
# define FULL 2

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
	int				eat_count;
	int				start_time;
	int				end_time;
}				t_data;

typedef struct s_semaphores
{
	sem_t			*forks;
	sem_t			*dead;
}				t_semaphores;

typedef struct s_philo
{
	int					id;
	t_arg				*arg;
	t_data				*data;
	t_semaphores		*semaphores;

}				t_philo;

void			init_philo(t_philo **philo, pid_t **pid_list,
					int ac, char **av);
int				print(t_philo *philo, char *str);
int				monitoring(t_philo *philo);
int				get_time(void);
void			catnap(int start_time, int time, int time_to);
void			philo_eat(t_philo *philo);
void			philo_sleep(t_philo *philo);
void			philo_think(t_philo *philo);
void			action(t_philo *philo);
void			get_left_fork(t_philo *philo);
void			get_right_fork(t_philo *philo);
void			drop_forks(t_philo *philo);
void			init_data(t_philo *philo);
t_arg			*init_arg(int ac, char **av);
t_semaphores	*init_semaphores(t_arg *arg);
void			wait_child(pid_t *pid_list, int philo_num);
int				ft_atoi(const char *str);
void			parsing(char **av, t_arg *arg);
int				full_check(t_philo *philo);

#endif