/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoll <mdoll@stduent.42wolfsburg>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 11:55:01 by mdoll             #+#    #+#             */
/*   Updated: 2023/04/27 14:35:46 by mdoll            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "philo.h"
#include <strings.h>
#include <stdlib.h>

static void	destroy(int i, t_data *data, bool mutex)
{
	while (--i >= 0)
		pthread_mutex_destroy(&data->forks[i]);
	if (mutex)
		printf("mutex init failed\n");
}

static void	free_stuff(int i, t_data *data, bool mutex)
{
	destroy(i, data, mutex);
	if (data->forks)
		free(data->forks);
	if (data->tid)
		free(data->tid);
}

int	fill_struct(t_data *data, char **argv, int argc)
{
	int	i;

	data->finished = false;
	data->number_of_philo = (int) atolong(argv[1]);
	data->time_to_die = (int) atolong(argv[2]);
	data->time_to_eat = (int) atolong(argv[3]);
	data->time_to_sleep = (int) atolong(argv[4]);
	data->how_much_eat = 0;
	if (argc == 6)
		data->how_much_eat = (int) atolong(argv[5]);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->number_of_philo);
	if (!data->forks)
		return (1);
	i = -1;
	while (++i < data->number_of_philo)
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (destroy(i, data, true), free(data->forks), 1);
	data->tid = (pthread_t *)malloc(data->number_of_philo * sizeof(pthread_t));
	if (!data->tid)
		return (free_stuff(i, data, false), 1);
	if (pthread_mutex_init(&data->death, NULL)
		|| pthread_mutex_init(&data->mut_finished, NULL))
		return (free_stuff(i, data, true), \
				pthread_mutex_destroy(&data->death), 1);
	return (0);
}

static t_philo	*set_values(int id, t_data *data, t_time *start_time)
{
	t_philo	*philo;

	philo = (t_philo *)malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->data = data;
	philo->start_time = *start_time;
	philo->id = id;
	philo->nb_eaten = 0;
	philo->fork_left = &data->forks[id];
	philo->fork_right = &data->forks[(id + 1) % data->number_of_philo];
	philo->last_time_eaten = 0;
	philo->death = &data->death;
	return (philo);
}

t_philo	**init_philosopher(t_data *data, t_time *start_time)
{
	int				id;
	t_philo			**philo_arr;

	id = 0;
	philo_arr = (t_philo **)malloc(sizeof (t_philo *) * data->number_of_philo);
	if (!philo_arr)
		return (free_data(data), NULL);
	while (id < data->number_of_philo)
	{
		philo_arr[id] = set_values(id, data, start_time);
		if (!philo_arr[id])
			return (free_philo(philo_arr, data->number_of_philo), NULL);
		id++;
	}
	return (philo_arr);
}
