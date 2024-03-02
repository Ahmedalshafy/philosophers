/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prog.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalshafy <aalshafy@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 08:37:29 by aalshafy          #+#    #+#             */
/*   Updated: 2024/03/02 17:38:48 by aalshafy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../philosopher.h"

void *philosopher(void *arg)
{
	t_philosopher *philo;
    long            start_time;
    int*            philo_died;

	start_time = get_time();
    philo = (t_philosopher *)arg;
    philo_died = malloc(sizeof(int)); // need to free it in main
    *philo_died = 0;
	while (1)
    {
        printf("id = %d, eat_count = %d\n", philo->id, philo->eat_count);
        printf("meal_nbr = %d\n", philo->data->meal_nbr);
        if (get_time() - philo->last_meal > philo->data->time_to_die ||
             get_time() - start_time > philo->data->time_to_die)
        {
            philo_state(philo, "died");
            *philo_died = 1;
            return ((void *)philo_died);
        }
        if (philo->id % 2 == 0)
            usleep(1000);
        is_eating(philo);
        if (philo->eat_count >= philo->data->meal_nbr)
        {
            printf("time stamp: %llu, philosopher %d is full\n", get_time(), philo->id);
            break;
        }
        philo_state(philo, "sleeping");
        usleep(philo->data->time_to_sleep * 1000);
        philo_state(philo, "thinking");
    }
    return ((void *)philo_died);
}

void philo_state(t_philosopher *philo, char *state)
{
    pthread_mutex_lock(&philo->print);
    printf("time stamp: %llu, philosopher %d is %s\n", get_time(), philo->id, state);
    pthread_mutex_unlock(&philo->print);
}

void is_eating(t_philosopher *philo)
{
    // printf("time stamp: %llu, philosopher %d is trying to take a fork\n philo->fork = %d, *philo->next_fork = %d\n", get_time(), philo->id, philo->fork, *philo->next_fork);
    // this isnt excuting
    pthread_mutex_lock(&philo->fork_lock);
    if (philo->fork == 1 && (*philo->next_fork) == 1)
    {        
        philo->fork = 0;
        philo_state(philo, "has taken a fork");
        (*philo->next_fork) = 0;
        philo_state(philo, "has taken a fork");
        philo_state(philo, "eating");
        usleep(philo->data->time_to_eat * 1000);
        philo->eat_count++;
        philo->last_meal = get_time();
        pthread_mutex_unlock(&philo->fork_lock);
        philo->fork = 1;
        (*philo->next_fork) = 1;
    }
    else
    {
        pthread_mutex_unlock(&philo->fork_lock);
        usleep(1000);
        is_eating(philo);
    }
}

void *check_die(void *arg)
{
    t_philosopher *philo;

    philo = (t_philosopher *)arg;
    printf("time stamp: %llu, philosopher %d is checking if he is dead\n", get_time(), philo->id);
    while (1)
    {
        if (get_time() - philo->last_meal > philo->data->time_to_die)
        {
            printf("time stamp: %llu, philosopher %d will dead\n", get_time(), philo->id);
            philo_state(philo, "died");
            return (NULL);
        }
    }
}