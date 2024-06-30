#include "minishell.h"

static void	ft_witch_cd(t_data *data)
{
	if (data->cmds->args[1] == NULL || \
		ft_strncmp(data->cmds->args[1], "~", 1) == 0)
	{
		ft_cd(data->home, data);
		ft_echo(data);
		free_data(data);
	}
	else
	{
		ft_cd(ft_substr(data->line, 3, ft_strlen(data->line) - 3), data);
		ft_echo(data);
		free_data(data);
	}
}

int	ft_is_built_in(t_data *data)
{
	if (ft_strncmp(data->cmds->name, "cd", 3) == 0)
	{
		ft_witch_cd(data);
		return (1);
	}
	if (ft_strncmp(data->cmds->name, "echo", 5) == 0)
	{
		ft_echo(data);
		free_data(data);
		return (1);
	}
	if (ft_strncmp(data->cmds->name, "export", 7) == 0)
	{
		ft_export(data->cmds->args, &data->my_env);
		free_data(data);
		return (1);
	}
	if (ft_strncmp(data->cmds->name, "exit", 5) == 0)
		exit_minishell(&data->token, &data->cmds, data);
	return (0);
}
