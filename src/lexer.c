#include "../inc/minishell.h"
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

int	ft_iswspace(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

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
		while (src[i] && !ft_iswspace(src[i]))
		{
			c = src[i];
			temp->value = ft_charjoin(temp->value, c);
			i++;
		}
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
		while (src[i] && !ft_iswspace(src[i]))
		{
			c = src[i];
			temp->value = ft_charjoin(temp->value, c);
			i++;
		}
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
		return (i);
	}
	else if (src[i] == '=')
	{
		temp = ft_toknew('=', EQUAL);
		ft_tokadd_back(token, temp);
		i++;
		return (i);
	}
	else if (src[i] == '|')
	{
		temp = ft_toknew('|', PIPE);
		ft_tokadd_back(token, temp);
		i++;
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
				temp1 = ft_filenew(token->value);
				ft_fileadd_back(&(*cmds)->args, temp1);
			}
			else
				(*cmds)->name = ft_strdup(token->value);
			array_count++;
		}
		else if (token->type == FLAG)
		{
			(*cmds)->flags = ft_strjoin((*cmds)->flags, token->value);
		}
		else if (token->type == ORED)
		{
			token = token->next;
			temp1 = ft_filenew(token->value);
			ft_fileadd_back(&(*cmds)->output, temp1);
		}
		else if (token->type == IRED)
		{
			token = token->next;
			temp1 = ft_filenew(token->value);
			ft_fileadd_back(&(*cmds)->input, temp1);
		}
		else if (token->type == PIPE)
		{
			array_count = 0;
			cmds = &(*cmds)->next;
		}
		token = token->next;
	}
}

int main(int argc, char **argv, char **env)
{
	t_token 	*token;
	t_token 	*temp;
	t_commands	*cmds;
	char	*line;
	char	*user;

	(void)argc;
	(void)argv;
	user = get_user(env);
	if (user == NULL)
		return (-1);
	while (1)
	{
		token = NULL;
		cmds = NULL;
		line = readline(user);
		if (!line)
			break ;
		//if (*line)
		//	add_history(line);
		lexer_init(&token, line);
		//print_lst(token);
		// Free allocated memory (tokens list)
		init_cmd(&cmds, token);
		fill_cmd(&cmds, token);
		print_cmds(cmds);
		ft_pathfinder(cmds, env);
		free_all(cmds, NULL);
		while (token)
		{
			temp = token;
			token = token->next;
			free(temp->value);
			free(temp);
		}
		//print_cmds(cmds);
		free(line);
	}
	free(user);
	//t_commands	**head = NULL;
	//cmds = *head;
	while (token)
	{
		temp = token;
		token = token->next;
		free(temp->value);
		free(temp);
	}
	//free_all(cmds, NULL);
	return (0);
}
