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

void	*philosopher(void *arg)
{
	t_time	start_time;

	start_time = *(t_time *)arg;
	printf("%dms\n", get_time_stamp(start_time));
	return (NULL);
}
