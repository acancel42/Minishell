/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acancel <acancel@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 08:56:51 by acancel           #+#    #+#             */
/*   Updated: 2024/09/25 08:56:52 by acancel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_arg(char *args)
{
	int	i;

	i = -1;
	if (args[0] != '_' && !ft_isalpha(args[0]))
		return (1);
	while (args[++i])
		if (ft_isoperator(args[i]))
			return (1);
	return (0);
}

void	ft_existant_export(t_data *data, int *i, \
							char **new_env, char **new_export)
{
	ft_replace_export(&new_env, &new_export, *i, data);
	ft_free_tab(data->my_env);
	data->my_env = tab_dup(new_env);
	if (!data->my_env)
	{
		ft_free_tab(new_env);
		ft_free_tab(new_export);
		ft_exit(data->token, data->cmds, data);
	}
	ft_free_tab(data->export);
	data->export = tab_dup(new_export);
	ft_free_tab(new_env);
	ft_free_tab(new_export);
	if (!data->export)
		ft_exit(data->token, data->cmds, data);
}

int	ft_new_export(t_data *data, int *i, char **args, char **new_export)
{
	if (ft_isexport(args[*i], data->export))
	{
		(*i)++;
		return (0);
	}
	new_export = tab_join((data->export), args[*i]);
	if (!new_export)
		ft_exit(data->token, data->cmds, data);
	ft_free_tab(data->export);
	data->export = tab_dup(new_export);
	ft_free_tab(new_export);
	if (!data->export)
		ft_exit(data->token, data->cmds, data);
	return (1);
}

void	ft_export_loop(char **args, t_data *data, int *i)
{
	char	**new_env;
	char	**new_export;

	new_env = NULL;
	new_export = NULL;
	if (check_arg(args[*i]))
	{
		write(1, "not a valid identifier\n", 24);
		data->last_error_status = 1;
		(*i)++;
		return ;
	}
	if (ft_strchr(args[*i], '='))
		ft_existant_export(data, i, new_env, new_export);
	else
	{
		if (ft_new_export(data, i, args, new_export) == 0)
			return ;
	}
	(*i)++;
}

int	ft_export(char **args, t_data *data)
{
	int		i;

	i = 1;
	if (ft_print_export(args, data) == 1)
		return (0);
	while (args[i])
		ft_export_loop(args, data, &i);
	return (0);
}
