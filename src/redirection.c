#include "minishell.h"

int	ft_redir_output(t_data *data)
{
	data->cmds->outfile_fd = open(data->cmds->redirections->name, \
			O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (data->cmds->outfile_fd == -1)
		perror(data->cmds->redirections->name);
	if (dup2(data->cmds->outfile_fd, STDOUT_FILENO) == -1)
		perror("dup out redir");
	return (0);
}

int	ft_redir_input(t_data *data)
{
	data->cmds->infile_fd = open(data->cmds->redirections->name, O_RDONLY);
	if (data->cmds->infile_fd == -1)
		perror(data->cmds->redirections->name);
	if (dup2(data->cmds->infile_fd, STDIN_FILENO) == -1)
		perror("dup in redir");
	return (0);
}


int	ft_wich_redir(t_data *data)
{
	char	*temp;

	while (data->cmds->redirections)
	{
		if (!ft_strncmp(data->cmds->redirections->name, ">", 1))
		{
			data->cmds->redirections->name = \
				ft_strdup(data->cmds->redirections->name + 1);
			ft_redir_output(data);
			temp = ft_strdup(">");
			data->cmds->redirections->name = \
				ft_strjoin(temp, data->cmds->redirections->name, 1);
		}
		else if (!ft_strncmp(data->cmds->redirections->name, "<", 1))
		{
			data->cmds->redirections->name = \
				ft_strdup(data->cmds->redirections->name + 1);
			ft_redir_input(data);
			temp = ft_strdup("<");
			data->cmds->redirections->name = \
				ft_strjoin(temp, data->cmds->redirections->name, 1);
		}
		data->cmds->redirections = data->cmds->redirections->next;
	}
	return (0);
}

