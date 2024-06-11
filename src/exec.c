#include "minishell.h"
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

int	ft_exec_v1(t_commands *cmds, char **my_env)
{
	int		i;

	i = 0;
	cmds->infile_fd = -1;
	cmds->outfile_fd = -1;
	cmds->pid = -1;
	cmds->pid = fork();
	if (cmds->pid == 0)
	{
		if (execve(cmds->path, cmds->args, my_env) == -1)
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
	wait(NULL);
	return (0);
}
