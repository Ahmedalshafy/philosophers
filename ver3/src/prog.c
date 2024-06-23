/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prog.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalshafy <aalshafy@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 08:37:29 by aalshafy          #+#    #+#             */
/*   Updated: 2024/03/08 15:28:05 by aalshafy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../philosopher.h"

void *philo_rotine(void *arg)
{
    t_philosopher *philo;

    philo = (t_philosopher *)arg;
    if (philo->id % 2 == 0)
        ft_usleep(1);
    while (philo->data->is_dead == 0)
    {
        philo_eat(philo);
        philo_sleep(philo);
        philo_think(philo);
    }
    return (NULL);
}

void philo_eat(t_philosopher *philo)
{
    pthread_mutex_lock(&philo->fork_lock);
    philo_state(philo, "has taken a fork");
    pthread_mutex_lock(philo->next_fork_lock);
    philo_state(philo, "has taken a fork");
    philo_state(philo, "is eating");
    ft_usleep(philo->data->time_to_eat);
    philo->last_meal = get_time();
    philo->eat_count++;
    pthread_mutex_unlock(&philo->fork_lock);
    pthread_mutex_unlock(philo->next_fork_lock);
}

void philo_sleep(t_philosopher *philo)
{
    philo_state(philo, "is sleeping");
    ft_usleep(philo->data->time_to_sleep);
}

void philo_think(t_philosopher *philo)
{
    philo_state(philo, "is thinking");
}

void philo_state(t_philosopher *philo, char *state)
{
    pthread_mutex_lock(&philo->data->print);
    printf("time stamp: %hu, philosopher %d is %s\n", time_stamp(philo->start_time), philo->id, state);
    pthread_mutex_unlock(&philo->data->print);
}