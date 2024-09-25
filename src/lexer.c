#include "minishell.h"

int	ft_assign_value_util(char **name, char **dst, t_data *dt)
{
	if (ft_isdigit((*dst)[dt->exp.i]))
	{
		*name = ft_strndup((*dst) + dt->exp.s + 1, 1);
		if (!(*name))
			return (-1);
		dt->exp.i++;
		dt->exp.e++;
	}
	else if ((*dst)[dt->exp.i] == '$')
	{
		*name = ft_strndup((*dst) + dt->exp.s + 1, 1);
		if (!(*name))
			return (-1);
		dt->exp.i++;
		dt->exp.e++;
	}
	else
	{
		while (ft_isalnum((*dst)[dt->exp.i++]) && (*dst)[dt->exp.i - 1] != '$')
			dt->exp.e++;
		*name = ft_strndup((*dst) + (dt->exp.s + 1), dt->exp.e - dt->exp.s - 1);
		if (!(*name))
			return (-1);
	}
	return (0);
}

int	ft_assign_value(char **name, char **value, char **dest, t_data *data)
{
	if ((*dest)[data->exp.i] == '?')
	{
		*name = NULL;
		*value = ft_itoa(data->last_error_status);
		if (!(*value))
			return (-1);
		data->exp.e++;
		data->exp.is_itoa = true;
	}
	else
	{
		if (ft_assign_value_util(name, dest, data) == -1)
			return (-1);
		*value = find_env_var(*name, data->my_env);
	}
	return (0);
}

int	ft_replace_value(char **dest, char **value, char **name, t_data *data)
{
	char	*tmp;

	if (*value)
	{
		tmp = malloc(ft_strlen((*dest)) - ft_strlen(*name) + \
					ft_strlen(*value) + 1);
		if (!tmp)
			return (-1);
		ft_strncpy(tmp, (*dest), data->exp.s);
		ft_strcpy(tmp + data->exp.s, *value);
		data->exp.i = data->exp.s + ft_strlen(*value);
		ft_strcpy(tmp + data->exp.s + ft_strlen(*value), (*dest) + data->exp.e);
		free((*dest));
		(*dest) = ft_strdup(tmp);
		if (!(*dest))
			return (-1);
	}
	else
	{
		data->exp.i = data->exp.s;
		tmp = malloc(ft_strlen((*dest)) - ft_strlen(*name) + \
				ft_strlen(*value) + 1);
		ft_strncpy(tmp, (*dest), data->exp.s);
		ft_strcpy(tmp + data->exp.s, (*dest) + data->exp.e);
		free((*dest));
		(*dest) = ft_strdup(tmp);
		if (!(*dest))
			return (-1);
		if (!(*dest)[0])
		{
			free(tmp);
			free(*name);
			return (2);
		}
	}
	free(tmp);
	free(*name);
	return (0);
}

int	ft_expand_loop(char **dest, char **name, char **value, t_data *data)
{
	int	ret;

	if ((*dest)[data->exp.i] == '$')
	{
		data->exp.s = data->exp.i;
		data->exp.e = data->exp.i + 1;
		data->exp.i++;
		if (ft_assign_value(name, value, dest, data) == -1)
			return (-1);
		ret = ft_replace_value(dest, value, name, data);
		if (ret == 2)
			return (2);
		if (ret == -1)
			return (-1);
		if (data->exp.is_itoa == true)
		{
			data->exp.is_itoa = false;
			free(*value);
		}
	}
	else
		data->exp.i++;
	return (0);
}

int	expand_variables(char **dest, char *src, t_data *data)
{
	char		*name;
	char		*value;
	int			ret;

	(*dest) = ft_strdup(src);
	if (!(*dest))
		return (-1);
	value = NULL;
	name = NULL;
	data->exp.i = 0;
	data->exp.e = 0;
	data->exp.is_itoa = false;
	if (ft_strncmp((*dest), "$", 1) == 0 && ft_strlen((*dest)) == 1)
		return (data->exp.i);
	while ((*dest) && (*dest)[data->exp.i])
	{
		ret = ft_expand_loop(dest, &name, &value, data);
		if (ret == -1)
			return (-1);
		else if (ret == 2)
			break ;
	}
	return (data->exp.i);
}

static char	*handle_w_utils(t_token **token, t_data *data, char *temp2, int j)
{
	char	*temp;
	char	*temp3;

	temp = ft_strdup(temp2);
	free(temp2);
	while ((*token)->next && (*token)->is_separated == 1)
	{
		if (ft_strncmp((*token)->value, "$", 2) == 0 && \
			ft_strncmp((*token)->next->value, "", 1) == 0)
			(*token) = (*token)->next;
		(*token) = (*token)->next;
		if ((*token)->type != T_S_QUOTED_WORD)
			j = expand_variables(&temp3, (*token)->value, data);
		else
		{
			temp3 = ft_strdup((*token)->value);
			if (!temp3)
				ft_exit(*token, data->cmds, data);
		}
		temp = ft_strjoin(temp, temp3, 1);
		if (!temp)
			ft_exit(*token, data->cmds, data);
		free(temp3);
	}
	return (temp);
}

void	handle_word(t_commands **cmds, t_token **token, t_data *data, int *i)
{
	char	*temp2;
	int		j;

	temp2 = NULL;
	j = 0;
	if (ft_strncmp((*token)->value, "", 1 == 0) && (*token)->is_separated == 0)
		temp2 = ft_strdup((*token)->value);
	else
	{
		if ((*token)->next && ft_strncmp((*token)->value, "$", 2) == 0 && \
			ft_strncmp((*token)->next->value, "", 1) == 0)
			(*token) = (*token)->next;
		if ((*token)->type != T_S_QUOTED_WORD)
		{
			j = expand_variables(&temp2, (*token)->value, data);
		}
		else
		{
			temp2 = ft_strdup((*token)->value);
			if (!temp2)
				ft_exit(*token, *cmds, data);
		}
		temp2 = handle_w_utils(token, data, temp2, j);
	}
	if (*i == 0)
	{
		(*cmds)->name = ft_strdup(temp2);
		if (!(*cmds)->name)
			ft_exit(*token, *cmds, data);
	}
	(*cmds)->args[(*i)++] = ft_strdup(temp2);
	if (!(*cmds)->args[(*i) - 1])
		ft_exit(*token, *cmds, data);
	free(temp2);
}

static char	*handle_rword_utils(t_token **token, t_data *data, \
								char *temp2, int j)
{
	char	*temp;
	char	*temp3;

	temp = ft_strdup(temp2);
	free (temp2);
	if (!temp)
		ft_exit(*token, data->cmds, data);
	while ((*token)->next && (*token)->is_separated == 1)
	{
		if (ft_strncmp((*token)->value, "$", 2) == 0 && \
			ft_strncmp((*token)->next->value, "", 1) == 0)
			(*token) = (*token)->next;
		(*token) = (*token)->next;
		if ((*token)->type != T_RS_QUOTED_WORD)
			j = expand_variables(&temp3, (*token)->value, data);
		else
		{
			temp3 = ft_strdup((*token)->value);
			if (!temp3)
			{
				free(temp);
				ft_exit(*token, data->cmds, data);
			}
		}
		temp = ft_strjoin(temp, temp3, 1);
		free(temp3);
		if (!temp)
			ft_exit(*token, data->cmds, data);
	}
	return (temp);
}

int	ft_is_variable(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == '$')
			return (1);
	return (0);
}

int	handle_rword(t_commands **cmds, t_token **token, t_data *data, int *k)
{
	char	*redir_type;
	char	*temp2;
	int		j;

	temp2 = NULL;
	if ((*token)->type == T_HEREDOC && \
		ft_is_variable((*token)->next->value) == 1)
	{
		printf("syntax error\n");
		return (2);
	}
	redir_type = ft_strdup((*token)->value);
	if (!redir_type)
		ft_exit(*token, *cmds, data);
	(*token) = (*token)->next;
	j = 0;
	if (ft_strncmp((*token)->value, "$", 2) == 0 && \
		ft_strncmp((*token)->next->value, "", 1) == 0)
		(*token) = (*token)->next;
	if ((*token)->type != T_RS_QUOTED_WORD)
		j = expand_variables(&temp2, (*token)->value, data);
	else
	{
		temp2 = ft_strdup((*token)->value);
		if (!temp2)
			ft_exit(*token, *cmds, data);
	}
	temp2 = handle_rword_utils(token, data, temp2, j);
	(*cmds)->redirections[(*k)++] = ft_strjoin(redir_type, temp2, 0);
	if (!(*cmds)->redirections[(*k - 1)])
		ft_exit(*token, *cmds, data);
	free(redir_type);
	free(temp2);
	return (0);
}

int	fill_cmd(t_commands **cmds, t_token *token, t_data *data)
{
	int	i;
	int	k;

	k = 0;
	i = 0;
	while (token && *cmds)
	{
		if (!(*cmds)->args)
			(*cmds)->args = ft_calloc(count_type_until_pipe(token, T_WORD, 0) \
			+ count_type_until_pipe(token, T_D_QUOTED_WORD, 0) \
			+ count_type_until_pipe(token, T_S_QUOTED_WORD, 0) \
			+ 1, sizeof(char *));
		if (!(*cmds)->args)
			ft_exit(token, *cmds, data);
		if (!(*cmds)->redirections)
			(*cmds)->redirections = \
				ft_calloc(count_type_until_pipe(token, T_RWORD, 0) \
				+ count_type_until_pipe(token, T_RD_QUOTED_WORD, 0) \
				+ count_type_until_pipe(token, T_RS_QUOTED_WORD, 0) \
				+ 1, sizeof(char *));
		if (!(*cmds)->redirections)
			ft_exit(token, *cmds, data);
		if (ft_isword(token))
			handle_word(cmds, &token, data, &i);
		else if (token->type == T_REDIR_OUT || token->type == T_REDIR_IN \
				|| token->type == T_APPEND_OUT || token->type == T_HEREDOC)
		{
			if (handle_rword(cmds, &token, data, &k) == 2)
			{
				data->last_error_status = 2;
				return (2);
			}
		}
		else if (token->type == T_PIPE)
		{
			k = 0;
			i = 0;
			cmds = &(*cmds)->next;
		}
		token = token->next;
	}
	return (0);
}
