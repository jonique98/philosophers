/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumjo <sumjo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 21:32:27 by sumjo             #+#    #+#             */
/*   Updated: 2023/11/03 18:30:57 by sumjo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_atoi(const char *str)
{
	int					i;
	int					minus;
	unsigned long long	num;

	i = 0;
	minus = 1;
	num = 0;
	while ((9 <= str[i] && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			minus = -1;
		i++;
	}
	if (!('0' <= str[i] && str[i] <= '9'))
		return (num);
	while ('0' <= str[i] && str[i] <= '9')
	{
		num *= 10;
		num += str[i] - '0';
		i++;
	}
	return (num * minus);
}

int	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	catnap(int current_time, int t, int limit)
{
	usleep(t / 2);
	while (1)
	{
		if (get_time() - current_time >= limit)
			return ;
		usleep(100);
	}
}

void	wait_child(pid_t *pid_list, int philo_num)
{
	int	i;
	int	status;

	i = -1;
	while (++i < philo_num)
	{
		waitpid(-1, &status, 0);
		if (status == 256)
		{
			while (i < philo_num)
			{
				kill(pid_list[i], SIGKILL);
				i++;
			}
		}
	}
}
