/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acancel <acancel@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 16:51:48 by acancel           #+#    #+#             */
/*   Updated: 2024/07/29 13:16:19 by acancel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strjoin(char *s1, char *s2, int flag)
{
	int			i;
	int			j;
	char		*dest;
	int			len;

	i = 0;
	len = ft_strlen(s1);
	len += ft_strlen(s2);
	dest = ft_calloc(len + 1, sizeof(char));
	if (dest == NULL)
		return (NULL);
	while (s1 && s1[i])
	{
		dest[i] = s1[i];
		i++;
	}
	j = 0;
	while (i + j < len)
	{
		dest[i + j] = s2[j];
		j++;
	}
	if (flag)
		free(s1);
	return (dest);
}

char	*ft_charjoin(char *s1, char const s2)
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
	free(s1);
	return (dest);
}
