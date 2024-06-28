#include "minishell.h"

int	first_child(t_commands *cmds, char **my_env)
{
	close(cmds->fd_p[0]);
	if (dup2(cmds->fd_p[1], STDOUT_FILENO) == -1)
		perror("dup");
	if (cmds->redirections)
		ft_wich_redir(cmds);
	close(cmds->fd_p[1]);
	if (execve(cmds->path, cmds->args, my_env) == -1)
	{
		printf("execve failed pipe in\n");
		return (-1);
	}
	return (0);
}

int	last_child(t_commands *cmds, char **my_env, int*temp)
{
	close(cmds->fd_p[1]);
	if (dup2(*temp, STDIN_FILENO) == -1)
		perror("dup");
	if (cmds->redirections)
		ft_wich_redir(cmds);
	close(cmds->fd_p[0]);
	if (execve(cmds->path, cmds->args, my_env) == -1)
	{
		printf("execve failed pipe out\n");
		return (-1);
	}
	return (0);
}

int	middle_child(t_commands *cmds, char **my_env, int *temp)
{
	close(cmds->fd_p[0]);
	if (dup2(*temp, STDIN_FILENO) == -1)
		perror("dup");
	if (dup2(cmds->fd_p[1], STDOUT_FILENO) == -1)
		perror("dup");
	if (cmds->redirections)
		ft_wich_redir(cmds);
	close(cmds->fd_p[1]);
	if (execve(cmds->path, cmds->args, my_env) == -1)
	{
		printf("execve failed pipe out\n");
		return (-1);
	}
	return (0);
}

void witch_child(t_commands *cmds, char **my_env, t_data *data, int *temp)
{
	printf("%d %d\n", cmds->index, data->index_max);
	if (cmds->index == 0)
		first_child(cmds, my_env);
	else if (cmds->index == data->index_max)
		last_child(cmds, my_env, temp);
	else
		middle_child(cmds, my_env, temp);
}

int	ft_pipe(t_commands *cmds, t_data *data, t_token *token)
{
	int	temp;

	temp = -1;
	(void)token;
	while (cmds != NULL)
	{
		if (pipe(cmds->fd_p) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
			//exit_minishell(&token, &cmds, NULL, &data->my_env);
		}
		cmds->pid = fork();
		if (cmds->pid == -1)
			perror("fork");
		if (cmds->pid == 0)
			witch_child(cmds, data->my_env, data, &temp);
		temp = cmds->fd_p[0];
		// close(cmds->fd_p[0]); need to close temp !
		close(cmds->fd_p[1]);
		cmds = cmds->next;
	}
	while (wait(NULL) > 0)
		;
	return (0);
}

//test
//gjfdxjgdjgj

