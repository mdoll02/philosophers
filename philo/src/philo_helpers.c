/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoll <mdoll@stduent.42wolfsburg>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 11:22:28 by mdoll             #+#    #+#             */
/*   Updated: 2023/04/21 11:22:28 by mdoll            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "stdio.h"
#include "msg.h"
#include "color.h"
#include <sys/time.h>
#include "philo_helpers.h"

int	get_time_stamp(t_time start_time)
{
	t_time	cur_time;
	int		ms;
	long	s;

	gettimeofday(&cur_time, NULL);
	ms = (cur_time.tv_usec - start_time.tv_usec) / 1000;
	s = (cur_time.tv_sec - start_time.tv_sec) * 1000;
	return (ms + (int)s);
}

void	fork_unlock(t_philo **philo)
{
	if ((*philo)->id % 2 == 1)
	{
		pthread_mutex_unlock((*philo)->fork_left);
		pthread_mutex_unlock((*philo)->fork_right);
	}
	else
	{
		pthread_mutex_unlock((*philo)->fork_right);
		pthread_mutex_unlock((*philo)->fork_left);
	}
}

void	fork_lock(t_philo **philo)
{
	if ((*philo)->id % 2 == 1)
	{
		pthread_mutex_lock((*philo)->fork_left);
		print_msg((*philo), FORK, MGT);
		pthread_mutex_lock((*philo)->fork_right);
		print_msg((*philo), FORK, MGT);
	}
	else
	{
		pthread_mutex_lock((*philo)->fork_right);
		print_msg((*philo), FORK, MGT);
		pthread_mutex_lock((*philo)->fork_left);
		print_msg((*philo), FORK, MGT);
	}
}

void	print_msg(t_philo *philo, char *msg, char *color)
{
	int	time;

	pthread_mutex_lock(philo->death);
	if (philo->is_ded == false)
	{
		time = get_time_stamp(*philo->start_time);
		pthread_mutex_lock(philo->display);
		printf("%s""%u %u""%s" END, color, time, philo->id, msg);
		pthread_mutex_unlock(philo->display);
	}
	pthread_mutex_unlock(philo->death);
}
