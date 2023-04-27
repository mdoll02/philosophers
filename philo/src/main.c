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
#include "philo_helpers.h"
#include <msg.h>
#include <color.h>

static void	end_stuff(t_philo ***philo_arr, t_data *data, int phil_num)
{
	int	i;

	i = 0;
	print_msg((*philo_arr)[phil_num], DIE, END);
	while (i < data->number_of_philo)
	{
		(*philo_arr)[i]->is_ded = true;
		i++;
	}
}

static void	check_if_ded(t_philo ***philo_arr, t_data *data, t_time start_time)
{
	int		i;

	while (1)
	{
		i = 0;
		while (i < data->number_of_philo)
		{
			pthread_mutex_lock(&data->death);
			if (get_time_stamp(start_time) - (*philo_arr)[i]->last_time_eaten >= data->time_to_die && (*philo_arr)[i]->last_time_eaten != 0)
			{
				end_stuff(philo_arr, data, i);
				pthread_mutex_unlock(&data->death);
				return ;
			}
			pthread_mutex_unlock(&data->death);
			i++;
		}
	}
}

int	main(int argc, char **argv)
{
	t_data			data;
	int				i;
	t_time			start_time;
	t_philo			**philo_arr;

	if (input_check(argc, argv))
		return (1);
	i = 0;
	fill_struct(&data, argv, argc);
	gettimeofday(&start_time, NULL);
	philo_arr = init_philosopher(&data, &start_time);
	while (i < data.number_of_philo)
	{
		if (pthread_create(&data.tid[i], NULL, &philosopher, \
										philo_arr[i]) != 0)
		{
			printf("failed to initialize thread\n");
			break ;
		}
		i++;
	}
	check_if_ded(&philo_arr, &data, start_time);
	i = 0;
	while (i < data.number_of_philo)
		pthread_join(data.tid[i++], NULL);
	free_philo(philo_arr);
	return (0);
}
