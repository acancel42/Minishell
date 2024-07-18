#include "minishell.h"

t_file	*ft_filenew(char *content, char *type)
{
	char	*temp;
	t_file	*new;

	new = ft_calloc(1, sizeof(t_file));
	if (!new)
		return (NULL);
	temp = ft_strdup(type);
	new->next = NULL;
	new->fd = 0;
	new->state = false;
	new->name = ft_strjoin(temp, content, 1);
	return (new);
}

static	t_file	*ft_filelast(t_file *lst)
{
	while (lst && lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	ft_fileadd_back(t_file **lst, t_file *new)
{
	t_file	*temp;

	if (!lst || !new)
		return ;
	temp = ft_filelast(*lst);
	if (temp != NULL)
		temp->next = new;
	else
		*lst = new;
}

void	ft_filedelone(t_file *file)
{
	if (file->name)
		free(file->name);
	free(file);
}

void	ft_fileclear(t_file **file)
{
	t_file	*temp;

	temp = NULL;
	while (*file)
	{
		temp = (*file)->next;
		ft_filedelone(*file);
		*file = temp;
	}
}
