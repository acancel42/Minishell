/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talibert <talibert@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 17:13:07 by acancel           #+#    #+#             */
/*   Updated: 2024/05/21 19:18:51 by talibert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_print_char(char c)
{
	return (write(1, &c, 1));
}

size_t	ft_strlen_ft_printf(const char *str)
{
	size_t	i;

	i = 0;
	while (str && str[i])
	{
		i++;
		if (i > 2147483647)
			return (-1);
	}
	return (i);
}

int	ft_print_str(char *s)
{
	ssize_t	len;
	ssize_t	count;
	ssize_t	count_temp;

	len = 0;
	count = 0;
	count_temp = 0;
	if (!s)
		return (write(1, "(null)", 6));
	len = ft_strlen_ft_printf(s);
	if (len == -1)
		return (-1);
	while (count < len)
	{
		count_temp = (write(1, s + count, len - count));
		if (count_temp == -1)
			return (-1);
		count += count_temp;
	}
	return (count);
}
