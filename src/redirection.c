#include "minishell.h"

int	ft_redir_output(t_commands *cmds, int i)
{
	cmds->outfile_fd = open(cmds->redirections[i], \
			O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (cmds->outfile_fd == -1)
	{
		perror(cmds->redirections[i]);
		return (-1);
	}
	if (!cmds->name)
		close(cmds->outfile_fd);
	return (0);
}

int	ft_redir_input(t_commands *cmds, int i)
{
	cmds->infile_fd = open(cmds->redirections[i], O_RDONLY);
	if (cmds->infile_fd == -1)
	{
		perror(cmds->redirections[i]);
		return (-1);
	}
	return (0);
}

int	ft_wich_redir(t_commands *cmds, int i)
{
	char	*temp;
	char	redir_type;

	temp = NULL;
	redir_type = cmds->redirections[i][0];
	temp = ft_strdup(cmds->redirections[i] + 1);
	if (!temp)
		return (-1);
	free(cmds->redirections[i]);
	cmds->redirections[i] = ft_strdup(temp);
	if (!cmds->redirections[i])
		return (-1);
	if (temp)
		free(temp);
	if (redir_type == '>')
	{
		if (ft_redir_output(cmds, i) == -1)
			return (-1);
	}
	else if (cmds->name)
	{
		if (ft_redir_input(cmds, i) == -1)
			return (-1);
	}
	return (0);
}

int	ft_append(t_data *data, t_commands *cmds, char *file, int flag)
{
	char	*temp;

	temp = NULL;
	if (flag)
	{
		temp = ft_strdup(file + 1);
		if (!temp)
			ft_exit(data->token, data->cmds, data);
	}
	cmds->outfile_fd = open(temp, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (cmds->outfile_fd == -1)
		perror(temp);
	if (temp)
		free(temp);
	if (!cmds->name)
		close(cmds->outfile_fd);
	return (0);
}

int	ft_redir_or_append(t_data *data, t_commands *cmds)
{
	int		i;

	i = 0;
	while (cmds->redirections[i])
	{
		if (cmds->redirections[i][0] == '+')
			ft_append(data, cmds, cmds->redirections[i], 1);
		else if (cmds->redirections[i][0] == '-')
		{
			handle_heredoc(data, cmds, cmds->redirections[i] + 1);
		}
		else if (cmds->redirections[i][0] == '<' || \
					cmds->redirections[i][0] == '>')
		{
			if (ft_wich_redir(cmds, i) == -1)
				ft_exit(data->token, data->cmds, data);
		}
		i++;
	}
	return (0);
}
