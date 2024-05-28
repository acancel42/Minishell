/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acancel <acancel@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 20:53:41 by acancel           #+#    #+#             */
/*   Updated: 2024/05/28 17:29:37 by acancel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strdup(const char *s)
{
	size_t	size;
	char	*dest;

	size = ft_strlen(s);
	dest = ft_calloc(size + 1, sizeof(char));
	if (dest == NULL)
		return (NULL);
	dest = ft_memcpy(dest, s, size);
	return (dest);
}

char	*ft_chardup(const char c)
{
	size_t	size;
	char	*dest;

	size = 1;
	dest = ft_calloc(size + 1, sizeof(char));
	if (dest == NULL)
		return (NULL);
	dest = ft_memcpy(dest, &c, size);
	return (dest);
}
