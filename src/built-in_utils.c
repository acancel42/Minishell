#include "minishell.h"

static void	ft_witch_cd(t_data *data, t_commands *cmds)
{
	if (cmds->args[1] == NULL || \
		ft_strncmp(cmds->args[1], "~", 1) == 0)
	{
		ft_cd(data->home, data);
		free_data(data);
	}
	else
	{
		ft_cd(ft_substr(data->line, 3, ft_strlen(data->line) - 3), data);
		free_data(data);
	}
}

int	ft_exec_cd(t_data *data)
{
	if (data->is_home == false)
	{
		printf("cd: HOME not set\n");
		return (1);
	}
	ft_witch_cd(data, data->cmds);
	return (1);
}

int	ft_exec_built_in(t_data *data, t_commands *cmds)
{
	if (ft_strncmp(cmds->name, "cd", 3) == 0)
		return (ft_exec_cd(data));
	if (ft_strncmp(cmds->name, "echo", 5) == 0)
		return (ft_echo(cmds), 1);
	if (ft_strncmp(cmds->name, "export", 7) == 0)
		return (ft_export(cmds->args, data), 1);
	if (ft_strncmp(cmds->name, "unset", 6) == 0)
		return (ft_unset(cmds->args, data), 1);
	if (ft_strncmp(cmds->name, "env", 4) == 0)
		return (ft_env(data), 1);
	if (ft_strncmp(cmds->name, "pwd", 4) == 0)
		return (ft_pwd(), 1);
	if (ft_strncmp(cmds->name, "exit", 5) == 0)
		exit_minishell(&data->token, &data->cmds, data);
	return (0);
}

int	ft_is_built_in(t_commands *cmds)
{
	if (!ft_strncmp(cmds->name, "cd", 3) || \
		!ft_strncmp(cmds->name, "exit", 5) || \
		!ft_strncmp(cmds->name, "echo", 5) || \
		!ft_strncmp(cmds->name, "export", 7) || \
		!ft_strncmp(cmds->name, "unset", 6) || \
		!ft_strncmp(cmds->name, "pwd", 4) || \
		!ft_strncmp(cmds->name, "env", 4))
		return (1);
	return (0);
}

int	get_home(t_data *data)
{
	int		i;

	data->is_home = false;
	i = 0;
	while (data->my_env[i])
	{
		if (ft_strncmp(data->my_env[i], "HOME=", 5) == 0)
		{
			data->is_home = true;
			break ;
		}
		i++;
	}
	if (data->is_home == true)
	{
		data->home = ft_substr(data->my_env[i], 5, 6 + 8);
		if (data->home == NULL)
			return (-1);
	}
	return (0);
}
