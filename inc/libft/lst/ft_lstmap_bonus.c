/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talibert <talibert@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 16:43:00 by acancel           #+#    #+#             */
/*   Updated: 2024/05/21 19:18:51 by talibert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*temp;
	t_list	*lstdup;
	void	*tempcontent;

	lstdup = NULL;
	while (lst)
	{
		tempcontent = f(lst->content);
		if (tempcontent == NULL)
		{
			ft_lstclear(&lstdup, (*del));
			return (NULL);
		}
		temp = ft_lstnew(tempcontent);
		if (temp == NULL)
		{
			ft_lstclear(&lstdup, (*del));
			del(tempcontent);
			return (NULL);
		}
		ft_lstadd_back(&lstdup, temp);
		lst = lst->next;
	}
	return (lstdup);
}
