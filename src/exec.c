#include "minishell.h"
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

int	ft_exec(t_commands *cmds, t_data *data)
{
	cmds->infile_fd = -1;
	cmds->outfile_fd = -1;
	cmds->pid = -1;
	cmds->pid = fork();
	if (cmds->pid == 0)
	{
		if (cmds->redirections)
			ft_wich_redir(cmds);
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
