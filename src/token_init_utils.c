# include "minishell.h"

int handle_output(char *src, t_token **token, int i)
{
	int j = 0;
	char c;
	t_token *temp;
	if (src && src[i + 1] == '>') {
		j++;
		i++;
	}
	i++;
	while (src[i] && ft_iswspace(src[i]) && !ft_isoperator(src[i]))
		i++;
	temp = ft_toknew(src[i++], T_REDIR_OUT);
	if (j > 0)
		temp->type = T_APPEND_OUT;
	while (src[i] && !ft_iswspace(src[i]) && !ft_isoperator(src[i])) {
		c = src[i];
		temp->value = ft_charjoin(temp->value, c);
		i++;
	}
	ft_tokadd_back(token, temp);
	printf("%s\n", temp->value);
	return (i);
}

int handle_input(char *src, t_token **token, int i)
{
	int j = 0;
	char c;
	t_token *temp;
	if (src && src[i + 1] == '<') {
		j++;
		i++;
	}
	i++;
	while (src[i] && ft_iswspace(src[i]) && !ft_isoperator(src[i]))
		i++;
	temp = ft_toknew(src[i++], T_REDIR_IN);
	if (j > 0)
		temp->type = T_HEREDOC;
	while (src[i] && !ft_iswspace(src[i]) && !ft_isoperator(src[i])) {
		c = src[i];
		temp->value = ft_charjoin(temp->value, c);
		i++;
	}
	ft_tokadd_back(token, temp);
	printf("%s\n", temp->value);
	return (i);
}

int handle_pipe(t_token **token, int i)
{
	t_token *temp;
	temp = ft_toknew('|', T_PIPE);
	ft_tokadd_back(token, temp);
	i++;
	return (i);
}

int handle_else(char *src, t_token **token, int i)
{
	char c;
	t_token *temp;
	temp = ft_toknew(src[i++], T_WORD);
	ft_tokadd_back(token, temp);
	while (src[i] && !ft_iswspace(src[i]) && !ft_isoperator(src[i]) && !ft_isquote(src[i]))
	{
		c = src[i];
		printf("%c\n", c);
		temp->value = ft_charjoin(temp->value, c);
		i++;
	}
	if (!ft_iswspace(src[i]) && !ft_isoperator(src[i]))
		temp->is_separated = 1;
	printf("%s\n", temp->value);
	return (i);
}

