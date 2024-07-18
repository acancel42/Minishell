#include "minishell.h"

void	exit_minishell(t_token **token, t_commands **cmds, t_data *data)
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

void	ft_exec_error(t_token *token, t_commands *cmds, t_data *data, int flag)
{
	if (flag == 0)
		perror("pipe");
	else if (flag == 1)
		perror("fork");
	else if (flag == 2)
		perror("dup2");
	exit_minishell(&token, &cmds, data);
}
