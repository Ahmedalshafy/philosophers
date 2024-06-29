/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalshafy <aalshafy@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 13:29:07 by aalshafy          #+#    #+#             */
/*   Updated: 2024/06/29 12:17:21 by aalshafy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

int	main(int argc, char **argv)
{
	t_data			data;
	t_philosophers	philos[MAX_PHILOS];
	pthread_mutex_t	forks_mutexes[MAX_PHILOS];
	int				forks[MAX_PHILOS];

	if (argc != 5 && argc != 6)
		return (printf("Error: wrong number of arguments\n"), 1);
	if (!check_args(argv))
		return (printf("Error: wrong arguments\n"), 1);
	if (!init_data(&data, argv, philos, argc))
		return (printf("Error: init_data\n"), 1);
	if (!init_forks(forks, forks_mutexes, data.philo_nbr))
		return (printf("Error: init_forks\n"), 1);
	init_philosophers(&data, philos, forks, forks_mutexes);
	if (!init_threads(philos, &data))
		return (destory_mutexes(&data, forks_mutexes, "Error: init_threads\n"),
			1);
	destory_mutexes(&data, forks_mutexes, NULL);
}

int	check_args(char **argv)
{
	int i;

	i = 1;
	while (argv[i])
	{
		if (ft_atoi(argv[i]) < 1)
			return (0);
		i++;
	}
	return (1);
}