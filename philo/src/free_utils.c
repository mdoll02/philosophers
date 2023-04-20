/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoll <mdoll@stduent.42wolfsburg>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 09:49:21 by mdoll             #+#    #+#             */
/*   Updated: 2023/04/20 09:54:14 by mdoll            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>

void	free_data(t_data *data)
{
	while (data->number_of_philo--)
		pthread_mutex_destroy(&data->forks[data->number_of_philo]);
	free(data->forks);
	free(data->tid);
	pthread_mutex_destroy(&data->display);
}

void	free_philo(t_philo **philo)
{
	free_data((*philo)->data);
	free(*philo);
}
