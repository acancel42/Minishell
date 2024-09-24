#include "minishell.h"

static int	ft_redir_output(t_data *data, t_commands *cmds, int i)
{
	ft_close(cmds->outfile_fd, data, cmds, 1);
	cmds->outfile_fd = open(cmds->redirections[i], \
			O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (cmds->outfile_fd == -1)
	{
		perror(cmds->redirections[i]);
		return (-1);
	}
	return (0);
}

static int	ft_redir_input(t_commands *cmds, t_data *data, int i)
{
	ft_close(cmds->infile_fd, data, cmds, 0);
	cmds->infile_fd = open(cmds->redirections[i], O_RDONLY);
	if (cmds->infile_fd == -1)
	{
		perror(cmds->redirections[i]);
		return (-1);
	}
	return (0);
}

int	ft_wich_redir(t_data *data, t_commands *cmds, int i)
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
		if (ft_redir_output(data, cmds, i) == -1)
			return (2);
	}
	else if (cmds->name)
	{
		if (ft_redir_input(cmds, data, i) == -1)
			return (2);
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
	ft_close(cmds->outfile_fd, data, cmds, 1);
	cmds->outfile_fd = open(temp, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (cmds->outfile_fd == -1)
	{
		perror(temp);
		free(temp);
		return (-1);
	}
	if (temp)
		free(temp);
	if (!cmds->name)
		ft_close(cmds->outfile_fd, data, cmds, 1);
	return (0);
}

int	ft_redir_or_append(t_data *data, t_commands *cmds)
{
	int		i;
	int		j;

	j = 0;
	i = -1;
	while (cmds->redirections[++i])
	{
		if (cmds->redirections[i][0] == '+')
			ft_append(data, cmds, cmds->redirections[i], 1);
		else if (cmds->redirections[i][0] == '-')
		{
			//printf("minishell: %s: ambiguous redirect\n", cmds->redirections[i]);
			//ft_close(cmds->infile_fd, data, cmds, 0);
			if (handle_heredoc(data, cmds, cmds->redirections[i] + 1) == 2)
				return (-1);
		}
		else if (cmds->redirections[i][0] == '<' || \
					cmds->redirections[i][0] == '>')
		{
			j = ft_wich_redir(data, cmds, i);
			if (j == -1)
				ft_exit(data->token, data->cmds, data);
			else if (j == 2)
				return (-1);
		}
	}
	return (0);
}
