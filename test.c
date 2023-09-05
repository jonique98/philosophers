/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumjo <sumjo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 18:53:05 by sumjo             #+#    #+#             */
/*   Updated: 2023/09/05 21:23:39 by sumjo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ph.h"

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

int main(int ac, char **av)
{
	ac = 0;
	t_arg arg;
	t_philo		**philo;
	pthread_t	*ph;
	pthread_mutex_t *mutex;
	int *fork;
	
	int i = 0;
	arg.philo_num = ft_atoi(av[1]);
	arg.time_to_die = ft_atoi(av[2]);
	arg.time_to_eat = ft_atoi(av[3]);
	// int time_to_sleep = ft_atoi(av[4]);
	
	ph = malloc(sizeof(ph) * arg.philo_num);
	mutex = malloc(sizeof(pthread_t) * arg.philo_num);
	fork = calloc(arg.philo_num, sizeof(int));
	mutex = malloc(sizeof(pthread_mutex_t) * arg.philo_num);

	philo = malloc(sizeof(t_philo *) * arg.philo_num);
	while (i < arg.philo_num)
	{
		// pthread_create(&ph[i], NULL, );
		philo[i] = malloc(sizeof(t_philo));
		philo[i]->id = i + 1;
		philo[i]->left_fork = fork + philo[i]->id;
		philo[i]->right_fork = fork + (philo[i]->id % arg.philo_num) + 1;
		i++;
	}
	for(int j = 0; j < 5; j++)
		printf("id = %d left_fork = %d right_fork = %d\n", philo[j]->id, *(philo[j]->left_fork), *(philo[j]->right_fork));
}

// pthread_mutex_t g_mutex;
// int g_cnt;

// void *count(void *arg)
// {
// 	char *name;
// 	int i = 0;

// 	name = (char *)arg;
// 	pthread_mutex_lock(&g_mutex);
// 	g_cnt = 0;
// 	while (i < 13)
// 	{
// 		printf("%s cnt : %d\n", name, g_cnt);
// 		g_cnt++;
// 		usleep(20000);
// 		i++;
// 	}
// 	pthread_mutex_unlock(&g_mutex);
// 	return ((void *)arg);
// }

// int main()
// {
// 	pthread_t pth1 = 0;
// 	pthread_t pth2 = 0;
// 	pthread_t pth3 = 0;

// 	pthread_mutex_init(&g_mutex, NULL);
// 	pthread_create(&pth1, NULL, count, (void *)"thread1");
// 	pthread_create(&pth2, NULL, count, (void *)"thread2");
// 	pthread_create(&pth3, NULL, count, (void *)"thread3");
// 	pthread_join(pth1, NULL);
// 	pthread_join(pth2, NULL);
// 	pthread_join(pth3, NULL);
// 	pthread_mutex_destroy(&g_mutex);
// }
