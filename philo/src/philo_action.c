/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoll <mdoll@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 14:55:04 by mdoll             #+#    #+#             */
/*   Updated: 2023/04/13 14:55:04 by mdoll            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
#include "philo.h"

static int	get_time_stamp(t_time start_time)
{
	t_time	cur_time;
	int		ms;
	long	s;

	gettimeofday(&cur_time, NULL);
	ms = (cur_time.tv_usec - start_time.tv_usec) / 1000;
	s = (cur_time.tv_sec - start_time.tv_sec) * 1000;
	return (ms + (int)s);
}

static void	eat_n_sleep(t_philo *philo)
{
	printf("%u %u is eating\n", get_time_stamp(*philo->start_time), philo->id);
	usleep(philo->data->time_to_eat * 1000);
	philo->nb_eaten++;
	printf("%u %u is sleeping\n", get_time_stamp(*philo->start_time), philo->id);
	usleep(philo->data->time_to_sleep * 1000);
}

void	*philosopher(void *arg)
{
	t_philo	philo;

	philo = *(t_philo *) arg;
	while (philo.nb_eaten < philo.data->how_much_eat)
	{
		if (philo.id % 2 == 0)
		{
			pthread_mutex_lock(philo.fork_left);
			pthread_mutex_lock(philo.fork_right);
		}
		else
		{
			pthread_mutex_lock(philo.fork_right);
			pthread_mutex_lock(philo.fork_left);
		}
		eat_n_sleep(&philo);
		pthread_mutex_unlock(philo.fork_left);
		pthread_mutex_unlock(philo.fork_right);
		printf("%u %u is thinking\n", get_time_stamp(*philo.start_time), philo.id);
	}
	return (NULL);
}
