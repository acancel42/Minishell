#include "minishell.h"

int	handle_double_quote(char *src, t_token **token, t_data *data)
{
	char	c;
	int		i;
	t_token	*temp;

	i = 0;
	(void)(data);
	if (src[i] == '"' && src[i + 1] == '"')
	{
		if (data->rflag == 0)
			temp = ft_toknew(0, T_D_QUOTED_WORD);
		else
		{
			data->rflag = 0;
			temp = ft_toknew(0, T_RD_QUOTED_WORD);
		}
		ft_tokadd_back(token, temp);
		if (!ft_iswspace(src[i + 2]) && !ft_isoperator(src[i + 2]))
			temp->is_separated = 1;
		return (i + 2);
	}
	i++;
	if (data->rflag == 0)
		temp = ft_toknew(src[i], T_D_QUOTED_WORD);
	else
	{
		data->rflag = 0;
		temp = ft_toknew(src[i], T_RD_QUOTED_WORD);
	}
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

int	handle_single_quote(char *src, t_token **token, t_data *data)
{
	char	c;
	int		i;
	t_token	*temp;

	i = 0;
	(void)(data);
	if (src[i] == '\'' && src[i + 1] == '\'')
	{
		if (data->rflag == 0)
			temp = ft_toknew(0, T_S_QUOTED_WORD);
		else
		{
			data->rflag = 0;
			temp = ft_toknew(0, T_RS_QUOTED_WORD);
		}
		ft_tokadd_back(token, temp);
		if (!ft_iswspace(src[i + 2]) && !ft_isoperator(src[i + 2]))
			temp->is_separated = 1;
		return (i + 2);
	}
	i++;
	if (data->rflag == 0)
		temp = ft_toknew(src[i], T_S_QUOTED_WORD);
	else
	{
		data->rflag = 0;
		temp = ft_toknew(src[i], T_RS_QUOTED_WORD);
	}
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

int	token_init(char *src, int i, t_token **token, t_data *data)
{
	while (ft_iswspace(src[i]))
		i++;
	if (!src[i])
		return (i);
	if (src[i] == '"')
		i += handle_double_quote(src + i, token, data);
	else if (src[i] == '\'')
		i += handle_single_quote(src + i, token, data);
	else if (src[i] == '>')
		i += handle_output(src + i, token, data);
	else if (src[i] == '<')
		i += handle_input(src + i, token, data);
	else if (src[i] == '|')
		i += handle_pipe(token, data);
	else
		i += handle_else(src + i, token, data);
	return (i);
}
