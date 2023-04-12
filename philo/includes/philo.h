/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoll <mdoll@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 10:11:28 by mdoll             #+#    #+#             */
/*   Updated: 2023/04/05 10:11:28 by mdoll            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

typedef struct s_table
{
	int		number_of_philo;
}		t_table;

typedef struct s_philo
{
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		how_much_eat;
	t_table	tb;
}		t_philo;

int	input_check(int argc, char **argv);

#endif