#include "minishell.h"
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

int			ft_exec_v1(t_commands *cmds, char **my_env)
{
	char	**arguments;
	int		i;

	printf("Name = %s\nPATH = %s\nFlags = %s\nFile Name = %s\n", cmds->name, cmds->path, cmds->flags, cmds->file_name);
	i = 0;
	cmds->infile_fd = -1;
	cmds->outfile_fd = -1;
	cmds->pid = -1;
	printf("bf fork\n");
	cmds->pid = fork();
	if (cmds->pid == 0)
	{
		cmds->infile_fd = open("../Makefile", O_RDONLY);
		if (cmds->infile_fd == -1)
			printf("error read\n");
		printf("fd = %d\n", cmds->infile_fd);
		arguments = ft_calloc(3, sizeof(char *));
		if (arguments == NULL)
			printf("Error calloc\n");
		arguments[i] = ft_strdup(cmds->name);
		if (arguments[i] == NULL)
			printf("dup1 failed\n");
		i++;
		if (cmds->flags)
		{
			arguments[i] = ft_strdup(cmds->flags);
			i++;
		}
		//arguments[i] = ft_strdup("Makefile");
		// if (arguments[i] == NULL)
		// 	printf("dup2 failed\n");
		// printf("avant execve : path : %s\n", cmds->path);
		// while (arguments[i])
		// {
		// 	printf("arg[%i] = %s\n", i, arguments[i]);
		// 	i++;
		// }
		// i = 0;
		// while (my_env[i])
		// {
		// 	printf("env[%i] = %s\n", i, my_env[i]);
		// 	i++;
		// }
		close(cmds->infile_fd);
		if (execve(cmds->path, arguments, my_env) == -1)
		{
			printf("execve failed\n");
		}
		close(cmds->infile_fd);
		return (-1);
	}
	if (cmds->pid == -1)
	{
		printf("fork error\n");
		return (-1);
	}
	while (wait(NULL))
		;
	printf("jgfdhjgfdhjgfjhgfsjgshjhfjghjgshfj\n");
	return (0);
}
