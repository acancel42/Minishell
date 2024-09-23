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
		printf("%s: command not found\n", data->cmds->name);
		return (0);
	}
	return (1);
}

int	ft_pathfinder(t_data *data)
{
	int			exit_ret;

	exit_ret = 0;
	while (data->cmds)
	{
		if (!data->cmds->name)
		{
			data->cmds = data->cmds->next;
			continue ;
		}
		data->cmds->valid_path = access(data->cmds->args[0], F_OK | X_OK);
		if (ft_wrong_path(data, &exit_ret) == 0)
			return (0);
		if (data->cmds->path || exit_ret == 2)
			data->cmds = data->cmds->next;
	}
	return (1);
}
