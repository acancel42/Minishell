#include "minishell.h"

t_commands *ft_cmdnew(char *user, int flag)
{
	t_commands *new = ft_calloc(1, sizeof(t_commands));
	static int	i;

	if (!flag)
		i = 0;
	new->next = NULL;
	new->path = NULL;
	new->valid_path = 0;
	new->name = NULL;
	new->index = i;
	new->infile_fd = 0;
	new->outfile_fd = 1;
	new->user = ft_strdup(user);
	i++;
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

void	ft_cmdsdelone(t_commands *cmds)
{
	if (cmds->name)
		free(cmds->name);
	if (cmds->path)
		free(cmds->path);
	if (cmds->redirections)
		ft_fileclear(&cmds->redirections);
	if (cmds->args)
		ft_free_tab(cmds->args);
	if(cmds->user)
		free(cmds->user);
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
