/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalshafy <aalshafy@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 10:02:23 by aalshafy          #+#    #+#             */
/*   Updated: 2024/03/08 15:51:59 by aalshafy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../philosopher.h"

void *checks(void *arg)
{
    t_philosopher *philo;

    philo = (t_philosopher *) &arg; // pointer problem
    printf("philo->data->is_dead: %d\n", philo[0].data->is_dead); // philo[0].data->is_dead
    while (1)
    {
        if (check_die(philo) || check_eat_time(philo))
        {
            philo->data->is_dead = 1;
            return (void *) &philo->data->is_dead;
        }
    }
    return ((void *) &philo->data->is_dead);
}

int check_eat_time(t_philosopher *philo)
{
    int i;
    
    i = -1;
    printf("philo->data->meal_nbr: %d\n", philo[0].data->meal_nbr); // philo[0].data->meal_nbr
    printf("philo->data->philo_nbr: %d\n", philo[0].data->philo_nbr); // philo[0].data->philo_nbr
    while (++i < philo[0].data->philo_nbr) // philo[0].data->philo_nbr
    {
        if (philo[i].eat_count < philo[0].data->meal_nbr) // philo[0].data->meal_nbr
            return (0);
    }
    printf("All philosophers have eaten %d times\n", philo->data->meal_nbr);
    return (1);
}

int check_die(t_philosopher *philo)
{
    int i;
    
    i = -1;
    while (++i < philo->data->philo_nbr)
    {
        pthread_mutex_lock(&philo[i].fork_lock);
        if (get_time() - philo[i].last_meal > philo->data->time_to_die)
        {
            philo_state(&philo[i], "died");
            pthread_mutex_unlock(&philo[i].fork_lock);
            return (1);
        }
        pthread_mutex_unlock(&philo[i].fork_lock);
    }
    return (0);
}