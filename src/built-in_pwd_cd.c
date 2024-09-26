/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built-in_pwd_cd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acancel <acancel@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 08:56:13 by acancel           #+#    #+#             */
/*   Updated: 2024/09/26 02:41:17 by acancel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_pwd(char **pwd)
{
	*pwd = getcwd(NULL, 0);
	if (!*pwd)
		return (-2);
	return (0);
}

int	ft_pwd(t_data *data)
{
	printf("%s\n", find_env_var("PWD", data->my_env));
	return (0);
}

static int	ft_get_oldpwd(t_data *data)
{

	if (find_env_var("OLDPWD", data->my_env))
		tab_replace(data->my_env, find_env_var("PWD", data->my_env));
	else
		tab_join(data->my_env, find_env_var("PWD", data->my_env));
	return (0);
}

int	ft_cd(char *path, t_data *data, t_commands *cmds)
{
	int		i;
	char	*pwd;

	if (ft_get_oldpwd(data) == -1)
		return (-1);
	if (chdir(path) == -1)
	{
		printf("cd: %s: No such file or directory\n", path);
		data->last_error_status = 1;
		return (-2);
	}
	i = 0;
	while (ft_strncmp(data->my_env[i], "PWD=", 4))
		i++;
	if (get_pwd(&pwd) == -2)
	{
		data->last_error_status = 1;
		printf("getcwd: cannot access parent directories\n");
	}
	free(data->my_env[i]);
	data->my_env[i] = ft_strjoin("PWD=", pwd, 0);
	free(pwd);
	if (!data->my_env[i])
		ft_exit(data->token, cmds, data);
	return (0);
}
