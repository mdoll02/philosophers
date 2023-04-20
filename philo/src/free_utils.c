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
	free(data->forks);
	free(data->tid);
}

void	free_philo(t_philo **philo)
{
	free_data((*philo)->data);
	free(*philo);
}
