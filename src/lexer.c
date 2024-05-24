#include "../inc/minishell.h"

t_token	*ft_toknew(char *content, t_token_types type)
{
	t_token	*new;

	new = ft_calloc(1, sizeof(t_token));
	if (new == NULL)
		return (NULL);
	new->next = NULL;
	new->value = content;
	new->type = type;
	return (new);
}

t_token	*ft_toklast(t_token *lst)
{
	while (lst && lst->next != NULL )
		lst = lst->next;
	return (lst);
}

void	ft_tokadd_back(t_token **lst, t_token *new)
{
	t_token	*temp;

	temp = ft_toklast(*lst);
	if (temp != NULL)
		temp->next = new;
	else
		*lst = new;
}

int	token_init(char	*src, t_token *token)
{
	int		i;
	char	c;
	t_token	*temp;

	i = 0;
	printf("%s\n", src);
	if (src[i] == '=')
	{
		temp = ft_toknew("=", EQUAL);
		printf("%s\n", temp->value);
		ft_tokadd_back(&token, temp);
		printf("%s\n", token->value);
		printf("%s\n", "test");
		return (1);
	}
	else if (ft_isdigit(src[i]))
	{
		token->type = INT;
		c = src[i];
		token->value = ft_strdup(&c);
		while (ft_isalnum(src[++i]))
		{
			c = src[i];
			token->value = ft_strjoin(token->value, &c);
		}
		return (i);
	}
	else
		exit(EXIT_FAILURE);
}


void lexer_init(t_token *token, char *src)
{
	int		i;

	i = 0;
	while (src[i])
	{
		i += token_init(&src[i], token);
		printf("%s\n", token->value);
	}
}

void print_lst(t_token *token)
{
	while (token && token->next)
	{
\
		printf("%s\n", token->value);
		token = token->next;
	}
}

int	main(int argc, char **argv)
{
	t_token *token = NULL;

	(void)argc;
	lexer_init(token, argv[1]);
	//print_lst(&token);
}
