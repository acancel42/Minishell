#include "minishell.h"

int	ft_redir_output(t_commands *cmds, int i)
{
	cmds->outfile_fd = open(cmds->redirections[i], \
			O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (cmds->outfile_fd == -1)
		perror(cmds->redirections[i]);
	return (0);
}

int	ft_redir_input(t_commands *cmds, int i)
{
	cmds->infile_fd = open(cmds->redirections[i], O_RDONLY);
	if (cmds->infile_fd == -1)
		perror(cmds->redirections[i]);
	return (0);
}

int	ft_wich_redir(t_commands *cmds, int i)
{
	char	*temp;

	if (cmds->redirections[i][0] == '>')
	{
		cmds->redirections[i] = \
			ft_strdup(cmds->redirections[i] + 1);
		ft_redir_output(cmds, i);
		temp = ft_strdup(">");
		cmds->redirections[i] = \
			ft_strjoin(temp, cmds->redirections[i], 1);
	}
	else if (cmds->redirections[i][0] == '<')
	{
		cmds->redirections[i] = \
			ft_strdup(cmds->redirections[i] + 1);
		ft_redir_input(cmds, i);
		temp = ft_strdup("<");
		cmds->redirections[i] = \
			ft_strjoin(temp, cmds->redirections[i], 1);
	}
	return (0);
}

void	ft_redir_or_append(t_commands *cmds)
{
	int		i;
	char	*temp;

	i = 0;
	while (cmds->redirections[i])
	{
		printf("------op : %c\n", cmds->redirections[i][0]);
		if (cmds->redirections[i][0] == '+')
		{
			cmds->redirections[i] = \
			ft_strdup(cmds->redirections[i] + 1);
			cmds->outfile_fd = open(cmds->redirections[i], \
			O_WRONLY | O_APPEND | O_CREAT, 0644);
			if (cmds->outfile_fd == -1)
				perror(cmds->redirections[i]);
			temp = ft_strdup("+");
			cmds->redirections[i] = \
			ft_strjoin(temp, cmds->redirections[i], 1);
		}
		else if (cmds->redirections[i][0] == '<' || \
					cmds->redirections[i][0] == '>')
			ft_wich_redir(cmds, i);
		i++;
	}
}
