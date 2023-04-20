/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoll <mdoll@stduent.42wolfsburg>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 11:55:01 by mdoll             #+#    #+#             */
/*   Updated: 2023/04/20 11:55:01 by mdoll            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "philo.h"
#include <pthread/pthread.h>
#include <strings.h>
#include <stdlib.h>

int	fill_struct(t_data *data, char **argv, int argc)
{
	int	i;

	data->number_of_philo = (int) atolong(argv[1]);
	data->time_to_die = (int) atolong(argv[2]);
	data->time_to_eat = (int) atolong(argv[3]);
	data->time_to_sleep = (int) atolong(argv[4]);
	data->how_much_eat = -1;
	if (argc == 6)
		data->how_much_eat = (int) atolong(argv[5]);
	i = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->number_of_philo);
	if (!data->forks)
		return (1);
	while (i < data->number_of_philo)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&data->forks[i]);
			printf("mutex init failed\n");
			return (free(data->forks), 1);
		}
		i++;
	}
	data->tid = (pthread_t *)malloc(data->number_of_philo * sizeof(pthread_t));
	if (!data->tid)
	{
		while (--i >= 0)
			pthread_mutex_destroy(&data->forks[i]);
		return (free(data->forks), 1);
	}
	if (pthread_mutex_init(&data->display, NULL) != 0)
	{
		while (--i >= 0)
			pthread_mutex_destroy(&data->forks[i]);
		printf("mutex init failed\n");
		return (1);
	}
	return (0);
}

t_philo	*init_philosopher(t_data *data, t_time *start_time)
{
	unsigned int	id;
	t_philo			*philo_arr;

	id = 0;
	philo_arr = (t_philo *)malloc(sizeof (t_philo) * data->number_of_philo);
	if (!philo_arr)
		return (free_data(data), NULL);
	while (id < (unsigned int)data->number_of_philo)
	{
		philo_arr[id].data = data;
		philo_arr[id].start_time = start_time;
		philo_arr[id].id = id;
		philo_arr[id].nb_eaten = 0;
		philo_arr[id].fork_left = &data->forks[id];
		philo_arr[id].fork_right = &data->forks[(id + 1) % data->number_of_philo];
		philo_arr[id].display = &data->display;
		philo_arr[id].is_ded = false;
		philo_arr[id].last_time_eaten = 0;
		id++;
	}
	return (philo_arr);
}
