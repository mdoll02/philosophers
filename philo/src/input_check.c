/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoll <mdoll@stduent.42wolfsburg>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 11:16:17 by mdoll             #+#    #+#             */
/*   Updated: 2023/04/20 09:54:20 by mdoll            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <limits.h>

int	input_check(int argc, char **argv)
{
	long	num;

	if (argc < 5 || argc > 6)
		return (printf("invalid number of parameters\n"), 1);
	argv++;
	while (argc-- > 1)
	{
		num = atolong(*argv);
		if (num == 0 || num < 0 || num > INT_MAX)
			return (printf("Input is invalid\n"), 1);
		argv++;
	}
	return (0);
}
