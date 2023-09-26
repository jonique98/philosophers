#ifndef PH_BONUS_H
# define PH_BONUS_H

# define FAIL 1
# define DEAD 1

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

typedef struct s_philo
{
	int					id;
	t_arg				*arg;
	t_data				*data;
}				t_philo;

#endif

