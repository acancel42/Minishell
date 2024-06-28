#include "minishell.h"

int	first_child(t_data *data)
{
	close(data->cmds->fd_p[0]);
	if (dup2(data->cmds->fd_p[1], STDOUT_FILENO) == -1)
		perror("dup");
	if (data->cmds->redirections)
		ft_wich_redir(data->cmds);
	close(data->cmds->fd_p[1]);
	if (execve(data->cmds->path, data->cmds->args, data->my_env) == -1)
	{
		printf("execve failed pipe in\n");
		return (-1);
	}
	return (0);
}

int	last_child(t_data *data, int *temp)
{
	close(data->cmds->fd_p[1]);
	if (dup2(*temp, STDIN_FILENO) == -1)
		perror("dup");
	if (data->cmds->redirections)
		ft_wich_redir(data->cmds);
	close(data->cmds->fd_p[0]);
	if (execve(data->cmds->path, data->cmds->args, data->my_env) == -1)
	{
		printf("execve failed pipe out\n");
		return (-1);
	}
	return (0);
}

int	middle_child(t_data *data, int *temp)
{
	close(data->cmds->fd_p[0]);
	if (dup2(*temp, STDIN_FILENO) == -1)
		perror("dup");
	if (dup2(data->cmds->fd_p[1], STDOUT_FILENO) == -1)
		perror("dup");
	if (data->cmds->redirections)
		ft_wich_redir(data->cmds);
	close(data->cmds->fd_p[1]);
	if (execve(data->cmds->path, data->cmds->args, data->my_env) == -1)
	{
		printf("execve failed pipe out\n");
		return (-1);
	}
	return (0);
}

void	witch_child(t_data *data, int *temp)
{
	if (data->cmds->index == 0)
		first_child(data);
	else if (data->cmds->index == data->index_max)
		last_child(data, temp);
	else
		middle_child(data, temp);
}

int	ft_pipe(t_data *data)
{
	int	temp;

	temp = -1;
	while (data->cmds->next != NULL)
	{
		if (pipe(data->cmds->fd_p) == -1)
		{
			perror("pipe");
			exit_minishell(&data->token, &data->cmds, data, NULL); //review that exit !!!!
		}
		data->cmds->pid = fork();
		if (data->cmds->pid == -1)
			perror("fork");
		if (data->cmds->pid == 0)
			witch_child(data, &temp);
		if (temp != -1)
			close(temp);
		temp = data->cmds->fd_p[0];
		close(data->cmds->fd_p[0]);
		close(data->cmds->fd_p[1]);
		data->cmds = data->cmds->next;
	}
	while (wait(NULL) > 0)
		;
	return (0);
}


