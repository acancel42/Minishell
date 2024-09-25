#include "minishell.h"

int	handle_output(char *src, t_token **token, t_data *data)
{
	int		j;
	int		i;
	t_token	*temp;

	i = 0;
	(void)(data);
	j = 0;
	if (src && src[i + 1] == '>')
	{
		j++;
		i++;
	}
	if (j == 0)
	{
		temp = ft_toknew('>', T_REDIR_OUT);
		if (!temp)
			ft_exit(*token, NULL, data);
		ft_tokadd_back(token, temp);
	}
	else
	{
		temp = ft_toknew('+', T_APPEND_OUT);
		if (!temp)
			ft_exit(*token, NULL, data);
		ft_tokadd_back(token, temp);
	}
	data->rflag = 1;
	i++;
	return (i);
}

int	handle_input(char *src, t_token **token, t_data *data)
{
	int		j;
	int		i;
	t_token	*temp;

	(void)(data);
	i = 0;
	j = 0;
	if (src && src[i + 1] == '<')
	{
		j++;
		i++;
	}
	if (j == 0)
	{
		temp = ft_toknew('<', T_REDIR_IN);
		if (!temp)
			ft_exit(*token, NULL, data);
		ft_tokadd_back(token, temp);
	}
	else
	{
		temp = ft_toknew('-', T_HEREDOC);
		if (!temp)
			ft_exit(*token, NULL, data);
		ft_tokadd_back(token, temp);
	}
	data->rflag = 1;
	i++;
	return (i);
}

int	handle_pipe(t_token **token, t_data *data)
{
	t_token	*temp;

	(void)(data);
	temp = ft_toknew('|', T_PIPE);
	if (!temp)
		ft_exit(*token, NULL, data);
	ft_tokadd_back(token, temp);
	return (1);
}

int	handle_else(char *src, t_token **token, t_data *data)
{
	char	c;
	int		i;
	t_token	*temp;

	i = 0;
	(void)(data);
	if (data->rflag == 0)
	{
		temp = ft_toknew(src[i++], T_WORD);
		if (!temp)
			ft_exit(*token, NULL, data);
	}
	else
	{
		data->rflag = 0;
		temp = ft_toknew(src[i++], T_RWORD);
		if (!temp)
			ft_exit(*token, NULL, data);
	}
	ft_tokadd_back(token, temp);
	while (src[i] && !ft_iswspace(src[i]) && !ft_isoperator(src[i]) && \
		!ft_isquote(src[i]))
	{
		c = src[i];
		temp->value = ft_charjoin(temp->value, c);
		if (!temp->value)
			ft_exit(*token, NULL, data);
		i++;
	}
	if (!ft_iswspace(src[i]) && !ft_isoperator(src[i]))
		temp->is_separated = 1;
	return (i);
}
