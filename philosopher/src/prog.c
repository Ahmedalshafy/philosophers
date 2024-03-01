/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prog.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalshafy <aalshafy@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 08:37:29 by aalshafy          #+#    #+#             */
/*   Updated: 2024/03/01 19:10:34 by aalshafy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../philosopher.h"

void *philosopher(void *arg)
{
	t_philosopher *philo;
    long            start_time;

	start_time = get_time();
    philo = (t_philosopher *)arg;
	while (1)
    {
        if (philo->eat_count >= philo->data->meal_nbr)
            break;
        if (get_time() - philo->last_meal > philo->data->time_to_die ||
             get_time() - start_time > philo->data->time_to_die)
        {
            philo_state(philo, "died");
            return (NULL);
        }
        philo_state(philo, "thinking");
        is_eating(philo);
        philo_state(philo, "sleeping");
        usleep(philo->data->time_to_sleep * 1000);
    }
    return (NULL);
}

void philo_state(t_philosopher *philo, char *state)
{
    pthread_mutex_lock(&philo->print);
    printf("time stamp: %llu, philosopher %d is %s\n", get_time(), philo->id, state);
    pthread_mutex_unlock(&philo->print);
}

void is_eating(t_philosopher *philo)
{
    printf("time stamp: %llu, philosopher %d is trying to take a fork\n philo->fork = %d, *philo->next_fork = %d\n", get_time(), philo->id, philo->fork, *philo->next_fork);
    // this isnt excuting
    if (philo->fork == 1 && (*philo->next_fork) == 1)
    {        
        pthread_mutex_lock(&philo->fork_lock);
        philo->fork = 0;
        philo_state(philo, "has taken a fork");
        pthread_mutex_lock(&philo->next_fork_lock);
        (*philo->next_fork) = 0;
        philo_state(philo, "has taken a fork");
        philo_state(philo, "eating");
        usleep(philo->data->time_to_eat * 1000);
        philo->eat_count++;
        philo->last_meal = get_time();
        pthread_mutex_unlock(&philo->fork_lock);
        pthread_mutex_unlock(&philo->next_fork_lock);
        philo->fork = 1;
        (*philo->next_fork) = 1;
    }
}

void *check_die(void *arg)
{
    t_philosopher *philo;

    philo = (t_philosopher *)arg;
    while (1)
    {
        if (get_time() - philo->last_meal > philo->data->time_to_die)
        {
            philo_state(philo, "died");
            return (NULL);
        }
    }
}