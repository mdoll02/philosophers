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

void	*philosopher(void *arg)
{
	struct timeval	cur_time;
	struct timeval	start_time;

	start_time = *(struct timeval *)arg;
	gettimeofday(&cur_time, NULL);
	printf("My creation was at: %ld Seconds and %d microseconds\n", cur_time.tv_sec, cur_time.tv_usec);
	usleep(1000);
	gettimeofday(&cur_time, NULL);
	printf("My creation was %ld ms milliseconds ago\n", ((cur_time.tv_usec - start_time.tv_usec) / 1000) + ((cur_time.tv_sec - start_time.tv_sec) * 1000));
	return (NULL);
}
