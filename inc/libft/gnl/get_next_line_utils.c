/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talibert <talibert@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 11:58:30 by acancel           #+#    #+#             */
/*   Updated: 2024/05/21 19:18:51 by talibert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char		*dest;
	size_t		len;
	size_t		i;
	size_t		j;

	len = ft_strlen_or_len_to_nl(s1);
	len += ft_strlen_or_len_to_nl(s2);
	dest = malloc((len + 1) * sizeof(char));
	if (dest == NULL)
		return (NULL);
	dest[len] = '\0';
	i = 0;
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
	free (s1);
	return (dest);
}

size_t	ft_is_strchr(const char *str, char c)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	if (str[i] == c)
		return (1);
	return (0);
}

size_t	ft_strlen_or_len_to_nl(char *s)
{
	size_t	i;

	i = 0;
	while (s && s[i])
	{
		i++;
		if (s[i - 1] == '\n')
			break ;
	}
	return (i);
}
