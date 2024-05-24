/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talibert <talibert@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 14:33:44 by acancel           #+#    #+#             */
/*   Updated: 2024/05/21 19:18:51 by talibert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size == 0)
		return (ft_strlen((char *)src));
	while (src && src[i] && i < (size - 1))
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return (ft_strlen((char *)src));
}
