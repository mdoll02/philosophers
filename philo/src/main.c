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
#include <pthread/pthread.h>
#include <strings.h>
#include <unistd.h>

static void	fill_struct(t_philo *phil, char **argv, int argc)
{
	phil->number_of_philo = (int)atolong(argv[1]);
	phil->time_to_die = (int)atolong(argv[2]);
	phil->time_to_eat = (int)atolong(argv[3]);
	phil->time_to_sleep = (int)atolong(argv[4]);
	if (argc == 6)
		phil->how_much_eat = (int)atolong(argv[5]);
	else
		phil->how_much_eat = -1;
}

void	*do_some_thing(void *arg)
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

int	main(int argc, char **argv)
{
	t_philo			phil;
	pthread_t		tid[100000];
	int				i;
	struct timeval	start_time;

	if (input_check(argc, argv))
		return (1);
	i = 0;
	fill_struct(&phil, argv, argc);
	gettimeofday(&start_time, NULL);
	printf("number of philos: %i\ntime to die: %d\ntime to eat: %d\ntime to sleep %d\nhow much eat: %d\n", phil.number_of_philo, phil.time_to_die, phil.time_to_eat, phil.time_to_sleep, phil.how_much_eat);
	while (i < phil.number_of_philo)
	{
		if (pthread_create(&tid[i], NULL, &do_some_thing, &start_time) != 0)
			printf("thread broky\n");
		i++;
	}
	while (i >= 0)
	{
		pthread_join(tid[i], NULL);
		i--;
	}
	return (0);
}
