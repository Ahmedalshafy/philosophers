/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalshafy <aalshafy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 14:08:31 by aalshafy          #+#    #+#             */
/*   Updated: 2024/03/08 08:24:47 by aalshafy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../philosopher.h"

int init_data(t_data *data, char **argv) // takes pointer to struct so it can modify it
{
	data->philo_nbr = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->meal_nbr = ft_atoi(argv[5]);
	if (data->philo_nbr < 1 || data->time_to_die < 1 
	|| data->time_to_eat < 1 || data->time_to_sleep < 1 || data->meal_nbr < 1)
		return (0);
	if (pthread_mutex_init(&data->print, NULL)) // init mutex for print
		return (0);
	data->philosophers = malloc(sizeof(t_philosopher) * data->philo_nbr);
	if (!data->philosophers)
		return (0);
	if (init_philosophers(data) != 0)
		return (free(data->philosophers), 0);
	pthread_mutex_destroy(&data->print);
	return (free(data->philosophers), 1);
}

int init_philosophers(t_data *data)
{
	t_philosopher *philosophers;
	int i;
	int *ret;

	philosophers = data->philosophers;
	if (init_philosophers_mutexes(philosophers, data))
		return (2);
	init_philosophers_data(philosophers, data);
	if (create_philosopher_thread(philosophers, data))
		return (4);
	destroy_philosophers_mutexes(philosophers, data);
	return (0);
}

// init philosphers mutexes
int init_philosophers_mutexes(t_philosopher *philosophers, t_data *data)
{
	int i;

	i = 0;
	while(++i <= data->philo_nbr)
	{
		if (pthread_mutex_init(&philosophers[i].fork_lock, NULL)) // need function to destroy philoshoper
			return (1);
	}
	return (0);
}

// init philosphers data
void init_philosophers_data(t_philosopher *philosophers, t_data *data)
{
	int i;

	i = 0;
	while(++i <= data->philo_nbr)
	{
		philosophers[i].id = i;
		philosophers[i].fork = 1;
		philosophers[i].eat_count = 0;
		philosophers[i].start_time = get_time();
		philosophers[i].last_meal = get_time();
		if (i == data->philo_nbr)
			philosophers[i].next_fork = &philosophers[1].fork;
		else
			philosophers[i].next_fork = &philosophers[i + 1].fork;
		if (i == data->philo_nbr)
			philosophers[i].next_fork_lock = &philosophers[1].fork_lock;
		else
			philosophers[i].next_fork_lock = &philosophers[i + 1].fork_lock;
	}
}

// creat philosopher thread
int create_philosopher_thread(t_philosopher *philosophers, t_data *data)
{
	int i;
	int *ret;

	i = 0;
	while (++i <= data->philo_nbr)
	{
		if (pthread_create(&philosophers[i].th, NULL, philosopher, &data))
			return (4);
	}
	i = 0;
	while (++i <= data->philo_nbr)
	{
		if (pthread_join(philosophers[i].th, (void **) &ret))
			return (4);
		if (*ret == 1)
		{
			printf("philosopher %d died\n", i);
			free(ret);
			return (5);
		}
	}
	return (0);
}

// destroy philosphers mutexes
void destroy_philosophers_mutexes(t_philosopher *philosophers, t_data *data)
{
	int i;

	i = 0;
	while(++i <= data->philo_nbr)
	{
		pthread_mutex_destroy(&philosophers[i].fork_lock);
	}
}

