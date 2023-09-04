#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

void    *ph_thread(void *argv)
{
    t_arg        *arg;
    t_philo        *philo;

    philo = argv;
    arg = philo->arg;
    if (philo->id % 2 == 0)
        sleep_until_even_eat(arg);
    while (!arg->finish)
    {
        if (arg->philo_num - 1 == philo->id && philo->eat_count == 0)
            usleep(1);
        ph_action(arg, philo);
        if (arg->philo_num == 1)
            spend_time((long long)arg->time_to_sleep, arg);
        if (arg->eat_times == philo->eat_count)
        {
            arg->finished_eat++;
            break ;
        }
        ph_stat_printf(arg, philo->id, "is sleeping");
        spend_time((long long)arg->time_to_sleep, arg);
        ph_stat_printf(arg, philo->id, "is thinking");
    }
    return (0);
}

int    ph_start(t_arg *arg, t_philo *philo)
{
    int        i;

    i = 0;
    while (i < arg->philo_num)
    {
        philo[i].last_eat_time = get_time();
        if (pthread_create(&(philo[i].thread), NULL, ph_thread, &(philo[i])))
            return (1);
        i++;
    }
    // ph_check_finish(arg, philo);
    i = 0;
    while (i < arg->philo_num)
        pthread_join(philo[i++].thread, NULL);
    return (0);
}

