#include "minishell.h"

void	ft_exec_error(t_token *token, t_commands *cmds, t_data *data, int flag)
{
	if (flag == 0)
		perror("pipe");
	else if (flag == 1)
		perror("fork");
	exit_minishell(&token, &cmds, data); //review that exit !!!!
}

void	ft_close_fd_pipe(t_commands *cmds)
{
	while (cmds != NULL)
	{
		close(cmds->fd_p[0]);
		cmds = cmds->next;
	}
}
