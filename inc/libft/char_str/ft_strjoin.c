/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acancel <acancel@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 16:51:48 by acancel           #+#    #+#             */
/*   Updated: 2024/05/28 17:35:08 by acancel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char		*dest;
	size_t		len_s1;
	size_t		len_s2;

	if (!s1 || !s2)
		return (NULL);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	dest = ft_calloc(len_s1 + len_s2 + 1, sizeof(char));
	if (dest == NULL)
		return (NULL);
	ft_memcpy(dest, s1, len_s1);
	ft_memcpy(dest + len_s1, s2, len_s2);
	return (dest);
}

char	*ft_charjoin(char const *s1, char const s2)
{
	char		*dest;
	size_t		len_s1;

	if (!s1 || !s2)
		return (NULL);
	len_s1 = ft_strlen(s1);
	dest = ft_calloc(len_s1 + 2, sizeof(char));
	if (dest == NULL)
		return (NULL);
	ft_memcpy(dest, s1, len_s1);
	ft_memcpy(dest + len_s1, &s2, 1);
	return (dest);
}
