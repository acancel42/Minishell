#include "minishell.h"

int	expand_variables(char **dest, char *src, t_data *data)
{
	int		start;
	int		end;
	char	*name;
	char	*value;
	char	*temp;
	int		i;
	bool	is_itoa;

	(*dest) = ft_strdup(src);
	if (!(*dest))
		return (-1);
	i = 0;
	end = 0;
	is_itoa = false;
	if (ft_strncmp((*dest), "$", 1) == 0 && ft_strlen((*dest)) == 1)
		return (i);
	while ((*dest) && (*dest)[i])
	{
		if ((*dest)[i] == '$')
		{
			start = i;
			end = i + 1;
			i++;
			if ((*dest)[i] == '?')
			{
				name = NULL;
				value = ft_itoa(data->last_error_status);
				if (!value)
					return (-1);
				end++;
				is_itoa = true;
			}
			else
			{
				if (ft_isdigit((*dest)[i]))
				{
					name = ft_strndup((*dest) + start + 1, 1);
					if (!name)
						return (-1);
					i++;
					end++;
				}
				else
				{
					while (ft_isalnum((*dest)[i++]) && (*dest)[i - 1] != '$')
						end++;
					name = ft_strndup((*dest) + (start + 1), end - start - 1);
					if (!name)
						return (-1);
				}
				value = find_env_var(name, data->my_env);
			}
			if (value)
			{
				temp = malloc(ft_strlen((*dest)) - ft_strlen(name) + \
							ft_strlen(value) + 1);
				if (!temp)
					return (-1);
				ft_strncpy(temp, (*dest), start);
				ft_strcpy(temp + start, value);
				i = start + ft_strlen(value);
				ft_strcpy(temp + start + ft_strlen(value), (*dest) + end);
				free((*dest));
				(*dest) = ft_strdup(temp);
				if (!(*dest))
					return (-1);
			}
			else
			{
				i = start;
				temp = malloc(ft_strlen((*dest)) - ft_strlen(name) + \
						ft_strlen(value) + 1);
				ft_strncpy(temp, (*dest), start);
				ft_strcpy(temp + start, (*dest) + end);
				free((*dest));
				(*dest) = ft_strdup(temp);
				if (!(*dest))
					return (-1);
				if (!(*dest)[0])
				{
					free(temp);
					free(name);
					break ;
				}
			}
			free(temp);
			free(name);
			if (is_itoa == true)
			{
				is_itoa = false;
				free(value);
			}
		}
		else
			i++;
	}
	return (i);
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

static char	*handle_rword_utils(t_token **token, t_data *data, char *temp2, int j)
{
	char	*temp;
	char	*temp3;

	temp = ft_strdup(temp2);
	free (temp2);
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
				ft_exit(*token, data->cmds, data);
		}
		temp = ft_strjoin(temp, temp3, 1);
		if (!temp)
			ft_exit(*token, data->cmds, data);
		free(temp3);
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
	while (token)
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
				return (2);
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
