#include "minishell.h"
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

int	ft_exec_v1(t_data *data)
{
	data->cmds->infile_fd = -1;
	data->cmds->outfile_fd = -1;
	data->cmds->pid = -1;
	data->cmds->pid = fork();
	if (data->cmds->pid == 0)
	{
		if (data->cmds->redirections)
			ft_wich_redir(data);
		if (execve(data->cmds->path, data->cmds->args, data->my_env) == -1)
		{
			printf("execve failed\n");
			return (-1);
		}
	}
	if (data->cmds->pid == -1)
	{
		printf("fork error\n");
		return (-1);
	}
	while (wait(NULL) > 0)
		;
	return (0);
}
