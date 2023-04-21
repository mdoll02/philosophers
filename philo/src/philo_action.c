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
	pthread_mutex_lock(philo->display);
	printf(RED"%u %u"EAT END, get_time_stamp(*philo->start_time), philo->id);
	pthread_mutex_unlock(philo->display);
	usleep(philo->data->time_to_eat * 1000);
	philo->nb_eaten++;
	fork_unlock(philo);
	pthread_mutex_lock(philo->display);
	printf(BLU"%u %u"SLEEP END, get_time_stamp(*philo->start_time), philo->id);
	pthread_mutex_unlock(philo->display);
	usleep(philo->data->time_to_sleep * 1000);
}

void	*philosopher(void *arg)
{
	t_philo	philo;

	philo = *(t_philo *) arg;
	while (philo.is_ded == false)
	{
		fork_lock(&philo);
		eat_n_sleep(&philo);
		pthread_mutex_lock(philo.display);
		printf(GRN"%u %u"THINK END, get_time_stamp(*philo.start_time), philo.id);
		pthread_mutex_unlock(philo.display);
		if (philo.nb_eaten == philo.data->how_much_eat)
			break ;
	}
	return (NULL);
}
