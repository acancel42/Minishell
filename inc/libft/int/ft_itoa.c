/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talibert <talibert@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 15:05:19 by acancel           #+#    #+#             */
/*   Updated: 2024/05/21 19:18:51 by talibert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static size_t	ft_decade_size(int n, size_t i)
{
	if (n == 0)
		i++;
	if (n < 0)
	{
		n = -n;
		i++;
	}
	while (n > 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	size_t	i;
	char	*nb;

	i = 0;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	i = ft_decade_size(n, i);
	nb = ft_calloc(i + 1, sizeof(char));
	if (nb == NULL)
		return (NULL);
	if (n < 0)
	{
		n = -n;
		nb[0] = '-';
	}
	while (n > 9)
	{
		nb[i - 1] = n % 10 + '0';
		i--;
		n = n / 10;
	}
	nb[i - 1] = n + '0';
	return (nb);
}
/* [i - 1] because a len start at 1 */
