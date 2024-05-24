/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talibert <talibert@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 20:53:41 by acancel           #+#    #+#             */
/*   Updated: 2024/05/21 19:17:51 by talibert         ###   ########.fr       */
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
