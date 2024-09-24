#include "minishell.h"

int	is_flagn(char *str)
{
	int	i;

	i = 0;
	if (str[i] != '-')
		return (0);
	i++;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	ft_echo(t_commands *cmds)
{
	int	i;
	int	flag;

	flag = 0;
	i = 1;
	while (cmds->args[i] && cmds->args[i][0] == 0)
		i++;
	while (cmds->args[i] && is_flagn(cmds->args[i]))
	{
		i++;
		flag++;
	}
	while (cmds->args[i])
	{
		printf("%s", cmds->args[i]);
		if (cmds->args[i + 1] && cmds->args[i + 1][0] != 0)
			printf(" ");
		i++;
	}
	if (!flag)
		printf("\n");
	return (0);
}

int	ft_env(t_data *data)
{
	int	i;

	i = -1;
	if (!data->my_env)
		return (-2);
	while (data->my_env[++i])
		printf("%s\n", data->my_env[i]);
	return (0);
}
