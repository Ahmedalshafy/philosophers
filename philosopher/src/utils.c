/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalshafy <aalshafy@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 13:39:42 by aalshafy          #+#    #+#             */
/*   Updated: 2024/02/28 09:52:56 by aalshafy         ###   ########.fr       */
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

	philosophers = malloc(sizeof(t_philosopher) * data->philo_nbr);
	if (!philosophers)
		return (0);
	i = 0;
	while (++i <= data->philo_nbr)
	{
		philosophers[i].id = i;
		philosophers[i].data = data;
		if (pthread_mutex_init(&philosophers[i].left_fork, NULL)) // need function to destroy philoshoper
			return (1);
		if (pthread_mutex_init(&philosophers[i].right_fork, NULL))
			return (2);
		printf("i - create = %d\n", i);
		if (pthread_create(&philosophers[i].th, NULL, philosopher, &philosophers[i]))
			return (3);
	}
	i = 0;
	while (++i <= data->philo_nbr)
	{
		printf("i - join = %d\n", i);
		if (pthread_join(philosophers[i].th, NULL))
			return (4);
		i++;
	}
	usleep(1000);
	i = 0;
	while (++i <= data->philo_nbr)
	{
		printf("i = %d\n", i);
		pthread_mutex_destroy(&philosophers[i].left_fork);
		pthread_mutex_destroy(&philosophers[i].right_fork);
	}
	free(philosophers);
	return (0);
}

void *philosopher(void *arg)
{
	t_philosopher *philo;

	philo = (t_philosopher *)arg;
	printf("philosopher id %d\n", philo->id);
	if (philo->id == 1)
	{
		printf("time stamp: %ld, philosopher %d has taken a fork\n", get_time(), philo->id);
		pthread_mutex_lock(&philo->left_fork);
		printf("time stamp: %ld, philosopher %d has taken a fork\n", get_time(), philo->id);
		pthread_mutex_lock(&philo->right_fork);
		printf("time stamp: %ld, philosopher %d is eating\n", get_time(), philo->id);
		usleep(philo->data->time_to_eat);
		pthread_mutex_unlock(&philo->left_fork);
		pthread_mutex_unlock(&philo->right_fork);
		printf("time stamp: %ld, philosopher %d is sleeping\n", get_time(), philo->id);
		usleep(philo->data->time_to_sleep);
		printf("time stamp: %ld, philosopher %d is thinking\n", get_time(), philo->id);
	}
	else
	{
		usleep(philo->data->time_to_sleep + 1000);
		printf("time stamp: %ld, philosopher %d is sleeping\n", get_time(), philo->id);
		pthread_mutex_lock(&philo->right_fork);
		pthread_mutex_lock(&philo->left_fork);
		printf("time stamp: %ld, philosopher %d has taken a fork\n", get_time(), philo->id);
		printf("time stamp: %ld, philosopher %d has taken a fork\n", get_time(), philo->id);
		printf("time stamp: %ld, philosopher %d is eating\n", get_time(), philo->id);
		usleep(philo->data->time_to_eat);
		pthread_mutex_unlock(&philo->right_fork);
		pthread_mutex_unlock(&philo->left_fork);
		printf("time stamp: %ld, philosopher %d is thinking\n", get_time(), philo->id);
	}
	return (NULL);
}

int ft_atoi(char *str)
{
	int i;
	int sign;
	int res;

	i = 0;
	sign = 1;
	res = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (res * sign);
}

long get_time(void)
{
	struct timeval time;
	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}