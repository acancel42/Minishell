/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprint_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talibert <talibert@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 17:13:07 by acancel           #+#    #+#             */
/*   Updated: 2024/05/21 19:18:51 by talibert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_dprint_char(char c)
{
	return (write(2, &c, 1));
}

int	ft_dprint_str(char *s)
{
	ssize_t	len;
	ssize_t	count;
	ssize_t	count_temp;

	len = 0;
	count = 0;
	count_temp = 0;
	if (!s)
		return (write(2, "(null)", 6));
	len = ft_strlen_ft_printf(s);
	if (len == -1)
		return (-1);
	while (count < len)
	{
		count_temp = (write(2, s + count, len - count));
		if (count_temp == -1)
			return (-1);
		count += count_temp;
	}
	return (count);
}
