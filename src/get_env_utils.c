/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acancel <acancel@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 08:57:03 by acancel           #+#    #+#             */
/*   Updated: 2024/09/25 08:57:04 by acancel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_variable_missing(t_data *data, char *variable, int flag)
{
	char	**new_env;

	if (flag == 0)
	{
		new_env = tab_join(data->my_env, variable);
		if (!new_env)
			ft_exit(NULL, NULL, data);
		ft_free_tab(data->my_env);
		data->my_env = tab_dup(new_env);
		ft_free_tab(new_env);
		if (!data->my_env)
			ft_exit(NULL, NULL, data);
	}
	else
	{
		new_env = tab_join(data->export, variable);
		if (!new_env)
			ft_exit(NULL, NULL, data);
		ft_free_tab(data->export);
		data->export = tab_dup(new_env);
		ft_free_tab(new_env);
		if (!data->export)
			ft_exit(NULL, NULL, data);
	}
}

void	ft_pwd_missing(t_data *data)
{
	char	*buf;
	char	*temp;

	buf = NULL;
	buf = getcwd(NULL, 0);
	if (!buf)
		ft_exit(NULL, NULL, data);
	temp = ft_strjoin("PWD=", buf, 0);
	free(buf);
	if (!temp)
		ft_exit(NULL, NULL, data);
	ft_variable_missing(data, temp, 0);
	ft_variable_missing(data, temp, 1);
	free(temp);
}
