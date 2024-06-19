#include "minishell.h"

int	ft_pipe(t_commands *cmds, char **my_env)
{
	cmds->infile_fd = -1;
	cmds->outfile_fd = -1;
	cmds->pid = -1;
	if (pipe(cmds->fd_p) == -1)
	{
		perror("pipe");
		exit_minishell(NULL, &cmds, NULL); // ?? data still malloced
	}
	cmds->pid = fork();
	if (cmds->pid == -1)
		perror("fork");
	if (cmds->pid == 0)
	{
		close(cmds->fd_p[0]);
		if (cmds->redirections)
			ft_wich_redir(cmds->redirections);
		cmds->infile_fd = open(cmds->name, O_RDONLY);
		ft_dprintf("%s", cmds->name);
		int i = 0;
		while (cmds->args[++i])
			ft_dprintf("pipe 1 args[i] %s\n", cmds->args[i]);
		if (cmds->infile_fd == -1)
			perror(cmds->name);
		if (dup2(cmds->infile_fd, STDIN_FILENO) == -1)
			perror("dup IN");
		close(cmds->infile_fd);
		if (dup2(cmds->fd_p[1], STDOUT_FILENO) == -1)
			perror("dup in");
		close(cmds->fd_p[1]);
		if (execve(cmds->path, cmds->args, my_env) == -1)
		{
			printf("execve failed\n");
			return (-1);
		}
	}
	cmds->pid = fork();
	if (cmds->pid == -1)
		perror("fork");
	if (cmds->pid == 0)
	{
		close(cmds->fd_p[1]);
		if (cmds->redirections)
			ft_wich_redir(cmds->redirections);
		cmds->outfile_fd = open(cmds->name, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		ft_dprintf("%s", cmds->name);
		int i = 0;
		while (cmds->args[++i])
			ft_dprintf("args[i] %s\n", cmds->args[i]);
		if (cmds->outfile_fd == -1)
			perror(cmds->name);
		if (dup2(cmds->fd_p[0], STDIN_FILENO) == -1)
			perror("dup out");
		if (dup2(cmds->outfile_fd, STDOUT_FILENO) == -1)
			perror("dup in");
		close(cmds->outfile_fd);
		close(cmds->fd_p[0]);
		if (execve(cmds->path, cmds->args, my_env) == -1)
		{
			printf("execve failed\n");
			return (-1);
		}
	}
	close(cmds->fd_p[0]);
	close(cmds->fd_p[1]);
	return (0);
}
