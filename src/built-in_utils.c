#include "minishell.h"

static void	ft_witch_cd(t_data *data, t_commands *cmds)
{
	if (cmds->args[1] == NULL || \
		ft_strncmp(cmds->args[1], "~", 1) == 0)
	{
		ft_cd(data->home, data);
		ft_echo(cmds);
		free_data(data);
	}
	else
	{
		ft_cd(ft_substr(data->line, 3, ft_strlen(data->line) - 3), data);
		ft_echo(cmds);
		free_data(data);
	}
}

int	ft_is_built_in(t_data *data, t_commands *cmds)
{
	if (ft_strncmp(cmds->name, "cd", 3) == 0)
	{
		ft_witch_cd(data, cmds);
		return (1);
	}
	if (ft_strncmp(cmds->name, "echo", 5) == 0)
	{
		ft_echo(cmds);
		return (1);
	}
	if (ft_strncmp(cmds->name, "export", 7) == 0)
	{
		ft_export(cmds->args, &data->my_env);
		return (1);
	}
	if (ft_strncmp(cmds->name, "exit", 5) == 0)
		exit_minishell(&data->token, &data->cmds, data);
	return (0);
}
