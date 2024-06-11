#include "minishell.h"

void print_type(t_token_types type)
{
	if (type == T_WORD)
		printf("%s : ", "T_WORD");
	if (type == T_PIPE)
		printf("%s : ", "T_PIPE");
	if (type == T_REDIR_IN)
		printf("%s : ", "T_REDIR_IN");
	if (type == T_REDIR_OUT)
		printf("%s : ", "T_REDIR_OUT");
	if (type == T_APPEND_OUT)
		printf("%s : ", "T_APPEND_OUT");
	if (type == T_HEREDOC)
		printf("%s : ", "T_HEREDOC");
	if (type == T_D_QUOTED_WORD)
		printf("%s : ", "T_D_QUOTED_WORD");
	if (type == T_S_QUOTED_WORD)
		printf("%s : ", "T_S_QUOTED_WORD");
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

void	print_file(t_file *file)
{
	while (file)
	{

		printf("redirection : %s\n", file->name);
		file = file->next;
	}
}

void	print_cmds(t_commands *cmds)
{
	int	i;

	while (cmds)
	{
		i = -1;
		printf("command : %s\n", cmds->name);
		while (cmds->args[++i])
			printf("args : %s\n", cmds->args[i]);
		print_file(cmds->redirections);
		printf("%c", '\n');
		cmds = cmds->next;
	}
}
