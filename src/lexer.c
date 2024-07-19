#include "minishell.h"

int	expand_variables(char **dest, char *str, t_data *data)
{
	int		start;
	int		end;
	char	*name;
	char	*value;
	char	*temp;
	int		i;

	i = 0;
	end = 0;
	if (ft_strncmp(str, "$", 1) == 0 && ft_strlen(str) == 1)
	{
		(*dest) = ft_strdup(str);
		return (i);
	}
	while (str && str[i])
	{
		if (str[i] == '$')
		{
			start = i;
			end = i + 1;
			i++;
			while (ft_isalnum(str[i++]) && str[i - 1] != '$')
				end++;
			name = ft_strndup(str + (start + 1), end - start - 1);
			value = find_env_var(name, data->my_env);
			if (value)
			{
				i++;
				temp = malloc(ft_strlen(str) - ft_strlen(name) + ft_strlen(value) + 1);
				ft_strncpy(temp, str, start);
				ft_strcpy(temp + start, value);
				ft_strcpy(temp + start + ft_strlen(value), str + end);
				str = ft_strdup(temp);
			}
			else
			{
				i = start;
				temp = malloc(ft_strlen(str) - ft_strlen(name) + ft_strlen(value) + 1);
				ft_strncpy(temp, str, start);
				ft_strcpy(temp + start, str + end);
				str = ft_strdup(temp);
			}
			free(temp);
			free(name);
		}
		else
			i++;
	}
	(*dest) = ft_strdup(str);
	free(str);
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
			temp3 = ft_strdup((*token)->value);
		temp2 = ft_strjoin(temp2, temp3, 0);
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
		temp2 = ft_strdup((*token)->value);
	handle_word_utils(token, data, temp2, j);
	if (*i == 0)
		(*cmds)->name = ft_strdup(temp2);
	(*cmds)->args[(*i)++] = ft_strdup(temp2);
	free(temp2);
}

static void	handle_rword_utils(t_token **token, t_data *data, char *temp2, int j)
{
	char	*temp3;

	while ((*token)->next && (*token)->is_separated == 1)
	{
		(*token) = (*token)->next;
		if ((*token)->type != T_RS_QUOTED_WORD)
			j = expand_variables(&temp3, (*token)->value, data);
		else
			temp3 = ft_strdup((*token)->value);
		temp2 = ft_strjoin(temp2, temp3, 0);
		if (j)
		{
			free(temp3);
			break ;
		}
		free(temp3);
	}
}

void	handle_rword(t_commands **cmds, t_token **token, t_data *data, int *k)
{
	char	*redir_type;
	char	*temp2;
	int		j;

	temp2 = NULL;
	redir_type = ft_strdup((*token)->value);
	(*token) = (*token)->next;
	j = 0;
	if ((*token)->type != T_RS_QUOTED_WORD)
		j = expand_variables(&temp2, (*token)->value, data);
	else
		temp2 = ft_strdup((*token)->value);
	handle_rword_utils(token, data, temp2, j);
	(*cmds)->redirections[(*k)++] = ft_strjoin(redir_type, temp2, 0);
	free(redir_type);
	free(temp2);
}

void	fill_cmd(t_commands **cmds, t_token *token, t_data *data)
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
			(*cmds)->redirections = ft_calloc(count_type_until_pipe(token, T_RWORD, 0) \
			+ count_type_until_pipe(token, T_RD_QUOTED_WORD, 0) \
			+ count_type_until_pipe(token, T_RS_QUOTED_WORD, 0) \
			+ 1, sizeof(char *));
		if (!(*cmds)->redirections)
			exit_minishell(&token, cmds, data);
		if (ft_isword(token))
			handle_word(cmds, &token, data, &i);
		else if (token->type == T_REDIR_OUT || token->type == T_REDIR_IN \
				|| token->type == T_APPEND_OUT || token->type == T_HEREDOC)
			handle_rword(cmds, &token, data, &k);
		else if (token->type == T_PIPE)
		{
			k = 0;
			i = 0;
			cmds = &(*cmds)->next;
		}
		token = token->next;
	}
}
