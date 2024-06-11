#include "minishell.h"

// Initialiser un token à partir d'une chaîne
int	token_init(char *src, t_token **token)
{
	int		i;
	int		j;
	char	c;
	t_token	*temp;

	i = 0;
	j = 0;
	while (ft_iswspace(src[i]))
		i++;
	if (!src[i])
		return (i);
	if (src[i] == '"')
	{
		i++;
		temp = ft_toknew(src[i], T_D_QUOTED_WORD);
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
			printf("%s\n", "Interractive mode");
			exit(EXIT_FAILURE);
		}
		else
		{
			i++;
			if (!ft_iswspace(src[i]) && !ft_isoperator(src[i]))
				temp->is_separated = 1;
		}
		return (i);
	}
	else if (src[i] == '\'')
	{
		i++;
		temp = ft_toknew(src[i], T_S_QUOTED_WORD);
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
			printf("%s\n", "Interractive mode");
			exit(EXIT_FAILURE);
		}
		else
		{
			i++;
			if (!ft_iswspace(src[i]) && !ft_isoperator(src[i]))
				temp->is_separated = 1;
		}
		return (i);
	}
	else if (src[i] == '>')
	{
		if (src && src[i + 1] == '>')
		{
			j++;
			i++;
		}
		i++;
		while (src[i] && ft_iswspace(src[i]) && !ft_isoperator(src[i]))
			i++;
		temp = ft_toknew(src[i++], T_REDIR_OUT);
		if (j > 0)
			temp->type = T_APPEND_OUT;
		while (src[i] && !ft_iswspace(src[i]) && !ft_isoperator(src[i]))
		{
			c = src[i];
			temp->value = ft_charjoin(temp->value, c);
			i++;
		}
		ft_tokadd_back(token, temp);
		printf("%s\n", temp->value);
		return (i);
	}
	else if (src[i] == '<')
	{
		if (src && src[i + 1] == '<')
		{
			j++;
			i++;
		}
		i++;
		while (src[i] && ft_iswspace(src[i]) && !ft_isoperator(src[i]))
			i++;
		temp = ft_toknew(src[i++], T_REDIR_IN);
		if (j > 0)
			temp->type = T_HEREDOC;
		while (src[i] && !ft_iswspace(src[i]) && !ft_isoperator(src[i]))
		{
			c = src[i];
			temp->value = ft_charjoin(temp->value, c);
			i++;
		}
		ft_tokadd_back(token, temp);
		printf("%s\n", temp->value);
		return (i);
	}
	else if (src[i] == '|')
	{
		temp = ft_toknew('|', T_PIPE);
		ft_tokadd_back(token, temp);
		i++;
		return (i);
	}
	else
	{
		temp = ft_toknew(src[i++], T_WORD);
		ft_tokadd_back(token, temp);
		while (src[i] && !ft_iswspace(src[i]) && !ft_isoperator(src[i]) \
			&& !ft_isquote(src[i]))
		{
			c = src[i];
			temp->value = ft_charjoin(temp->value, c);
			i++;
		}
		if (!ft_iswspace(src[i]) && !ft_isoperator(src[i]))
			temp->is_separated = 1;
		return (i);
	}
}

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

void	fill_cmd(t_commands **cmds, t_token *token)
{
	t_file	*temp1;
	int	i;

	i = 0;
	while (token)
	{
		if (!(*cmds)->args)
			(*cmds)->args = ft_calloc(count_type_until_pipe(token, T_WORD) + count_type_until_pipe(token, T_WORD) + count_type_until_pipe(token, T_WORD) + 1, sizeof(char *));
		if (ft_isword(token))
		{
			if (i == 0)
				(*cmds)->name = ft_strdup(token->value);
			(*cmds)->args[i++] = ft_strdup(token->value);
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
}

void exit_minishell(t_token **token, t_commands **cmds, char **user)
{
	ft_cmdsclear(cmds);
	ft_tokenclear(token);
	if (user)
		free(*user);
	printf("%s\n", "exit");
	exit(EXIT_SUCCESS);
}

