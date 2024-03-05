/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalshafy <aalshafy@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 14:08:31 by aalshafy          #+#    #+#             */
/*   Updated: 2024/03/05 08:07:25 by aalshafy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../philosopher.h"

int init_data(t_data *data, char **argv)
{
	data->philo_nbr = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->meal_nbr = ft_atoi(argv[5]);
	if (data->philo_nbr < 1 || data->time_to_die < 1 
	|| data->time_to_eat < 1 || data->time_to_sleep < 1 || data->meal_nbr < 1)
		return (0);
	return (1);
}

int init_philosophers(t_data *data)
{
	t_philosopher *philosophers;
	int i;
	int *ret;

	philosophers = malloc(sizeof(t_philosopher) * data->philo_nbr);
	if (!philosophers)
		return (0);
	i = 0;
	while (++i <= data->philo_nbr)
	{
		philosophers[i].id = i;
		philosophers[i].fork = 1;
		philosophers[i].eat_count = 0;
		philosophers[i].start_time = get_time();
		philosophers[i].last_meal = get_time();
		philosophers[i].data = data;
		if (i == data->philo_nbr)
			philosophers[i].next_fork = &philosophers[1].fork;
		else
			philosophers[i].next_fork = &philosophers[i + 1].fork;		
	}
	i = 0;
	while (++i <= data->philo_nbr)
	{
		if (pthread_mutex_init(&philosophers[i].fork_lock, NULL)) // need function to destroy philoshoper
			return (1);
		if (pthread_mutex_init(&philosophers[i].next_fork_lock, NULL))
			return (2);
		if (pthread_mutex_init(&philosophers[i].print, NULL))
			return (3);
		if (pthread_create(&philosophers[i].th, NULL, philosopher, &philosophers[i]))
			return (3);
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
	i = 0;
	while (++i <= data->philo_nbr)
	{
		pthread_mutex_destroy(&philosophers[i].fork_lock);
		pthread_mutex_destroy(&philosophers[i].next_fork_lock);
		pthread_mutex_destroy(&philosophers[i].print);
	}	
	free(philosophers);
	return (0);
}

// void init_threads(t_philosopher *philosophers)
// {
// 	int i;
	
		
// 	i = 0;
	
// }
