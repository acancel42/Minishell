#include "minishell.h"

int	ft_redir_output(t_file *redir)
{
	redir->fd = open(redir->name, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (redir->fd == -1)
		perror(redir->name);
	if (dup2(redir->fd, STDOUT_FILENO) == -1)
		perror("dup out");
	close(redir->fd);
	return (0);
}

int	ft_redir_input(t_file *redir)
{
	redir->fd = open(redir->name, O_RDONLY);
	if (redir->fd == -1)
		perror(redir->name);
	if (dup2(redir->fd, STDIN_FILENO) == -1)
		perror("dup in");
	close(redir->fd);
	return (0);
}

int ft_wich_redir(t_file *redirection)
{
	while (redirection)
	{

		if (!ft_strncmp(redirection->name, ">", 1))
		{
			redirection->name = ft_strdup(redirection->name + 1);
			ft_redir_output(redirection);
		}
		else if (!ft_strncmp(redirection->name, "<", 1))
		{
			redirection->name = ft_strdup(redirection->name + 1);
			ft_redir_input(redirection);
		}
		redirection = redirection->next;
	}
	return (0);
}