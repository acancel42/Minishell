#include "minishell.h"

int	expand_variables(char **dest, char *src, t_data *data)
{
	int		start;
	int		end;
	char	*name;
	char	*value;
	char	*temp;
	int		i;

	(*dest) = ft_strdup(src);
	if (!(*dest))
		return (-1);
	i = 0;
	end = 0;
	if (ft_strncmp((*dest), "$", 1) == 0 && ft_strlen((*dest)) == 1)
		return (i);
	while ((*dest) && (*dest)[i])
	{
		if ((*dest)[i] == '$')
		{
			start = i;
			end = i + 1;
			i++;
			while (ft_isalnum((*dest)[i++]) && (*dest)[i - 1] != '$')
				end++;
			name = ft_strndup((*dest) + (start + 1), end - start - 1);
			if (!name)
				return (-1);
			value = find_env_var(name, data->my_env);
			if (value)
			{
				i++;
				temp = malloc(ft_strlen((*dest)) - ft_strlen(name) + \
							ft_strlen(value) + 1);
				ft_strncpy(temp, (*dest), start);
				ft_strcpy(temp + start, value);
				ft_strcpy(temp + start + ft_strlen(value), (*dest) + end);
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
				(*dest) = ft_strdup(temp);
				if (!(*dest))
					return (-1);
			}
			free(temp);
			free(name);
		}
		else
			i++;
	}
	return (i);
}

static void	handle_word_utils(t_token **token, t_data *data, char *temp2, int j)
{
	char	*temp3;

	while ((*token)->next && (*token)->is_separated == 1)
	{
		(*token) = (*token)->next;
		if ((*token)->type != T_S_QUOTED_WORD)
			j = expand_variables(&temp3, (*token)->value, data);
		else
		{
			temp3 = ft_strdup((*token)->value);
			if (!temp3)
				exit_minishell(token, &data->cmds, data);
		}
		temp2 = ft_strjoin(temp2, temp3, 0);
		if (!temp2)
			exit_minishell(token, &data->cmds, data);
		if (j)
		{
			free(temp3);
			break ;
		}
		free(temp3);
	}
}

void	handle_word(t_commands **cmds, t_token **token, t_data *data, int *i)
{
	char	*temp2;
	int		j;

	temp2 = NULL;
	j = 0;
	if ((*token)->type != T_S_QUOTED_WORD)
		j = expand_variables(&temp2, (*token)->value, data);
	else
	{
		temp2 = ft_strdup((*token)->value);
		if (!temp2)
			exit_minishell(token, cmds, data);
	}
	handle_word_utils(token, data, temp2, j);
	if (*i == 0)
	{
		(*cmds)->name = ft_strdup(temp2);
		if (!(*cmds)->name)
			exit_minishell(token, cmds, data);
	}
	(*cmds)->args[(*i)++] = ft_strdup(temp2);
	if (!(*cmds)->args[(*i) - 1])
		exit_minishell(token, cmds, data);
	free(temp2);
}

static void	handle_rword_utils(t_token **token, t_data *data, \
								char *temp2, int j)
{
	char	*temp3;

	while ((*token)->next && (*token)->is_separated == 1)
	{
		(*token) = (*token)->next;
		if ((*token)->type != T_RS_QUOTED_WORD)
			j = expand_variables(&temp3, (*token)->value, data);
		else
		{
			temp3 = ft_strdup((*token)->value);
			if (!temp3)
				exit_minishell(token, &data->cmds, data);
		}
		temp2 = ft_strjoin(temp2, temp3, 0);
		if (!temp2)
			exit_minishell(token, &data->cmds, data);
		if (j)
		{
			free(temp3);
			break ;
		}
		free(temp3);
	}
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
		exit_minishell(token, cmds, data);
	(*token) = (*token)->next;
	j = 0;
	if ((*token)->type != T_RS_QUOTED_WORD)
		j = expand_variables(&temp2, (*token)->value, data);
	else
	{
		temp2 = ft_strdup((*token)->value);
		if (!temp2)
			exit_minishell(token, cmds, data);
	}
	handle_rword_utils(token, data, temp2, j);
	(*cmds)->redirections[(*k)++] = ft_strjoin(redir_type, temp2, 0);
	if (!(*cmds)->redirections[(*k - 1)])
		exit_minishell(token, cmds, data);
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
			exit_minishell(&token, cmds, data);
		if (!(*cmds)->redirections)
			(*cmds)->redirections = \
				ft_calloc(count_type_until_pipe(token, T_RWORD, 0) \
				+ count_type_until_pipe(token, T_RD_QUOTED_WORD, 0) \
				+ count_type_until_pipe(token, T_RS_QUOTED_WORD, 0) \
				+ 1, sizeof(char *));
		if (!(*cmds)->redirections)
			exit_minishell(&token, cmds, data);
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
