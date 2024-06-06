#include "minishell.h"
/*
char *ft_strjoin(char const *s1, char const *s2) {
	size_t len1 = ft_strlen(s1);
	size_t len2 = ft_strlen(s2);
	char *joined = malloc(len1 + len2 + 1);
	if (!joined) {
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	ft_strlcpy(joined, s1, len1);
	ft_strlcat(joined, s2, len2);
	return joined;
}*/

// Initialiser un token à partir d'une chaîne
int token_init(char *src, t_token **token) {
	int i = 0;
	char c;
	t_token *temp;

	while (ft_iswspace(src[i]))
			i++;
	if (src[i] == '>')
	{
		temp = ft_toknew('>', ORED);
		if (src && src[i + 1] == '>')
		{
			temp->value = ft_charjoin(temp->value, '>');
			temp->type = OAPP;
			i++;
		}
		i++;
		ft_tokadd_back(token, temp);
		while (src && ft_iswspace(src[i]))
			i++;
		temp = ft_toknew(0, OFILE);
		ft_tokadd_back(token, temp);
		while (src[i] && !ft_iswspace(src[i]) && !ft_isoperator(src[i]))
		{
			c = src[i];
			temp->value = ft_charjoin(temp->value, c);
			i++;
		}
		//free(temp);
		return (i);
	}
	if (src[i] == '<')
	{
		temp = ft_toknew('<', IRED);
		if (src && src[i + 1] == '<')
		{
			temp->value = ft_charjoin(temp->value, '<');
			temp->type = IAPP;
			i++;
		}
		ft_tokadd_back(token, temp);
		i++;
		while (src && ft_iswspace(src[i]))
			i++;
		temp = ft_toknew(0, IFILE);
		ft_tokadd_back(token, temp);
		while (src[i] && !ft_iswspace(src[i]) && !ft_isoperator(src[i]))
		{
			c = src[i];
			temp->value = ft_charjoin(temp->value, c);
			i++;
		}
		//free(temp);
		return (i);
	}
	else if (isalpha(src[i]) || src[i] == '_')
	{
		temp = ft_toknew(0, ARRAY);
		ft_tokadd_back(token, temp);
		while (src[i] && !ft_iswspace(src[i]) && (src [i] != '<' && src [i] != '>' && src [i] != '|' && src [i] != '-'))
		{
			c = src[i];
			temp->value = ft_charjoin(temp->value, c);
			i++;
		}
		//free(temp);
		return (i);
	}
	if (src[i] == '"')
	{
		temp = ft_toknew('"', LDQUO);
		ft_tokadd_back(token, temp);
		i++;
		temp = ft_toknew(0, ARRAY);
		ft_tokadd_back(token, temp);
		while (src[i] && src[i] != '"')
		{
			c = src[i];
			temp->value = ft_charjoin(temp->value, c);
			i++;
		}
		if (src[i] == '"')
		{
			temp = ft_toknew('"', RDQUO);
			ft_tokadd_back(token, temp);
			i++;
		}
		else
		{
			printf("%s\n", "Interractive mode");
			exit(EXIT_FAILURE);
		}
		//free(temp);
		return (i);
	}
	if (src[i] == '\'')
	{
		temp = ft_toknew('\'', LSQUO);
		ft_tokadd_back(token, temp);
		i++;
		temp = ft_toknew(0, ARRAY);
		ft_tokadd_back(token, temp);
		while (src[i] && src[i] != '\'')
		{
			c = src[i];
			temp->value = ft_charjoin(temp->value, c);
			i++;
		}
		if (src[i] == '\'')
		{
			temp = ft_toknew('\'', RSQUO);
			ft_tokadd_back(token, temp);
			i++;
		}
		else
		{
			printf("%s\n", "Interractive mode");
			exit(EXIT_FAILURE);
		}
		//free(temp);
		return (i);
	}
	else if (isdigit(src[i]))
	{
		temp = ft_toknew(0, INT);
		ft_tokadd_back(token, temp);
		while (isdigit(src[i]))
		{
			c = src[i];
			temp->value = ft_charjoin(temp->value, c);
			i++;
		}
		//free(temp);
		return (i);
	}
	else if (src[i] == '-')
	{
		temp = ft_toknew('-', SCO);
		ft_tokadd_back(token, temp);
		while (isalpha(src[++i]))
		{
			c = src[i];
			temp = ft_toknew(c, FLAG);
			ft_tokadd_back(token, temp);
		}
		//free(temp);
		return (i);
	}
	else if (src[i] == '=')
	{
		temp = ft_toknew('=', EQUAL);
		ft_tokadd_back(token, temp);
		i++;
		//free(temp);
		return (i);
	}
	else if (src[i] == '|')
	{
		temp = ft_toknew('|', PIPE);
		ft_tokadd_back(token, temp);
		i++;
		//free(temp);
		return (i);
	}
	else
		exit(EXIT_FAILURE);
}

// Initialiser le lexer avec une chaîne
void lexer_init(t_token **token, char *src)
{
	int i = 0;
	while (src[i]) {
		i += token_init(&src[i], token);
	}
}

void	init_cmd(t_commands **cmds, t_token *token)
{
	t_commands	*temp;

	while (token)
	{
		while (token && token->type != ARRAY && token->type != OFILE)
			token = token->next;
		temp = ft_cmdnew();
		ft_cmdadd_back(cmds, temp);
		while (token && token->type != PIPE)
			token = token->next;
	}
}

void	fill_cmd(t_commands **cmds, t_token *token)
{
	t_file	*temp1;
	int	array_count;
	int	i;

	i = 0;
	array_count = 0;
	while (token)
	{
		if (token->type == ARRAY)
		{
			if (array_count >=1)
			{
				temp1 = ft_filenew(token->value, NULL);
				ft_fileadd_back(&(*cmds)->args, temp1);
			}
			else
				(*cmds)->name = ft_strdup(token->value);
			array_count++;
		}
		else if (token->type == FLAG)
		{
			if (!(*cmds)->flags)
				(*cmds)->flags = ft_strjoin("-", (*cmds)->flags, 0);
			(*cmds)->flags = ft_strjoin((*cmds)->flags, token->value, 1);
	
		}
		else if (token->type == ORED)
		{
			token = token->next;
			temp1 = ft_filenew(token->value, ">");
			ft_fileadd_back(&(*cmds)->redirections, temp1);
		}
		else if (token->type == IRED)
		{
			token = token->next;
			temp1 = ft_filenew(token->value, "<");
			ft_fileadd_back(&(*cmds)->redirections, temp1);
		}
		else if (token->type == PIPE)
		{
			array_count = 0;
			cmds = &(*cmds)->next;
		}
		token = token->next;
	}
}

void exit_minishell(t_token **token, t_commands **cmds, char **user)
{
	ft_cmdsclear(cmds);
	ft_tokenclear(token);
	free(*user);
	printf("%s\n", "exit");
	exit(EXIT_SUCCESS);
}

int main(int argc, char **argv, char **env)
{
	t_token 			*token;
	t_commands			*cmds;
	char				*line;
	char				*user;
	char				**my_env;
	size_t				i;

	(void)argc;
	(void)argv;
	i = 0;
	user = get_user(env);
	if (user == NULL)
		return (-1);
	while (1)
	{
		token = NULL;
		cmds = NULL;
		line = readline(user);
		if (!line)
			exit_minishell(&token, &cmds, &user);
		if (*line)
			add_history(line);
		lexer_init(&token, line);
		//print_lst(token);
		// Free allocated memory (tokens list)
		init_cmd(&cmds, token);
		fill_cmd(&cmds, token);
		print_cmds(cmds);
		ft_pathfinder(cmds, env);
		my_env = ft_get_env(env);
		if (!my_env)
			printf("no env\n");
		
		if (!ft_exec_v1(&cmds, my_env))
			printf("execve failed\n");
		ft_free_tab(my_env);
		ft_cmdsclear(&cmds);
		ft_tokenclear(&token);
		free(line);
	}
	return (0);
}
