/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoll <mdoll@stduent.42wolfsburg>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 10:20:15 by mdoll             #+#    #+#             */
/*   Updated: 2023/04/27 10:49:05 by mdoll            ###   ########.fr       */
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
	data->finished = true;
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
			if (get_time_stamp(start_time) - philo_arr[i]->last_time_eaten >= data->time_to_die && philo_arr[i]->last_time_eaten != 0)
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
	i = 0;
	fill_struct(&data, argv, argc);
	gettimeofday(&start_time, NULL);
	philo_arr = init_philosopher(&data, &start_time);
	while (i < data.number_of_philo)
	{
		if (pthread_create(&data.tid[i], NULL, &philosopher, philo_arr[i]))
		{
			printf("failed to initialize thread\n");
			break ;
		}
		i++;
	}
	check_if_ded(philo_arr, &data, start_time);
	i = 0;
	while (i < data.number_of_philo)
		pthread_join(data.tid[i++], NULL);
	free_philo(philo_arr);
	return (0);
}

// TODO special case 1 philo or 0 times to eat
// TODO norm refactor
// TODO If a number for minimum eat is set, dont stop but eat until everybody is finished
// TODO 5 800 200 200 is fucked
// TODO 4 310 200 100 data-races