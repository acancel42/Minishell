/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talibert <talibert@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 16:34:56 by acancel           #+#    #+#             */
/*   Updated: 2024/05/21 19:18:51 by talibert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static size_t	ft_count_word(char const *str, char c)
{
	size_t	i;
	size_t	word;

	i = 0;
	word = 0;
	while (str[i])
	{
		if (str[i] != c && (str[i + 1] == c || str[i + 1] == 0))
			word++;
		i++;
	}
	return (word);
}

static void	ft_free_all(char **arr)
{
	size_t	j;

	j = 0;
	while (arr[j])
	{
		free(arr[j]);
		j++;
	}
	free(arr);
}

static char	**ft_filling(size_t word, char **arr, char const *s, char c)
{
	size_t	i;
	size_t	start;
	size_t	lenword;

	i = 0;
	start = 0;
	while (i < word)
	{
		while (s[start] && s[start] == c)
			start++;
		lenword = start;
		while (s[lenword] && s[lenword] != c)
			lenword++;
		arr[i] = ft_substr(s, start, lenword - start);
		if (arr[i] == NULL)
		{
			ft_free_all(arr);
			return (NULL);
		}
		i++;
		start = lenword;
	}
	return (arr);
}

char	**ft_split(char const *s, char c)
{
	size_t	word;
	char	**arr;

	if (!s)
		return (NULL);
	word = ft_count_word(s, c);
	arr = ft_calloc (word + 1, sizeof(char *));
	if (arr == NULL)
		return (NULL);
	arr = ft_filling(word, arr, s, c);
	return (arr);
}
