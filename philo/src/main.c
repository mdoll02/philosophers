/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoll <mdoll@stduent.42wolfsburg>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 10:20:15 by mdoll             #+#    #+#             */
/*   Updated: 2023/04/20 09:54:28 by mdoll            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "philo.h"
#include <pthread/pthread.h>
#include <strings.h>
#include <sys/time.h>

int	main(int argc, char **argv)
{
	t_data			data;
	int				i;
	t_time			start_time;
	t_philo			*philo_arr;

	if (input_check(argc, argv))
		return (1);
	i = 0;
	fill_struct(&data, argv, argc);
	gettimeofday(&start_time, NULL);
	philo_arr = init_philosopher(&data, &start_time);
	while (i < data.number_of_philo)
	{
		if (pthread_create(&data.tid[i], NULL, &philosopher, &philo_arr[i]) != 0)
			printf("thread broky\n");
		i++;
	}
	i = 0;
	while (i < data.number_of_philo)
	{
		pthread_join(data.tid[i++], NULL);
	}
	free_philo(&philo_arr);
	return (0);
}
