/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoll <mdoll@stduent.42wolfsburg>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 10:20:15 by mdoll             #+#    #+#             */
/*   Updated: 2023/04/27 14:37:04 by mdoll            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "philo.h"
#include <strings.h>
#include <sys/time.h>
#include "philo_helpers.h"
#include <msg.h>
#include <color.h>

static void	end_stuff(t_philo **philo_arr, t_data *data, int phil_num, bool prt)
{
	if (prt)
		print_msg(philo_arr[phil_num], DIE, END);
	else
		printf(ALL_ATE, data->how_much_eat);
	pthread_mutex_lock(&data->mut_finished);
	data->finished = true;
	pthread_mutex_unlock(&data->mut_finished);
}

static void	check_if_ded(t_philo **philo_arr, t_data *data, t_time start_time)
{
	int		i;
	bool	all_ate;

	while (!data->finished)
	{
		all_ate = true;
		i = 0;
		while (i < data->number_of_philo && !data->finished)
		{
			pthread_mutex_lock(&data->death);
			all_ate &= (philo_arr[i]->nb_eaten >= data->how_much_eat
					&& data->how_much_eat != 0);
			if (get_time_stamp(start_time) - philo_arr[i]->last_time_eaten >= \
						data->time_to_die && philo_arr[i]->last_time_eaten != 0)
				end_stuff(philo_arr, data, i, true);
			pthread_mutex_unlock(&data->death);
			i++;
		}
		if (all_ate)
			end_stuff(philo_arr, data, i, false);
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
	if (fill_struct(&data, argv, argc))
		return (1);
	gettimeofday(&start_time, NULL);
	philo_arr = init_philosopher(&data, &start_time);
	if (!philo_arr)
		return (1);
	i = -1;
	while (++i < data.number_of_philo)
		pthread_create(&data.tid[i], NULL, &philosopher, philo_arr[i]);
	if (data.number_of_philo)
		check_if_ded(philo_arr, &data, start_time);
	while (--i >= 0)
		pthread_join(data.tid[i], NULL);
	if (data.number_of_philo)
		free_philo(philo_arr, data.number_of_philo);
	return (0);
}
