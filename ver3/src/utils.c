/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalshafy <aalshafy@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 13:39:42 by aalshafy          #+#    #+#             */
/*   Updated: 2024/06/29 18:12:40 by aalshafy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

int	ft_atoi(char *str)
{
	int	i;
	int	sign;
	int	res;

	i = 0;
	sign = 1;
	res = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r')
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

// static size_t ft_strlen(char *str)
// {
// 	size_t i;

// 	i = 0;
// 	while (str[i])
// 		i++;
// 	return (i);
// }

size_t	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	// 	write(2, "Error: gettimeofday\n", 20);
	return (((time.tv_sec * 1000) + (time.tv_usec / 1000)));
}

size_t	time_stamp(size_t start_time)
{
	return (get_time() - start_time);
}

int	ft_usleep(size_t time)
{
	size_t	start;

	start = get_time();
	while (get_time() - start < time)
		usleep(500);
	return (0);
}

void	print_messege(int id, char *messege, t_philosophers *philos)
{
	pthread_mutex_lock(philos->print);
	if (!dead_status_check(philos))
		printf("%zu %d %s\n", time_stamp(philos->start_time), id, messege);
	pthread_mutex_unlock(philos->print);
}

void	destory_mutexes(t_data *data, pthread_mutex_t *forks_mutexes, char *str)
{
	int i;

	(void)str;
	if (str)
	{
		printf("%s\n", str);
	}
	i = -1;
	while (++i < data->philo_nbr)
		pthread_mutex_destroy(&forks_mutexes[i]);
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->dead_status);
	pthread_mutex_destroy(&data->meal_count_lock);
}