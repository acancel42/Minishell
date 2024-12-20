/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built-in_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acancel <acancel@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 08:56:18 by acancel           #+#    #+#             */
/*   Updated: 2024/09/25 08:56:19 by acancel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_wich_cd(t_data *data, t_commands *cmds)
{
	char	*temp;

	temp = NULL;
	if (cmds->args[1] == NULL || \
		ft_strncmp(cmds->args[1], "~", 2) == 0)
	{
		temp = find_env_var("HOME", data->my_env);
		if (temp == NULL)
			printf("cd: HOME not set\n");
		else
			ft_cd(temp, data, cmds);
	}
	else
	{
		temp = ft_substr(data->line, 3, ft_strlen(data->line) - 3);
		if (temp == NULL)
			ft_exit(data->token, cmds, data);
		ft_cd(temp, data, cmds);
		free(temp);
	}
}

int	ft_exec_cd(t_data *data)
{
	ft_wich_cd(data, data->cmds);
	return (1);
}

int	ft_exec_built_in(t_token *token, t_commands *cmds, t_data *data)
{
	if (!cmds->name)
		return (0);
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
		return (ft_pwd(data), 1);
	if (ft_strncmp(cmds->name, "exit", 5) == 0)
		ft_exit(token, cmds, data);
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
