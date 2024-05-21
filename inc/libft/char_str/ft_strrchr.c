/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acancel <acancel@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 15:42:42 by acancel           #+#    #+#             */
/*   Updated: 2023/11/24 13:19:03 by acancel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	size_t	i;

	i = ft_strlen((char *)str);
	while (i > 0 && str[i] != (unsigned char)c)
		i--;
	if (str[i] == (unsigned char)c)
	{
		return ((char *)(str + i));
	}
	return (NULL);
}
