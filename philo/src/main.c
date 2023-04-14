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
#include <pthread/pthread.h>
#include <strings.h>
#include <sys/time.h>

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

int	main(int argc, char **argv)
{
	t_philo			phil;
	pthread_t		tid[100000];
	int				i;
	t_time			start_time;

	if (input_check(argc, argv))
		return (1);
	i = 0;
	fill_struct(&phil, argv, argc);
	gettimeofday(&start_time, NULL);
	printf("number of philos: %i\ntime to die: %d\ntime to eat: %d\ntime to sleep %d\nhow much eat: %d\n", phil.number_of_philo, phil.time_to_die, phil.time_to_eat, phil.time_to_sleep, phil.how_much_eat);
	while (i < phil.number_of_philo)
	{
		if (pthread_create(&tid[i], NULL, &philosopher, &start_time) != 0)
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
