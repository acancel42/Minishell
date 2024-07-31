#include "minishell.h"

void	build_path(t_data *data, char *s1, \
					char *s2)
{
	size_t		len_s1;
	size_t		len_s2;

	if (!s1 || !s2)
	{
		data->cmds->path = NULL;
		return ;
	}
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	data->cmds->path = ft_calloc(len_s1 + 1 + len_s2 + 1, sizeof(char));
	if (data->cmds->path == NULL)
	{
		ft_putstr_fd("malloc failed\n", 2);
		ft_exit(data->token, data->cmds, data);
	}
	ft_memcpy(data->cmds->path, s1, len_s1);
	ft_memcpy(data->cmds->path + len_s1, "/", 1);
	ft_memcpy(data->cmds->path + len_s1 + 1, s2, len_s2);
	return ;
}

static void	try_acces(t_data *data, char **all_paths, int i)
{
	while (data->cmds->path != NULL && access(data->cmds->path, F_OK))
	{
		free(data->cmds->path);
		build_path(data, all_paths[i++], data->cmds->name);
	}
}

int	cmd_path(t_data *data)
{
	char	**all_paths;
	int		i;

	i = 0;
	if (ft_is_built_in(data->cmds) == 1)
		return (2);
	while (ft_strncmp(data->my_env[i], "PATH=", 5) != 0)
		i++;
	data->cmds->path = data->my_env[i];
	all_paths = ft_split(data->cmds->path + 5, ':');
	if (all_paths == NULL)
	{
		ft_putstr_fd("malloc failed\n", 2);
		ft_exit(data->token, data->cmds, data);
	}
	i = 0;
	build_path(data, all_paths[i], data->cmds->name);
	try_acces(data, all_paths, i);
	ft_free_tab(all_paths);
	if (data->cmds->path == NULL || ft_strncmp(data->cmds->name, "", 1) == 0)
	{
		printf("command '%s' not found\n", data->cmds->name);
		return (0);
	}
	return (1);
}

int	ft_pathfinder(t_data *data)
{
	int			btflag;

	btflag = 0;
	while (data->cmds)
	{
		data->cmds->valid_path = access(data->cmds->args[0], F_OK | X_OK);
		if (data->cmds->valid_path == -1 && ft_strchr_b(data->cmds->name, '/'))
		{
			btflag = cmd_path(data);
			if (btflag == 0)
				return (0);
		}
		else
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
				return (0);
			}
			if (!data->cmds->path)
				return (-1);
		}
		if (data->cmds->path || btflag == 2)
			data->cmds = data->cmds->next;
	}
	return (1);
}
