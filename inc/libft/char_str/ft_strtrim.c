/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acancel <acancel@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 18:54:56 by acancel           #+#    #+#             */
/*   Updated: 2023/11/25 16:59:28 by acancel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	start;
	size_t	end;

	i = 0;
	start = 0;
	if (!s1 || !set)
		return (NULL);
	end = ft_strlen(s1);
	while (ft_is_charset(s1[i], set) && s1[i])
	{
		start++;
		i++;
	}
	i = ft_strlen(s1) - 1;
	while (ft_is_charset(s1[i], set) && i > 0)
	{
		end--;
		i--;
	}
	return (ft_substr(s1, start, end - start));
}
