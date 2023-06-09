/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoll <mdoll@stduent.42wolfsburg>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 10:11:28 by mdoll             #+#    #+#             */
/*   Updated: 2023/04/27 11:14:23 by mdoll            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
# include <sys/time.h>

typedef struct timeval	t_time;

typedef struct s_data
{
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				how_much_eat;
	int				number_of_philo;
	bool			finished;
	pthread_mutex_t	*forks;
	pthread_t		*tid;
	pthread_mutex_t	death;
	pthread_mutex_t	mut_finished;
}		t_data;

typedef struct s_philo
{
	pthread_mutex_t	*fork_left;
	pthread_mutex_t	*fork_right;
	pthread_mutex_t	*death;
	t_data			*data;
	t_time			start_time;
	int				nb_eaten;
	int				last_time_eaten;
	unsigned int	id;
}		t_philo;

int		input_check(int argc, char **argv);
long	atolong(const char	*str);
void	*philosopher(void *arg);
void	free_philo(t_philo **philo, int nb_of_philo);
void	free_data(t_data *data);
t_philo	**init_philosopher(t_data *data, t_time *start_time);
int		fill_struct(t_data *data, char **argv, int argc);

#endif