#include "minishell.h"
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

int	ft_exec(t_commands *cmds, t_data *data)
{
	cmds->pid = -1;
	cmds->pid = fork();
	if (cmds->pid == 0)
	{
		if (cmds->redirections)
			ft_wich_redir(cmds);
		if (dup2(cmds->outfile_fd, STDOUT_FILENO) == -1)
			return(ft_exec_error(data->token, cmds, data, 2), 1);
		if (dup2(cmds->infile_fd, STDIN_FILENO) == -1)
			return(ft_exec_error(data->token, cmds, data, 2), 1);	
		if (execve(cmds->path, cmds->args, data->my_env) == -1)
		{
			printf("execve failed\n");
			return (-1);
		}
	}
	if (cmds->pid == -1)
	{
		printf("fork error\n");
		return (-1);
	}
	while (wait(NULL) > 0)
		;
	return (0);
}
