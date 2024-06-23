/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalshafy <aalshafy@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 14:08:31 by aalshafy          #+#    #+#             */
/*   Updated: 2024/03/08 18:18:20 by aalshafy         ###   ########.fr       */
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
	pthread_mutex_destroy(&data->print);
	return (1);
}

int init_philosophers(t_data *data)
{
	t_philosopher *philosophers;

	printf("philo_nbr: %d\n", data->philo_nbr);
	philosophers = malloc(sizeof(t_philosopher) * data->philo_nbr);
	if (!philosophers)
		return (0);
	printf("%s\n", "test1");
	if (init_philosophers_mutexes(philosophers, data))
		return (2);
	
	init_philosophers_data(philosophers, data);
	printf("%s\n", "test2");
	printf("philosophers[0].id: %d\n", philosophers[0].id);
	int i = create_philosopher_thread(philosophers, data);
	if (i != 0)
		return (i);
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
		philosophers[i].data = data;
		printf("philosophers[i].id: %d\n", philosophers[i].id);
		printf("philosophers[i].data->philo_nbr: %d\n", philosophers[i].data->philo_nbr);
		printf("philosophers[i].data->time_to_die: %llu\n", philosophers[i].data->time_to_die);
		printf("philosophers[i].data->time_to_eat: %llu\n", philosophers[i].data->time_to_eat);
		printf("philosophers[i].data->time_to_sleep: %llu\n", philosophers[i].data->time_to_sleep);
		printf("philosophers[i].data->meal_nbr: %d\n", philosophers[i].data->meal_nbr);
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
	
	if (pthread_create(&data->checks, NULL, checks, philosophers))
		return (10);
	while (++i <= data->philo_nbr)
	{
		if (pthread_create(&philosophers[i].th, NULL, philo_rotine, &philosophers[i]))
			return (100);
	}
	pthread_join(data->checks, (void **) &ret);
	if (*ret == 1)
		return (50);
	i = 0;
	while (++i <= data->philo_nbr)
	{
		if (pthread_join(philosophers[i].th, NULL))
			return (60);
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

