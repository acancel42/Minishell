#include "minishell.h"

// int	first_child(t_commands *cmds, t_data *data)
// {
// 	close(cmds->fd_p[0]);
// 	if (dup2(cmds->fd_p[1], STDOUT_FILENO) == -1)
// 		perror("dup");
// 	if (cmds->redirections)
// 		ft_wich_redir(cmds);
// 	close(cmds->fd_p[1]);
// 	if (!ft_is_built_in(data, cmds))
// 	{
// 		if (execve(cmds->path, cmds->args, data->my_env) == -1)
// 		{
// 			printf("execve failed pipe out\n");
// 			exit(EXIT_FAILURE);
// 		}
// 	}
// 	return (0);
// }

// int	last_child(t_commands *cmds, t_data *data, int *temp)
// {
// 	close(cmds->fd_p[1]);
// 	if (dup2(*temp, STDIN_FILENO) == -1)
// 		perror("dup");
// 	if (cmds->redirections)
// 		ft_wich_redir(cmds);
// 	close(cmds->fd_p[0]);
// 	close(*temp);
// 	if (!ft_is_built_in(data, cmds))
// 	{
// 		if (execve(cmds->path, cmds->args, data->my_env) == -1)
// 		{
// 			printf("execve failed pipe out\n");
// 			exit(EXIT_FAILURE);
// 		}
// 	}
// 	return (0);
// }

// int	middle_child(t_commands *cmds, t_data *data, int *temp)
// {
// 	printf("test\n");
// 	close(cmds->fd_p[0]);
// 	if (dup2(*temp, STDIN_FILENO) == -1)
// 		perror("dup");
// 	if (dup2(cmds->fd_p[1], STDOUT_FILENO) == -1)
// 		perror("dup");
// 	if (cmds->redirections)
// 		ft_wich_redir(cmds);
// 	close(cmds->fd_p[1]);
// 	close(*temp);
// 	dprintf(2, "%s\n", data->cmds->name);
// 	if (!ft_is_built_in(data, cmds))
// 	{
// 		if (execve(cmds->path, cmds->args, data->my_env) == -1)
// 		{
// 			printf("execve failed pipe out\n");
// 			exit(EXIT_FAILURE);
// 		}
// 	}
// 	return (0);
// }

// void	witch_child(t_commands *cmds, t_data *data, int *temp)
// {
// 	if (cmds->index == 0)
// 		first_child(cmds, data);
// 	else if (cmds->index == data->index_max)
// 		last_child(cmds, data, temp);
// 	else
// 		middle_child(cmds, data, temp);
// }

// int	ft_pipe(t_commands *cmds, t_data *data, t_token *token)
// {
// 	int	temp;
// 	t_commands *head;

// 	head = cmds;
// 	temp = -1;
// 	while (cmds != NULL)
// 	{
// 		if (pipe(cmds->fd_p) == -1)
// 			ft_exec_error(token, cmds, data, 0);
// 		cmds->pid = fork();
// 		if (cmds->pid == -1)
// 			ft_exec_error(token, cmds, data, 1);
// 		if (cmds->pid == 0)
// 			witch_child(cmds, data, &temp);
// 		if (temp != -1)
// 			close(temp);
// 		temp = cmds->fd_p[0];
// 		close(cmds->fd_p[1]);
// 		cmds = cmds->next;
// 	}
// 	cmds = head;
// 	ft_close_fd_pipe(cmds);
// 	while (wait(NULL) > 0)
// 		;
// 	return (0);
// }


