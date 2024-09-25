#include "minishell.h"

void	print_type(t_token_types type)
{
	if (type == T_WORD)
		printf("%s : ", "T_WORD");
	if (type == T_RWORD)
		printf("%s : ", "T_RWORD");
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
	if (type == T_RD_QUOTED_WORD)
		printf("%s : ", "T_RD_QUOTED_WORD");
	if (type == T_RS_QUOTED_WORD)
		printf("%s : ", "T_RS_QUOTED_WORD");
}

// Afficher les tokens
void	print_lst(t_token *token)
{
	while (token)
	{
		print_type(token->type);
		printf("'%s'\n", token->value);
		token = token->next;
	}
}

void	print_cmds(t_commands *cmds) // dprintf for pipes debug !
{
	int	i;
	int	j;

	while (cmds)
	{
		j = -1;
		i = -1;
		ft_dprintf("command : '%s'\n", cmds->name);
		ft_dprintf(2, "args 0 : '%s'\n", cmds->args[0]);
		while (cmds->args[++i])
			ft_dprintf("args : '%s'\n", cmds->args[i]);
		while (cmds->redirections[++j])
			ft_dprintf("redir : '%s'\n", cmds->redirections[j]);
		ft_dprintf("path : '%s'\n", cmds->path);
		ft_dprintf("%c", '\n');
		cmds = cmds->next;
	}
}

void	print_my_env(char **my_env)
{
	int	i;

	i = -1;
	while (my_env[++i])
		printf("%s\n", my_env[i]);
	return ;
}
