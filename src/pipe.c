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
			ft_wich_redir(cmds);
		else
			cmds->infile_fd = open(cmds->args[1], O_RDONLY);
		ft_dprintf("fdp1 %s\n", cmds->args[1]);
		// int i = -1;
		// while (cmds->args[++i])
		// 	ft_dprintf("pipe 1 args[%d] %s\n", i, cmds->args[i]);
		if (cmds->infile_fd == -1)
			perror(cmds->name);
		if (dup2(cmds->infile_fd, STDIN_FILENO) == -1)
			perror("dup IN p1");
		close(cmds->infile_fd);
		if (dup2(cmds->fd_p[1], STDOUT_FILENO) == -1)
			perror("dup OUT p1");
		close(cmds->fd_p[1]);
		if (execve(cmds->path, cmds->args, my_env) == -1)
		{
			printf ("p1 path = %s args = %s, my env %s\n", cmds->path, cmds->args[1], my_env[0]);
			printf("execve failed pipe in\n");
			return (-1);
		}
	}
	cmds->pid = fork();
	if (cmds->pid == -1)
		perror("fork");
	if (cmds->pid == 0)
	{
		close(cmds->fd_p[1]);
		if (cmds->next->redirections)
			ft_wich_redir(cmds->next);
		else
			cmds->outfile_fd = open(cmds->next->args[1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
		ft_dprintf("--fd p2 %s\n", cmds->next->args[1]);
		// int i = -1;
		// while (cmds->next->args[++i])
		// 	ft_dprintf("--p2 args[%d] %s\n", i, cmds->next->args[i]);
		if (cmds->outfile_fd == -1)
			perror(cmds->next->name);
		if (dup2(cmds->fd_p[0], STDIN_FILENO) == -1)
			perror("dup out p2");
		if (dup2(cmds->outfile_fd, STDOUT_FILENO) == -1)
			perror("dup in p2");
		close(cmds->outfile_fd);
		close(cmds->fd_p[0]);
		if (execve(cmds->next->path, cmds->next->args, my_env) == -1)
		{
			printf ("p2 path = %s args = %s, my env %s\n", cmds->path, cmds->args[1], my_env[0]);
			printf("execve failed pipe out\n");
			return (-1);
		}
	}
	close(cmds->fd_p[0]);
	close(cmds->fd_p[1]);
	return (0);
}
