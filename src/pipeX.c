#include "minishell.h"

static void	exec_child(t_commands *head, int *fd_pipe, \
						t_data *data, t_commands *cmds)
{
	struct stat	sb;

	ft_signalhandle_in_child();
	(void)fd_pipe;
	ft_close(fd_pipe[0], data, cmds, 2);
	if (dup2(cmds->outfile_fd, STDOUT_FILENO) == -1)
		ft_exec_error(data->token, cmds, data, 2);
	if (dup2(cmds->infile_fd, STDIN_FILENO) == -1)
		ft_exec_error(data->token, cmds, data, 2);
	close_files(cmds, data);
	if (ft_exec_built_in(data->token, cmds, data) == 1)
		free_child(data, &head);
	if (execve(cmds->path, cmds->args, data->my_env) != -1)
		return ;
	if (access(cmds->name, F_OK) == 0 && stat(cmds->args[0], &sb) == 0)
	{
		printf ("%s : Is a directory\n", cmds->name);
		data->last_error_status = 126;
	}
	else
		ft_putendl_fd("execve failed", 2);
	free_child(data, &head);
}

int	ft_pipe(t_commands *head, t_commands *cmds, t_data *data, t_token *token)
{
	int		fd_pipe[2];

	if (pipe(fd_pipe) == -1)
		return (ft_exec_error(token, cmds, data, 0), -1);
	cmds->next->infile_fd = fd_pipe[0];
	cmds->outfile_fd = fd_pipe[1];
	if (cmds->redirections)
		if (ft_redir_or_append(data, cmds) == -1)
			return (0);
	if (!cmds->name)
	{
		ft_close(fd_pipe[1], data, cmds, 2);
		return (0);
	}
	ft_wait_signal();
	data->pid = fork();
	if (data->pid == -1)
		return (ft_exec_error(token, cmds, data, 1), -1);
	if (data->pid == 0)
		exec_child(head, fd_pipe, data, cmds);
	close_files(cmds, data);
	return (0);
}

static void	ft_builtin_or_exec(t_data *data, t_commands *cmds, t_commands *head)
{
	struct stat	sb;

	close_files(cmds, data);
	if (ft_exec_built_in(data->token, cmds, data) == 1)
		free_child(data, &head);
	if (execve(cmds->path, cmds->args, data->my_env) == -1)
	{
		if (access(cmds->name, F_OK) == 0 && stat(cmds->args[0], &sb) == 0)
		{
			printf ("%s : Is a directory\n", cmds->name);
			data->last_error_status = 126;
		}
		else
			ft_putendl_fd("execve failed", 2);
		free_child(data, &head);
	}
}

int	ft_exec_cmd(t_commands *head, t_commands *cmds, \
				t_data *data, t_token *token)
{
	if (cmds->name && ft_strncmp(cmds->name, "", 1) == 0)
		return (0);
	if (cmds->redirections)
		if (ft_redir_or_append(data, cmds) == -1)
			return (0);
	if (!cmds->name)
	{
		close_files(cmds, data);
		return (0);
	}
	ft_wait_signal();
	data->pid = fork();
	if (data->pid == -1)
		return (ft_exec_error(token, cmds, data, 1), -1);
	if (data->pid == 0)
	{
		ft_signalhandle_in_child();
		if (dup2(cmds->outfile_fd, STDOUT_FILENO) == -1)
			return (ft_exec_error(token, cmds, data, 2), 1);
		if (dup2(cmds->infile_fd, STDIN_FILENO) == -1)
			return (ft_exec_error(token, cmds, data, 2), 1);
		ft_builtin_or_exec(data, cmds, head);
	}
	close_files(cmds, data);
	return (0);
}

void	exec_cmd(t_data *data, t_commands *cmds)
{
	t_commands	*temp;
	int			status;

	status = 0;
	temp = cmds;
	while (temp)
	{
		if (data->pflag != 0)
		{
			if (temp->index >= data->index_max)
				ft_exec_cmd(cmds, temp, data, data->token);
			else
				ft_pipe(cmds, temp, data, data->token);
		}
		else
			ft_exec_cmd(cmds, temp, data, data->token);
		if (g_sigint == 2)
			break ;
		temp = temp->next;
	}
	waitpid(data->pid, &status, 0);
	while (wait(0) != -1)
		;
	data->last_error_status = WEXITSTATUS(status);
}
