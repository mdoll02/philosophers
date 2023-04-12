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
#include <sys/time.h>

static void	fill_struct(t_philo *phil, char **argv, int argc)
{
	t_table	tb;

	tb.number_of_philo = (int)atolong(argv[1]);
	phil->tb = &tb;
	phil->time_to_die = (int)atolong(argv[2]);
	phil->time_to_eat = (int)atolong(argv[3]);
	phil->time_to_sleep = (int)atolong(argv[4]);
	if (argc == 6)
		phil->how_much_eat = (int)atolong(argv[5]);
	else
		phil->how_much_eat = -1;
}

int	main(int argc, char **argv)
{
	t_philo			phil;
	struct timeval	cur_time;

	if (input_check(argc, argv))
		return (1);
	fill_struct(&phil, argv, argc);
	printf("number of philos: %d\ntime to die: %d\ntime to eat: %d\ntime to sleep %d\nhow much eat: %d\n", phil.tb->number_of_philo, phil.time_to_die, phil.time_to_eat, phil.time_to_sleep, phil.how_much_eat);
	gettimeofday(&cur_time, NULL);
	printf("seconds: %ld\nmicroseconds: %d", cur_time.tv_sec, cur_time.tv_usec);
	return (0);
}
