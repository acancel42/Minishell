/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talibert <talibert@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 15:21:50 by acancel           #+#    #+#             */
/*   Updated: 2024/05/21 19:18:51 by talibert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_lstsize(t_list *lst)
{
	int	i;

	i = 0;
	if (lst != NULL)
	{
		while (lst != NULL)
		{
			i++;
			lst = lst->next;
		}
	}
	return (i);
}
