#include "minishell.h"

int	ft_isword(t_token *token)
{
	if (token->type == T_D_QUOTED_WORD || token->type == T_S_QUOTED_WORD || token->type == T_WORD)
		return (1);
	return (0);
}


void	lexer_init(t_token **token, t_data *data)
{
	int	i;

	i = 0;
	while (data->line[i])
		i += token_init(data->line + i, token, data);
}

void	init_cmd(t_commands **cmds, t_token *token, t_data *data)
{
	t_commands	*temp;
	int			flag;

	flag = 0;
	while (token)
	{
		if (token->type == T_PIPE)
			token = token->next;
		temp = ft_cmdnew(data->user, flag++);
		ft_cmdadd_back(cmds, temp);
		data->index_max = temp->index;
		while (token && token->type != T_PIPE)
			token = token->next;
	}

}

int	count_type_until_pipe(t_token *token, t_token_types type, int flag)
{
	int	count;

	count = 0;
	while (token && token->type != T_PIPE)
	{
		if (token->type == type)
		{
			if (flag == 0)
				count++;
			else if (flag == 1)
				if (token->value[0] != '-')
					count++;
		}
		token = token->next;
	}
	return (count);
}

char *find_env_var(char *name, char **env)
{
	int i = 0;
	int len = ft_strlen(name);

	while (env[i])
	{
		if (strncmp(env[i], name, len) == 0 && env[i][len] == '=')
			return &env[i][len + 1];
		i++;
	}
	return NULL;
}

int expand_variables(char **dest, char *str, t_data *data)
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

void handle_word(t_commands **cmds, t_token **token, t_data *data, int *i)
{
	char *temp2;
	char *temp3;
	int j;

	temp2 = NULL;
	temp3 = NULL;
	j = 0;
	if ((*token)->type != T_S_QUOTED_WORD)
		j = expand_variables(&temp2, (*token)->value, data);
	else
		temp2 = ft_strdup((*token)->value);
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
			break;
		}
		free(temp3);
	}
	if (*i == 0)
		(*cmds)->name = ft_strdup(temp2);
	(*cmds)->args[(*i)++] = ft_strdup(temp2);
	free(temp2);
}

void handle_redirection(t_commands **cmds, t_token *token, t_data *data)
{
	t_file *temp1;
	char *type;

	type = NULL;
	if (token->type == T_REDIR_OUT)
		type = ft_strdup(">");
	else if (token->type == T_REDIR_IN)
		type = ft_strdup("<");
	else if (token->type == T_APPEND_OUT)
		type = ft_strdup("+");
	else if (token->type == T_HEREDOC)
		type = ft_strdup("-");
	if (!type)
		exit_minishell(&token, cmds, data);
	temp1 = ft_filenew(token->value, type);
	ft_fileadd_back(&(*cmds)->redirections, temp1);
	free(type);
}

void fill_cmd(t_commands **cmds, t_token *token, t_data *data)
{
	int i = 0;
	while (token)
	{
		if (!(*cmds)->args)
			(*cmds)->args = ft_calloc(count_type_until_pipe(token, T_WORD, 0) + count_type_until_pipe(token, T_D_QUOTED_WORD, 0) + count_type_until_pipe(token, T_S_QUOTED_WORD, 0) + 1, sizeof(char *));
		if (!(*cmds)->args)
			exit_minishell(&token, cmds, data);
		if (ft_isword(token))
		{
			handle_word(cmds, &token, data, &i);
		}
		else if (token->type == T_REDIR_OUT || token->type == T_REDIR_IN || token->type == T_APPEND_OUT || token->type == T_HEREDOC)
		{
			handle_redirection(cmds, token, data);
		}
		else if (token->type == T_PIPE)
		{
			i = 0;
			cmds = &(*cmds)->next;
		}
		token = token->next;
	}
}

void exit_minishell(t_token **token, t_commands **cmds, t_data *data)
{

	ft_cmdsclear(cmds);
	ft_tokenclear(token);
	if (data)
	{
		if (data->line)
			free(data->line);
		if (data->my_env)
			ft_free_tab(data->my_env);
		if (data->user)
			free(data->user);
		if (data->home)
			free(data->home);
		free(data);
	}
	printf(RED"%s\n"RESET, "exit");
	exit(EXIT_SUCCESS);
}
