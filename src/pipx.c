/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipx.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acancel <acancel@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 23:13:00 by acancel           #+#    #+#             */
/*   Updated: 2024/07/17 01:49:25 by acancel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pip(t_commands *cmds, t_data *data, t_token *token)
{
	int		fd_pipe[2];
	int 	status;
	pid_t	pid;
	
	printf("1\n");
	if (pipe(fd_pipe) == -1)
		return(ft_exec_error(token, cmds, data, 0), -1);
	cmds->next->infile_fd = fd_pipe[0];
	cmds->outfile_fd = fd_pipe[1];
	if (cmds->redirections)
		ft_wich_redir(cmds);
	pid = fork();
	if (pid == -1)
		return(ft_exec_error(token, cmds, data, 1), -1);
	if (pid == 0)
	{
		close(fd_pipe[0]);
		if (dup2(fd_pipe[1], STDOUT_FILENO) == -1)
			return(ft_exec_error(token, cmds, data, 2), 1);
		if (dup2(cmds->infile_fd, STDIN_FILENO) == -1)
			return(ft_exec_error(token, cmds, data, 2), 1);
		if (execve(cmds->path, cmds->args, data->my_env) == -1)
		{
			printf("execve failed pipe out\n");
			exit(EXIT_FAILURE);
		}		
	}
	waitpid(pid, &status, 0);
	close(fd_pipe[1]);
	return (0);	
}

int	ft_last_cmd(t_commands *cmds, t_data *data, t_token *token)
{
	int 	status;
	pid_t	pid;

	printf("2\n");
	if (cmds->redirections)
		ft_wich_redir(cmds);
	pid = fork();
	if (pid == -1)
		return(ft_exec_error(token, cmds, data, 1), -1);
	if (pid == 0)
	{
		if (dup2(cmds->outfile_fd, STDOUT_FILENO) == -1)
			return(ft_exec_error(token, cmds, data, 2), 1);
		if (dup2(cmds->infile_fd, STDIN_FILENO) == -1)
			return(ft_exec_error(token, cmds, data, 2), 1);
		if (execve(cmds->path, cmds->args, data->my_env) == -1)
		{
			printf("execve failed pipe out\n");
			exit(EXIT_FAILURE);
		}		
	}
	waitpid(pid, &status, 0);
	return (0);	
}
