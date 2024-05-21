/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acancel <acancel@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 19:10:23 by acancel           #+#    #+#             */
/*   Updated: 2024/03/19 19:12:48 by acancel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	nsize;
	void	*tab;

	if (nmemb == 0 || size == 0)
		return (malloc(0));
	if ((size * nmemb) / nmemb != size)
		return (NULL);
	nsize = nmemb * size;
	tab = malloc(nsize);
	if (tab == NULL)
		return (NULL);
	ft_bzero(tab, nsize);
	return (tab);
}
