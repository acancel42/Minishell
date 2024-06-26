#include "minishell.h"

int	ft_redir_output(t_commands *cmds)
{
	cmds->outfile_fd = open(cmds->redirections->name, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (cmds->outfile_fd == -1)
		perror(cmds->redirections->name);
	if (dup2(cmds->outfile_fd, STDOUT_FILENO) == -1)
		perror("dup out redir");
	return (0);
}

int	ft_redir_input(t_commands *cmds)
{
	cmds->infile_fd = open(cmds->redirections->name, O_RDONLY);
	if (cmds->infile_fd == -1)
		perror(cmds->redirections->name);
	if (dup2(cmds->infile_fd, STDIN_FILENO) == -1)
		perror("dup in redir");
	return (0);
}

int	ft_wich_redir(t_commands *cmds)
{
	while (cmds->redirections)
	{

		if (!ft_strncmp(cmds->redirections->name, ">", 1))
		{
			cmds->redirections->name = ft_strdup(cmds->redirections->name + 1);
			ft_redir_output(cmds);
		}
		else if (!ft_strncmp(cmds->redirections->name, "<", 1))
		{
			cmds->redirections->name = ft_strdup(cmds->redirections->name + 1);
			ft_redir_input(cmds);
		}
		cmds->redirections = cmds->redirections->next;
	}
	return (0);
}
