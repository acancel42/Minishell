/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acancel <acancel@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 14:51:19 by Acancel           #+#    #+#             */
/*   Updated: 2023/11/27 15:01:05 by acancel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int	ft_check_int_overflow(int nbr, int sign, size_t i, const char *str);

int	ft_atoi(const char *str)
{
	long	nbr;
	int		sign;
	size_t	i;

	nbr = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -sign;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (nbr != ft_check_int_overflow(nbr, sign, i, str))
			return (ft_check_int_overflow(nbr, sign, i, str));
		nbr = nbr * 10 + str[i] - '0';
		i++;
	}
	return (nbr * sign);
}

int	ft_check_int_overflow(int nbr, int sign, size_t i, const char *str)
{
	if (((nbr * 10 + str[i] - 48) / 10) != nbr)
	{
		if (sign < 0)
			return ((int)LONG_MIN);
		return ((int)LONG_MAX);
	}
	return (nbr);
}
