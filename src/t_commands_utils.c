#include "minishell.h"

t_commands	*ft_cmdnew(int flag)
{
	t_commands	*new;
	static int	i;

	new = ft_calloc(1, sizeof(t_commands));
	if (!new)
		return (NULL);
	if (!flag)
		i = 0;
	new->next = NULL;
	new->path = NULL;
	new->valid_path = 0;
	new->name = NULL;
	new->index = i;
	new->infile_fd = 0;
	new->outfile_fd = 1;
	i++;
	return (new);
}

static	t_commands	*ft_cmdlast(t_commands *lst)
{
	while (lst && lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	ft_cmdadd_back(t_commands **lst, t_commands *new)
{
	t_commands	*temp;

	if (!lst || !new)
		return ;
	temp = ft_cmdlast(*lst);
	if (temp != NULL)
		temp->next = new;
	else
		*lst = new;
}

void	ft_cmdsdelone(t_commands *cmds)
{
	if (cmds->name)
		free(cmds->name);
	if (cmds->path)
		free(cmds->path);
	if (cmds->redirections)
		ft_free_tab(cmds->redirections);
	if (cmds->args)
		ft_free_tab(cmds->args);
	free(cmds);
}

void	ft_cmdsclear(t_commands **lst)
{
	t_commands	*temp;

	temp = NULL;
	while (*lst)
	{
		temp = (*lst)->next;
		ft_cmdsdelone(*lst);
		*lst = temp;
	}
}
