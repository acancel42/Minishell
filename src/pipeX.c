/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeX.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acancel <acancel@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 23:13:00 by acancel           #+#    #+#             */
/*   Updated: 2024/07/31 11:25:28 by acancel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_child(int *fd_pipe, t_data *data, t_commands *cmds)
{
	struct stat	sb;

	ft_signalhandle_in_child();
	close(fd_pipe[0]);
	if (dup2(cmds->outfile_fd, STDOUT_FILENO) == -1)
		ft_exec_error(data->token, cmds, data, 2);
	if (dup2(cmds->infile_fd, STDIN_FILENO) == -1)
		ft_exec_error(data->token, cmds, data, 2);
	if (ft_exec_built_in(data->token, cmds, data))
		exit(EXIT_SUCCESS);
	if (execve(cmds->path, cmds->args, data->my_env) == -1)
	{
		if (ft_strchr_b(cmds->name, '/') == 0 && stat(cmds->args[0], &sb) == 0)
		{
			if (dup2(STDOUT_FILENO, 1) == -1)
				ft_exec_error(data->token, cmds, data, 2);
			if (cmds->name[ft_strlen(cmds->name) - 1] == '/' || \
				cmds->name[ft_strlen(cmds->name) - 1] == '.')
				printf("%s : Is a directory\n", cmds->name);
			data->last_error_status = 126;
		}
		else
			ft_putendl_fd("execve failed", 2);
		exit(EXIT_FAILURE);
	}
}

int	ft_pipe(t_commands *cmds, t_data *data, t_token *token)
{
	int		fd_pipe[2];
	int		status;

	if (pipe(fd_pipe) == -1)
		return (ft_exec_error(token, cmds, data, 0), -1);
	cmds->next->infile_fd = fd_pipe[0];
	cmds->outfile_fd = fd_pipe[1];
	if (cmds->redirections)
		ft_redir_or_append(data, cmds);
	ft_wait_signal();
	data->pid = fork();
	if (data->pid == -1)
		return (ft_exec_error(token, cmds, data, 1), -1);
	if (data->pid == 0)
		exec_child(fd_pipe, data, cmds);
	wait(&status);
	data->last_error_status = WEXITSTATUS(status);
	if (cmds->outfile_fd != 1)
		close(cmds->outfile_fd);
	if (cmds->infile_fd != 0)
		close(cmds->infile_fd);
	return (0);
}

static void	ft_builtin_or_exec(t_data *data, t_commands *cmds)
{
	struct stat	sb;

	if (ft_exec_built_in(data->token, cmds, data) == 1)
		exit(EXIT_SUCCESS);
	if (execve(cmds->path, cmds->args, data->my_env) == -1)
	{
		if (ft_strchr_b(cmds->name, '/') == 0 && stat(cmds->args[0], &sb) == 0)
		{
			if (cmds->name[ft_strlen(cmds->name) - 1] == '/' || \
				cmds->name[ft_strlen(cmds->name) - 1] == '.')
				printf ("%s : Is a directory\n", cmds->name);
			data->last_error_status = 126;
		}
		else
			ft_putendl_fd("execve failed", 2);
		exit(data->last_error_status);
	}
}

int	ft_exec_cmd(t_commands *cmds, t_data *data, t_token *token)
{
	int	status;

	if (cmds->name && ft_strncmp(cmds->name, "", 1) == 0)
		return (0);
	if (cmds->redirections)
		ft_redir_or_append(data, cmds);
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
		ft_builtin_or_exec(data, cmds);
	}
	wait(&status);
	data->last_error_status = WEXITSTATUS(status);
	if (cmds->outfile_fd != 1)
		close(cmds->outfile_fd);
	if (cmds->infile_fd != 0)
		close(cmds->infile_fd);
	return (0);
}

void	exec_cmd(t_data *data, t_commands *cmds)
{
	t_commands	*temp;

	temp = cmds;
	while (temp)
	{
		if (data->pflag != 0)
		{
			if (temp->index >= data->index_max)
				ft_exec_cmd(temp, data, data->token);
			else
				ft_pipe(temp, data, data->token);
		}
		else
			ft_exec_cmd(temp, data, data->token);
		temp = temp->next;
	}
}
