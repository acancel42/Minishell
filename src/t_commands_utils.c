#include "minishell.h"

t_commands *ft_cmdnew(void)
{
	t_commands *new = ft_calloc(1, sizeof(t_commands));
	new->next = NULL;
	new->path = NULL;
	new->flags = NULL;
	new->valid_path = 0;
	new->name = NULL;
	return (new);
}

static t_commands *ft_cmdlast(t_commands *lst)
{
	while (lst && lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void ft_cmdadd_back(t_commands **lst, t_commands *new)
{
	if (!lst || !new)
		return;
	t_commands *temp = ft_cmdlast(*lst);
	if (temp != NULL)
		temp->next = new;
	else
		*lst = new;
}
