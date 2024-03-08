/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prog.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalshafy <aalshafy@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 08:37:29 by aalshafy          #+#    #+#             */
/*   Updated: 2024/03/06 12:22:06 by aalshafy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../philosopher.h"

void *philosopher(void *arg)
{
	t_philosopher *philo;
    long            start_time;
    int*            philo_died;
    int             eat_count;

	start_time = get_time();
    philo = (t_philosopher *)arg;
    eat_count = philo->eat_count;
    philo_died = malloc(sizeof(int)); // need to free it in main
    *philo_died = 0;
	while (1)
    {
        if (get_time() - philo->last_meal > philo->data->time_to_die ||
             get_time() - start_time > philo->data->time_to_die)
        {
            philo_state(philo, "died");
            *philo_died = 1;
            return ((void *)philo_died);
        }
        if (philo->id % 2 == 0)
        {
            while (philo->eat_count == eat_count)
            {    
                printf("time stamp: %hu, philosopher %d is waiting\n", time_stamp(philo->start_time), philo->id);
                ft_usleep(1);
                is_eating(philo);
            }
        }
        else
            is_eating(philo);
        printf("time stamp: %hu, philosopher %d is sleeping\n", time_stamp(philo->start_time), philo->id);
        eat_count = philo->eat_count;
        philo_state(philo, "sleeping");
        ft_usleep(philo->data->time_to_sleep);
        philo_state(philo, "thinking");
        if (philo->eat_count >= philo->data->meal_nbr)
        {
            printf("time stamp: %hu, philosopher %d is full\n", time_stamp(philo->start_time), philo->id);
            break;
        }
    }
    return ((void *)philo_died);
}

void philo_state(t_philosopher *philo, char *state)
{
    pthread_mutex_lock(&philo->data->print);
    printf("time stamp: %hu, philosopher %d is %s\n", time_stamp(philo->start_time), philo->id, state);
    pthread_mutex_unlock(&philo->data->print);
}

void is_eating(t_philosopher *philo)
{
    // printf("time stamp: %llu, philosopher %d is trying to take a fork\n philo->fork = %d, *philo->next_fork = %d\n", get_time(), philo->id, philo->fork, *philo->next_fork);
    // this isnt excuting
    pthread_mutex_lock(&philo->fork_lock);
    printf("time stamp: %hu, philosopher %d is trying to take a fork\n philo->fork = %d, *philo->next_fork = %d\n", time_stamp(philo->start_time), philo->id, philo->fork, *philo->next_fork);
    pthread_mutex_lock(philo->next_fork_lock);
    if (philo->fork == 1 && (*philo->next_fork) == 1)
    {        
        philo->fork = 0;
        philo_state(philo, "has taken a fork");
        (*philo->next_fork) = 0;
        philo_state(philo, "has taken a fork");
        philo_state(philo, "eating");
        ft_usleep(philo->data->time_to_eat);
        philo->eat_count++;
        philo->last_meal = get_time();
        pthread_mutex_unlock(&philo->fork_lock);
        pthread_mutex_unlock(philo->next_fork_lock);
        philo->fork = 1;
        (*philo->next_fork) = 1;
    }
    else
    {
        pthread_mutex_unlock(&philo->fork_lock);
        pthread_mutex_unlock(philo->next_fork_lock);
        // usleep(10);
        // is_eating(philo);
    }
}

void *check_die(void *arg)
{
    t_philosopher *philo;

    philo = (t_philosopher *)arg;
    while (1)
    {
        if (time_stamp(philo->start_time) - philo->last_meal > philo->data->time_to_die)
        {
            philo_state(philo, "died");
            return (NULL);
        }
    }
}