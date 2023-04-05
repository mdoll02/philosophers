/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoll <mdoll@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 11:16:17 by mdoll             #+#    #+#             */
/*   Updated: 2023/04/05 11:16:17 by mdoll            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <limits.h>

static int	ft_checkwhitespaces(char *str, int i)
{
	if (str[i] == '\n' || str[i] == ' '
		|| str[i] == '\t' || str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
	{
		return (1);
	}
	else
		return (0);
}

static int	ft_checkfirstdigit(char *str, int i)
{
	if (str[i] == '-')
		return (1);
	else if (str[i] == '+')
		return (2);
	else if (str[i] > '9' || str[i] < '0')
		return (-1);
	else
		return (0);
}

static long	atolong(const char	*str)
{
	int		i;
	long	returnv;
	int		isnegative;
	char	*s;

	s = (char *) str;
	i = 0;
	returnv = 0;
	while (ft_checkwhitespaces(s, i))
		i++;
	isnegative = ft_checkfirstdigit(s, i);
	if (isnegative == -1)
		return (0);
	else if (isnegative == 1)
		i++;
	else if (isnegative == 2)
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		returnv = returnv * 10 + str[i] - 48;
		i++;
	}
	if (isnegative == 1)
		returnv *= -1;
	return (returnv);
}

int	input_check(int argc, char **argv)
{
	long	num;

	if (argc < 5 || argc > 6)
		return (printf("invalid number of parameters\n"), 1);
	(*argv)++;
	while (argc-- > 1)
	{
		num = atolong(*argv);
		if (num > INT_MAX)
			return (printf("%s needs to be in integer range\n", *argv), 1);
		else if (num < 0)
			return (printf("%s needs to be a positive number\n", *argv), 1);
		printf("num: %ld\n", num);
		(*argv)++;
	}
	return (0);
}
