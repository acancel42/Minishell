/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acancel <acancel@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 08:57:13 by acancel           #+#    #+#             */
/*   Updated: 2024/09/25 08:57:14 by acancel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	fill_empty_env(t_data *data, char *buf)
{
	char	*temp;

	temp = ft_strjoin("PWD=", buf, 0);
	free(buf);
	if (!temp)
		ft_exit(NULL, NULL, data);
	data->my_env[0] = ft_strdup(temp);
	free(temp);
	if (!data->my_env[0])
		ft_exit(NULL, NULL, data);
	data->my_env[1] = ft_strdup("LOGNAME=?");
	if (!data->my_env[1])
		ft_exit(NULL, NULL, data);
	data->my_env[2] = ft_strdup("SESSION_MANAGER=?");
	if (!data->my_env[2])
		ft_exit(NULL, NULL, data);
	data->my_env[3] = ft_strdup("PATH=/usr/bin/");
	if (!data->my_env[3])
		ft_exit(NULL, NULL, data);
}

static void	ft_empty_env(t_data *data)
{
	size_t	i;
	char	*buf;

	buf = NULL;
	i = 0;
	data->my_env = ft_calloc(5, sizeof(char *));
	data->export = ft_calloc(5, sizeof(char *));
	if (!data->my_env || !data->export)
	{
		if (data->my_env)
			ft_free_tab(data->my_env);
		exit(EXIT_FAILURE);
	}
	buf = getcwd(NULL, 0);
	if (!buf)
		ft_exit(NULL, NULL, data);
	fill_empty_env(data, buf);
}

void	ft_get_env(t_data *data, char **env)
{
	if (!env[0])
	{
		ft_empty_env(data);
		data->export = tab_dup(data->my_env);
		if (!data->export)
			ft_free_tab(data->export);
	}
	else
	{
		if (data->my_env)
			ft_free_tab(data->my_env);
		data->my_env = tab_dup(env);
		if (!data->my_env)
			ft_free_tab(data->my_env);
		if (data->export)
			ft_free_tab(data->export);
		data->export = tab_dup(env);
		if (!data->export)
			ft_free_tab(data->export);
	}
}

void	ft_is_env_op(t_data *data)
{
	if (!find_env_var("PWD", data->my_env))
		ft_pwd_missing(data);
	if (!find_env_var("LOGNAME", data->my_env))
		ft_variable_missing(data, "LOGNAME=?", 0);
	if (!find_env_var("SESSION_MANAGER", data->my_env))
		ft_variable_missing(data, "SESSION_MANAGER=?", 0);
	if (!find_env_var("PATH", data->my_env))
		ft_variable_missing(data, "PATH=?", 0);
	if (!find_env_var("LOGNAME", data->export))
		ft_variable_missing(data, "LOGNAME=?", 1);
	if (!find_env_var("SESSION_MANAGER", data->export))
		ft_variable_missing(data, "SESSION_MANAGER=?", 1);
	if (!find_env_var("PATH", data->export))
		ft_variable_missing(data, "PATH=?", 1);
}
