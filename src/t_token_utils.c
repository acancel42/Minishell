#include "minishell.h"

t_token	*ft_toknew(char content, t_token_types type)
{
	t_token	*new;

	new = ft_calloc(1, sizeof(t_token));
	if (!new)
		return (NULL);
	new->next = NULL;
	new->value = ft_chardup(content);
	new->type = type;
	new->is_separated = 0;
	return (new);
}

static t_token	*ft_toklast(t_token *lst)
{
	while (lst && lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	ft_tokadd_back(t_token **lst, t_token *new)
{
	t_token	*temp;

	if (!lst || !new)
		return ;
	temp = ft_toklast(*lst);
	if (temp != NULL)
		temp->next = new;
	else
		*lst = new;
}

void	ft_tokendelone(t_token *token)
{
	if (token->value)
		free(token->value);
	free(token);
}

void	ft_tokenclear(t_token **token)
{
	t_token	*temp;

	temp = NULL;
	while (*token)
	{
		temp = (*token)->next;
		ft_tokendelone(*token);
		*token = temp;
	}
}
