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

/*void	fill_cmd(t_commands **cmds, t_token *token)
{
	t_file	*temp1;
	char 	*temp2;
	int	i;

	i = 0;
	while (token)
	{
		if (!(*cmds)->args)
			(*cmds)->args = ft_calloc(count_type_until_pipe(token, T_WORD) + count_type_until_pipe(token, T_WORD) + count_type_until_pipe(token, T_WORD) + 1, sizeof(char *));
		if (ft_isword(token))
		{
			temp2 = ft_strdup(token->value);
			while (token->next && token->is_separated == 1)
			{
				token = token->next;
				temp2 = ft_strjoin(temp2, token->value, 0);
			}
			if (i == 0)
				(*cmds)->name = ft_strdup(temp2);
			(*cmds)->args[i++] = ft_strdup(temp2);
			free(temp2);
		}
		else if (token->type == T_REDIR_OUT)
		{
			temp1 = ft_filenew(token->value, ">");
			ft_fileadd_back(&(*cmds)->redirections, temp1);
		}
		else if (token->type == T_REDIR_IN)
		{
			temp1 = ft_filenew(token->value, "<");
			ft_fileadd_back(&(*cmds)->redirections, temp1);
		}
		else if (token->type == T_APPEND_OUT)
		{
			temp1 = ft_filenew(token->value, "+");
			ft_fileadd_back(&(*cmds)->redirections, temp1);
		}
		else if (token->type == T_HEREDOC)
		{
			temp1 = ft_filenew(token->value, "-");
			ft_fileadd_back(&(*cmds)->redirections, temp1);
		}
		else if (token->type == T_PIPE)
		{
			i = 0;
			printf("debug\n");
			cmds = &(*cmds)->next;
		}
		token = token->next;
	}
}*/

void handle_word(t_commands **cmds, t_token **token, int *i)
{
	char *temp2;

	temp2 = ft_strdup((*token)->value);
	while ((*token)->next && (*token)->is_separated == 1)
	{
		(*token) = (*token)->next;
		temp2 = ft_strjoin(temp2, (*token)->value, 0);
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
	printf("%s\n", get_color("exit", RED));
	exit(EXIT_SUCCESS);
}

