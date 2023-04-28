/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoll <mdoll@stduent.42wolfsburg>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 14:55:04 by mdoll             #+#    #+#             */
/*   Updated: 2023/04/20 09:54:35 by mdoll            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "philo.h"
#include "color.h"
#include "msg.h"
#include "philo_helpers.h"

static void	eat_n_sleep(t_philo *philo)
{
	pthread_mutex_lock(philo->death);
	philo->last_time_eaten = get_time_stamp(philo->start_time);
	philo->nb_eaten++;
	pthread_mutex_unlock(philo->death);
	print_msg(philo, EAT, RED);
	usleep(philo->data->time_to_eat * 1000);
	fork_unlock(philo);
	print_msg(philo, SLEEP, BLU);
	usleep(philo->data->time_to_sleep * 1000);
}

void	*philosopher(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->data->mut_finished);
	while (philo->data->finished == false)
	{
		pthread_mutex_unlock(&philo->data->mut_finished);
		if (fork_lock(philo) == false)
		{
			usleep(philo->data->time_to_die * 1000);
			break ;
		}
		eat_n_sleep(philo);
		print_msg(philo, THINK, GRN);
		if (get_time_stamp(philo->start_time) + philo->data->time_to_eat \
			< philo->data->time_to_die)
			usleep(philo->data->time_to_eat * 1000);
		pthread_mutex_lock(&philo->data->mut_finished);
	}
	pthread_mutex_unlock(&philo->data->mut_finished);
	return (NULL);
}

//TODO: is_ded checks everywhere