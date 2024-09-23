#include "minishell.h"

void	ft_free_tab(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
}

void	free_data(t_data *data, t_commands **cmds)
{
	if (*cmds)
		ft_cmdsclear(cmds);
	if (data->token)
		ft_tokenclear(&data->token);
	if (data->line)
		free(data->line);
	if (data->user)
		free(data->user);
	data->index_max = 0;
	data->pflag = 0;
}

void	free_monitoring(char *host, char *username, char *pwd)
{
	if (pwd)
		free(pwd);
	if (host)
		free(host);
	if (username)
		free(username);
	return ;
}

void	free_child(t_data *data, t_commands **cmds)
{
	int	exit_status;

	free_data(data, cmds);
	if (data->home)
		free(data->home);
	if (data->export)
		ft_free_tab(data->export);
	if (data->my_env)
		ft_free_tab(data->my_env);
	exit_status = data->last_error_status;
	free(data);
	exit(exit_status);
}

void	ft_close(int fd, t_data *data, t_commands *cmds, int flag)
{
	if (fd > 1)
	{
		if (close(fd) == -1)
		{
			printf("close file descriptor %d failed\n", fd);
			perror("Error fd :");
			ft_exit(data->token, cmds, data);
		}
		if (flag == 0)	
			fd = 0;
		if (flag == 1)
			fd = 1;
	}
}

void	close_files(t_commands *cmds, t_data *data)
{
	if (cmds->outfile_fd != 1 && cmds->outfile_fd != -1)
		ft_close(cmds->outfile_fd, data, cmds, 1);
	if (cmds->infile_fd != 0 && cmds->infile_fd != -1)
		ft_close(cmds->infile_fd, data, cmds, 0);
}
