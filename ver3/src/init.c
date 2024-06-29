/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalshafy <aalshafy@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 14:08:31 by aalshafy          #+#    #+#             */
/*   Updated: 2024/06/29 17:17:06 by aalshafy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

int	init_data(t_data *data, char **argv, t_philosophers *philos, int argc)
{
	int	i;

	i = -1;
	data->philo_nbr = ft_atoi(argv[1]);
	while (++i < data->philo_nbr)
	{
		philos[i].time_to_die = ft_atoi(argv[2]);
		philos[i].time_to_eat = ft_atoi(argv[3]);
		philos[i].time_to_sleep = ft_atoi(argv[4]);
	}
	if (argc == 6)
		data->meal_nbr = ft_atoi(argv[5]);
	else
		data->meal_nbr = -1;
	data->philos = philos;
	data->is_dead = 0;
	if (pthread_mutex_init(&data->print, NULL))
		return (0);
	if (pthread_mutex_init(&data->dead_status, NULL))
		return (0);
	if (pthread_mutex_init(&data->meal_count_lock, NULL))
		return (0);
	return (1);
}

void	init_philosophers(t_data *data, t_philosophers *philos, int *forks,
		pthread_mutex_t *forks_mutexes)
{
	int	i;

	i = -1;
	while (++i < data->philo_nbr)
	{
		philos[i].id = i + 1;
		philos[i].philo_nbr = data->philo_nbr;
		philos[i].meal_count = 0;
		philos[i].is_eating = 0;
		philos[i].dead = &data->is_dead;
		philos[i].last_meal = get_time();
		philos[i].start_time = get_time();
		philos[i].meal_count = 0;
		philos[i].print = &data->print;
		philos[i].dead_status = &data->dead_status;
		philos[i].meal_count_lock = &data->meal_count_lock;
		philos[i].right_fork = &forks[i];
		if (i == data->philo_nbr)
			philos[i].left_fork = &forks[0];
		else
			philos[i].left_fork = &forks[i + 1];
		philos[i].right_fork_lock = &forks_mutexes[i];
		if (i == data->philo_nbr)
			philos[i].left_fork_lock = &forks_mutexes[0];
		else
			philos[i].left_fork_lock = &forks_mutexes[i + 1];
	}
}

// init philosphers mutexes
int	init_forks(int *forks, pthread_mutex_t *forks_mutexes, int philo_nbr)
{
	int	i;

	i = -1;
	while (++i < philo_nbr)
	{
		forks[i] = 1;
		if (pthread_mutex_init(&forks_mutexes[i], NULL))
			return (0);
	}
	return (1);
}

// creat philosopher thread
int	init_threads(t_philosophers *philos, t_data *data)
{
	int i;

	if (pthread_create(&data->checks, NULL, &check_status, data))
		return (0);
	i = -1;
	while (++i < data->philo_nbr)
	{
		if (pthread_create(&philos[i].th, NULL, &philo_routine, &philos[i]))
			return (0);
	}
	if (pthread_join(data->checks, NULL))
		return (0);
	i = -1;
	while (++i < data->philo_nbr)
	{
		if (pthread_join(philos[i].th, NULL))
			return (0);
	}
	return (1);
}