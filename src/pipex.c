/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acancel <acancel@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 08:58:12 by acancel           #+#    #+#             */
/*   Updated: 2024/09/25 08:58:13 by acancel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_child(t_data *data, t_commands **cmds)
{
	int	exit_status;

	free_data(data, cmds, &data->token);
	if (data->home)
		free(data->home);
	if (data->export)
		ft_free_tab(data->export);
	if (data->my_env)
		ft_free_tab(data->my_env);
	exit_status = data->last_error_status;
	free(data);
	exit(exit_status);
}

static void	exec_child(t_commands *head, int *fd_pipe, \
						t_data *data, t_commands *cmds)
{
	struct stat	sb;
	int			ret;

	ret = 0;
	ft_signalhandle_in_child();
	ft_dup2(data, cmds);
	close_files(cmds, data);
	if (ft_exec_built_in(data->token, cmds, data) == 1)
	{
		ft_close(fd_pipe[0], data, cmds, 2);
		free_child(data, &head);
	}
	ft_close(fd_pipe[0], data, cmds, 2);
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
	{
		if (ft_redir_or_append(data, cmds) == -1 || !cmds->name)
		{
			close_files(cmds, data);
			return (0);
		}
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
