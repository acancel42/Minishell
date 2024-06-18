#include "minishell.h"

int	ft_isword(t_token *token)
{
	if (token->type == T_D_QUOTED_WORD || token->type == T_S_QUOTED_WORD || token->type == T_WORD)
		return (1);
	return (0);
}


void	lexer_init(t_token **token, char *src)
{
	int	i;

	i = 0;
	while (src[i])
		i += token_init(src + i, token);
}

void	init_cmd(t_commands **cmds, t_token *token, char *user)
{
	t_commands	*temp;

	while (token)
	{
		if (token->type == T_PIPE)
			token = token->next;
		temp = ft_cmdnew(user);
		ft_cmdadd_back(cmds, temp);
		while (token && token->type != T_PIPE)
			token = token->next;
	}
}

int	count_type_until_pipe(t_token *token, t_token_types type)
{
	int	count;

	count = 0;
	while (token && token->type != T_PIPE)
	{
		if (token->type == type)
			count++;
		token = token->next;
	}
	return (count);
}

char *expand_variables(char *str)
{
	char *start = str;
	char *end;
	char *name;
	char *value;

	while ((start = ft_strchr(start, '$')) != NULL)
	{
		end = start;
		while (isalnum(*++end) || *end == '_')
			;
		name = ft_strndup(start + 1, end - start - 1);
		value = getenv(name);
		free(name);
		if (value)
		{
			char *temp = malloc(ft_strlen(str) - ft_strlen(name) + ft_strlen(value) + 1);
			ft_strncpy(temp, str, start - str);
			ft_strcpy(temp + (start - str), value);
			ft_strcpy(temp + (start - str) + ft_strlen(value), end);
			free(str);
			str = temp;
			start = str + (start - str) + ft_strlen(value);
		}
		else
		{
			start = end;
		}
	}
	return str;
}

void handle_word(t_commands **cmds, t_token **token, int *i)
{
	char *temp2;
	char *temp3;

	temp2 = ft_strdup((*token)->value);
	if ((*token)->type != T_S_QUOTED_WORD)
		temp2 = expand_variables(temp2);
	while ((*token)->next && (*token)->is_separated == 1)
	{
		(*token) = (*token)->next;
		if ((*token)->type != T_S_QUOTED_WORD)
			temp3 = expand_variables(ft_strdup((*token)->value));
		else
			temp3 = ft_strdup((*token)->value);
		temp2 = ft_strjoin(temp2, temp3, 0);
		free(temp3);
	}
	if (*i == 0)
		(*cmds)->name = ft_strdup(temp2);
	(*cmds)->args[(*i)++] = ft_strdup(temp2);
	free(temp2);
}

void handle_redirection(t_commands **cmds, t_token *token)
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
	temp1 = ft_filenew(token->value, type);
	ft_fileadd_back(&(*cmds)->redirections, temp1);
}

void fill_cmd(t_commands **cmds, t_token *token)
{
	int i = 0;
	while (token)
	{
		if (!(*cmds)->args)
			(*cmds)->args = ft_calloc(count_type_until_pipe(token, T_WORD) + count_type_until_pipe(token, T_WORD) + count_type_until_pipe(token, T_WORD) + 1, sizeof(char *));
		if (ft_isword(token))
		{
			handle_word(cmds, &token, &i);
		}
		else if (token->type == T_REDIR_OUT || token->type == T_REDIR_IN || token->type == T_APPEND_OUT || token->type == T_HEREDOC)
		{
			handle_redirection(cmds, token);
		}
		else if (token->type == T_PIPE)
		{
			i = 0;
			printf("debug\n");
			cmds = &(*cmds)->next;
		}
		token = token->next;
	}
}

void exit_minishell(t_token **token, t_commands **cmds, char **user)
{
	ft_cmdsclear(cmds);
	ft_tokenclear(token);
	if (user)
		free(*user);
	printf(RED"%s\n"RESET, "exit");
	exit(EXIT_SUCCESS);
}

