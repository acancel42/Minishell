# include "minishell.h"

int handle_double_quote(char *src, t_token **token, int i)
{
	char c;
	t_token *temp;
	i++;
	temp = ft_toknew(src[i], T_D_QUOTED_WORD);
	ft_tokadd_back(token, temp);
	i++;
	while (src[i] && src[i] != '"')
	{
		c = src[i];
		temp->value = ft_charjoin(temp->value, c);
		i++;
	}
	if (src[i] != '"')
	{
		printf("%s\n", "Interactive mode");
		exit(EXIT_FAILURE);
	}
	else
	{
		i++;
		if (!ft_iswspace(src[i]) && !ft_isoperator(src[i]))
			temp->is_separated = 1;
	}
	return (i);
}

int handle_single_quote(char *src, t_token **token, int i)
{
	char c;
	t_token *temp;
	i++;
	temp = ft_toknew(src[i], T_S_QUOTED_WORD);
	ft_tokadd_back(token, temp);
	i++;
	while (src[i] && src[i] != '\'')
	{
		c = src[i];
		temp->value = ft_charjoin(temp->value, c);
		i++;
	}
	if (src[i] != '\'')
	{
		printf("%s\n", "Interactive mode");
		exit(EXIT_FAILURE);
	}
	else
	{
		i++;
		if (!ft_iswspace(src[i]) && !ft_isoperator(src[i]))
			temp->is_separated = 1;
	}
	return (i);
}

int	token_init(char *src, t_token **token)
{
	int		i;

	i = 0;
	while (ft_iswspace(src[i]))
		i++;
	if (!src[i])
		return (i);
	if (src[i] == '"')
		i = handle_double_quote(src, token, i);
	else if (src[i] == '\'')
		i = handle_single_quote(src, token, i);
	else if (src[i] == '>')
		i = handle_output(src, token, i);
	else if (src[i] == '<')
		i = handle_input(src, token, i);
	else if (src[i] == '|')
		i = handle_pipe(token, i);
	else
		i = handle_else(src, token, i);
	return (i);
}
