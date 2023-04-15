/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoll <mdoll@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 10:20:15 by mdoll             #+#    #+#             */
/*   Updated: 2023/04/05 10:20:15 by mdoll            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "philo.h"
#include <pthread/pthread.h>
#include <strings.h>
#include <sys/time.h>
#include <stdlib.h>

static void	fill_struct(t_data *data, char **argv, int argc) {
	int	i;

	data->number_of_philo = (int) atolong(argv[1]);
	data->time_to_die = (int) atolong(argv[2]);
	data->time_to_eat = (int) atolong(argv[3]);
	data->time_to_sleep = (int) atolong(argv[4]);
	if (argc == 6)
		data->how_much_eat = (int) atolong(argv[5]);
	else
		data->how_much_eat = -1;
	i = 0;
	data->forks = malloc(sizeof(pthread_mutex_t));
	while (i < data->number_of_philo)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
		{
			printf("mutex inti failed\n");
			return ;
		}
		i++;
	}
}

static void	init_philosopher(t_philo *philo, t_data *data, t_time *start_time, int id)
{
	philo->data = data;
	philo->start_time = start_time;
	philo->id = id;
	philo->nb_eaten = 0;
	philo->fork_left = &data->forks[id];
	philo->fork_right = &data->forks[(id + 1) % data->number_of_philo];
}

int	main(int argc, char **argv)
{
	t_data			data;
	pthread_t		tid[100000];
	int				i;
	t_time			start_time;
	t_philo			philo;

	if (input_check(argc, argv))
		return (1);
	i = 0;
	fill_struct(&data, argv, argc);
	gettimeofday(&start_time, NULL);
	printf("number of philos: %i\ntime to die: %d\ntime to eat: %d\ntime to sleep %d\nhow much eat: %d\n", data.number_of_philo, data.time_to_die, data.time_to_eat, data.time_to_sleep, data.how_much_eat);
	while (i < data.number_of_philo)
	{
		philo = *(t_philo *)malloc(sizeof(philo));
		init_philosopher(&philo, &data, &start_time, i);
		if (pthread_create(&tid[i], NULL, &philosopher, &philo) != 0)
			printf("thread broky\n");
		i++;
	}
	while (i >= 0)
	{
		pthread_join(tid[i], NULL);
		i--;
	}
	return (0);
}
