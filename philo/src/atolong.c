/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atolong.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoll <mdoll@stduent.42wolfsburg>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 10:17:41 by mdoll             #+#    #+#             */
/*   Updated: 2023/04/20 09:55:40 by mdoll            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

long	atolong(const char	*str)
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
	else if (isnegative == 1 || isnegative == 2)
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
