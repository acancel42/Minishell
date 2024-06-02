#include "../inc/minishell.h"

t_file	*ft_filenew(char *content)
{
	t_file *new = ft_calloc(1, sizeof(t_file));
	new->next = NULL;
	new->fd = 0;
	new->state = false;
	new->name = ft_strdup(content);
	return (new);
}

static t_file *ft_filelast(t_file *lst) {
	while (lst && lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	ft_fileadd_back(t_file **lst, t_file *new)
{
	if (!lst || !new)
		return;
	t_file *temp = ft_filelast(*lst);
	if (temp != NULL)
		temp->next = new;
	else
		*lst = new;
}
