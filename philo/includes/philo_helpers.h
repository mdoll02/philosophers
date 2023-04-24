/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_helpers.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoll <mdoll@stduent.42wolfsburg>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 11:23:29 by mdoll             #+#    #+#             */
/*   Updated: 2023/04/21 11:23:37 by mdoll            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_HELPERS_H
# define PHILO_HELPERS_H

void	fork_unlock(t_philo *philo);
void	fork_lock(t_philo *philo);
int		get_time_stamp(t_time start_time);
void	print_msg(t_philo *philo, char *msg, char *color);

#endif
