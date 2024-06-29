/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalshafy <aalshafy@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 10:02:23 by aalshafy          #+#    #+#             */
/*   Updated: 2024/06/29 17:35:57 by aalshafy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

void	*check_status(void *arg)
{
	t_data			*data;
	t_philosophers	*philos;

	data = (t_data *)arg;
	philos = data->philos;
	while (1)
	{
		if (check_die(philos, data) || check_eat_time(philos, data))
			break ;
	}
	return (arg);
}

int	check_die(t_philosophers *philos, t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_nbr)
	{
		pthread_mutex_lock(philos[i].meal_count_lock);
		if (get_time() - philos[i].last_meal >= philos[i].time_to_die
			&& !philos[i].is_eating)
		{
			print_messege(philos[i].id, "died", philos);
			pthread_mutex_lock(philos[i].dead_status);
			*philos[i].dead = 1;
			pthread_mutex_unlock(philos[i].dead_status);
			return (pthread_mutex_unlock(philos[i].meal_count_lock), 1);
		}
		pthread_mutex_unlock(philos[i].meal_count_lock);
	}
	return (0);
}
int	check_eat_time(t_philosophers *philos, t_data *data)
{
	int	i;
	int	full_philos;

	i = -1;
	full_philos = 0;
	if (data->meal_nbr == -1)
		return (0);
	while (++i < data->philo_nbr)
	{
		pthread_mutex_lock(philos[i].meal_count_lock);
		if (philos[i].meal_count >= data->meal_nbr)
			full_philos++;
		pthread_mutex_unlock(philos[i].meal_count_lock);
	}
	if (full_philos == data->philo_nbr)
	{
		pthread_mutex_lock(&data->dead_status);
		data->is_dead = 1;
		pthread_mutex_unlock(&data->dead_status);
		return (1);
	}
	return (0);
}
