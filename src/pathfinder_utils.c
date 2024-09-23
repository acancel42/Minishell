#include "minishell.h"

static int	ft_given_path(t_data *data, int exit_ret)
{
	data->cmds->path = ft_strdup(data->cmds->args[0]);
	if (!data->cmds->path)
		ft_exit(data->token, data->cmds, data);
	if (access(data->cmds->path, F_OK | X_OK) == -1)
	{
		perror(data->cmds->path);
		data->last_error_status = 127;
		if (errno == 13)
			data->last_error_status--;
		exit_ret = 1;
	}
	return (exit_ret);
}

int	ft_wrong_path(t_data *data, int *exit_ret)
{
	if (data->cmds->valid_path == -1 && !ft_strchr_b(data->cmds->name, '/'))
	{
		*exit_ret = cmd_path(data);
		if (*exit_ret == 0)
		{
			data->last_error_status = 127;
			return (0);
		}
	}
	else
	{
		*exit_ret = ft_given_path(data, *exit_ret);
		if (*exit_ret == 1)
			return (0);
	}
	return (1);
}

void	try_acces(t_data *data, char **all_paths, int i)
{
	while (data->cmds->path != NULL && access(data->cmds->path, F_OK))
	{
		free(data->cmds->path);
		build_path(data, all_paths[i++], data->cmds->name);
	}
}
