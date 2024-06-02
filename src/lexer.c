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

// Création d'un nouveau token
t_commands *ft_cmdnew(char *content)
{
	t_commands *new = ft_calloc(1, sizeof(t_commands));
	new->next = NULL;
	new->path = NULL;
	new->flags = NULL;
	new->valid_path = 0;
	new->name = ft_strdup(content);
	return (new);
}

t_file *ft_filenew(char *content)
{
	t_file *new = ft_calloc(1, sizeof(t_file));
	new->next = NULL;
	new->fd = 0;
	new->state = false;
	new->name = ft_strdup(content);
	return (new);
}

t_token *ft_toknew(char content, t_token_types type) {
	t_token *new = ft_calloc(1, sizeof(t_token));
	new->next = NULL;
	new->value = ft_chardup(content);
	new->type = type;
	return (new);
}

// Trouver le dernier token de la liste
t_file *ft_filelast(t_file *lst) {
	while (lst && lst->next != NULL)
		lst = lst->next;
	return (lst);
}

t_token *ft_toklast(t_token *lst) {
	while (lst && lst->next != NULL)
		lst = lst->next;
	return (lst);
}

t_commands *ft_cmdlast(t_commands *lst)
{
	while (lst && lst->next != NULL)
		lst = lst->next;
	return (lst);
}

int	ft_iswspace(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

// Ajouter un token à la fin de la liste
void ft_tokadd_back(t_token **lst, t_token *new)
{
	if (!lst || !new)
		return;
	t_token *temp = ft_toklast(*lst);
	if (temp != NULL)
		temp->next = new;
	else
		*lst = new;
}

void ft_cmdadd_back(t_commands **lst, t_commands *new)
{
	if (!lst || !new)
		return;
	t_commands *temp = ft_cmdlast(*lst);
	if (temp != NULL)
		temp->next = new;
	else
		*lst = new;
}

void ft_fileadd_back(t_file **lst, t_file *new)
{
	if (!lst || !new)
		return;
	t_file *temp = ft_filelast(*lst);
	if (temp != NULL)
		temp->next = new;
	else
		*lst = new;
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
	{
		exit(EXIT_FAILURE);
	}
}

// Initialiser le lexer avec une chaîne
void lexer_init(t_token **token, char *src)
{
	int i = 0;
	while (src[i]) {
		i += token_init(&src[i], token);
	}
}

void print_type(t_token_types type)
{
	if (type == ARRAY)
		printf("%s : ", "ARRAY");
	if (type == SCO)
		printf("%s : ", "SCO");
	if (type == FLAG)
		printf("%s : ", "FLAG");
	if (type == INT)
		printf("%s : ", "INT");
	if (type == LSQUO)
		printf("%s : ", "LSQUO");
	if (type == RSQUO)
		printf("%s : ", "RSQUO");
	if (type == RDQUO)
		printf("%s : ", "RDQUO");
	if (type == LDQUO)
		printf("%s : ", "LDQUO");
	if (type == EQUAL)
		printf("%s : ", "EQUAL");
	if (type == IRED)
		printf("%s : ", "IRED");
	if (type == ORED)
		printf("%s : ", "ORED");
	if (type == IAPP)
		printf("%s : ", "IAPP");
	if (type == OAPP)
		printf("%s : ", "OAPP");
	if (type == IFILE)
		printf("%s : ", "IFILE");
	if (type == OFILE)
		printf("%s : ", "OFILE");
	if (type == PIPE)
		printf("%s : ", "PIPE");
}

// Afficher les tokens
void	print_lst(t_token *token)
{
	while (token)
	{
		print_type(token->type);
		printf("%s\n", token->value);
		token = token->next;
	}
}

void	print_file(t_file *file, t_token_types type)
{
	while (file)
	{
		if (type == ARRAY)
			printf("arg : %s\n", file->name);
		if (type == IRED)
			printf("input : %s\n", file->name);
		if (type == ORED)
			printf("output : %s\n", file->name);
		file = file->next;
	}
}

void	print_cmds(t_commands *cmds)
{
	while (cmds)
	{
		printf("command : %s\n", cmds->name);
		printf("flags : %s\n", cmds->flags);
		print_file(cmds->args, ARRAY);
		print_file(cmds->input, IRED);
		print_file(cmds->output, ORED);
		printf("%c", '\n');
		cmds = cmds->next;
	}
}

void	init_cmd(t_commands **cmds, t_token *token)
{
	t_commands	*temp;

	while (token)
	{
		while (token && (token->type != ARRAY))
			token = token->next;
		temp = ft_cmdnew(token->value);
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
	t_token 	*token = NULL;
	t_token 	*temp;
	t_commands	*cmds = NULL;
	//t_commands	**head = NULL;

	if (argc != 2)
	{
		printf("Usage: %s <string>\n", argv[0]);
		return (1);
	}
	lexer_init(&token, argv[1]);
	//print_lst(token);
	// Free allocated memory (tokens list)
	init_cmd(&cmds, token);
	fill_cmd(&cmds, token);
	print_cmds(cmds);
	//head = &cmds;
	while (cmds)
	{
		cmds->valid_path = access(cmds->name, F_OK);
		cmd_path(cmds, env);
		if (cmds->path)
			printf("path : %s\n", cmds->path);
		cmds = cmds->next;
	}
	//cmds = *head;
	while (token)
	{
		temp = token;
		token = token->next;
		free(temp->value);
		free(temp);
	}

	return (0);
}
