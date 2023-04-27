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
	pthread_mutex_unlock(philo->death);
	print_msg(philo, EAT, RED);
	usleep(philo->data->time_to_eat * 1000);
	philo->nb_eaten++;
	fork_unlock(philo);
	print_msg(philo, SLEEP, BLU);
	usleep(philo->data->time_to_sleep * 1000);
}

void	*philosopher(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (philo->data->finished == false)
	{
		fork_lock(philo);
		eat_n_sleep(philo);
		print_msg(philo, THINK, GRN);
	}
	return (NULL);
}

//TODO: is_ded checks everywhere