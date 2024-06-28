# include "minishell.h"

int handle_double_quote(char *src, t_token **token, int i, t_data *data)
{
	(void)(data);
	char c;
	t_token *temp;
	if (src[i] == '"' && src[i + 1] == '"')
	{
		temp = ft_toknew(0, T_D_QUOTED_WORD);
		ft_tokadd_back(token, temp);
		if (!ft_iswspace(src[i + 2]) && !ft_isoperator(src[i + 2]))
			temp->is_separated = 1;
		return (i + 2);
	}
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
		printf("%d\n", i);
		printf("%c\n", src[i]);
		printf("%s\n", "Interactive mode");
		exit(EXIT_FAILURE);
	}
	else if (!ft_iswspace(src[++i]) && !ft_isoperator(src[i]))
			temp->is_separated = 1;
	return (i);
}

int handle_single_quote(char *src, t_token **token, int i, t_data *data)
{
	(void)(data);
	char c;
	t_token *temp;
	if (src[i] == '\'' && src[i + 1] == '\'')
	{
		temp = ft_toknew(0, T_S_QUOTED_WORD);
		ft_tokadd_back(token, temp);
		if (!ft_iswspace(src[i + 2]) && !ft_isoperator(src[i + 2]))
			temp->is_separated = 1;
		return (i + 2);
	}
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
	else if (!ft_iswspace(src[++i]) && !ft_isoperator(src[i]))
			temp->is_separated = 1;
	return (i);
}

int	token_init(char *src, t_token **token, t_data *data)
{
	int		i;

	i = 0;
	while (ft_iswspace(src[i]))
		i++;
	if (!src[i])
		return (i);
	if (src[i] == '"')
		i = handle_double_quote(src, token, i, data);
	else if (src[i] == '\'')
		i = handle_single_quote(src, token, i, data);
	else if (src[i] == '>')
		i = handle_output(src, token, i, data);
	else if (src[i] == '<')
		i = handle_input(src, token, i, data);
	else if (src[i] == '|')
		i = handle_pipe(token, i, data);
	else
		i = handle_else(src, token, i, data);
	return (i);
}
