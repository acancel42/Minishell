/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acancel <acancel@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 08:56:45 by acancel           #+#    #+#             */
/*   Updated: 2024/09/25 08:56:46 by acancel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isexport(char *args, char **env)
{
	char	*variable;
	int		is_export;
	int		j;
	int		k;
	int		i;

	is_export = 0;
	j = 0;
	k = 0;
	i = 0;
	while (args[i] && args[i] != '=')
		i++;
	variable = ft_calloc(i + 1, sizeof(char));
	while (j < i)
	{
		variable[j] = args[j];
		j++;
	}
	while (env[k++] && env[k] != NULL)
	{
		if (ft_envcmp(env[k], variable) == 0)
			is_export = 1;
	}
	free(variable);
	return (is_export);
}

void	ft_replace_export(char ***nenv, char ***nexp, int i, t_data *data)
{
	if (ft_isexport(data->cmds->args[i], data->my_env) && \
				ft_isexport(data->cmds->args[i], data->export))
	{
		*nenv = tab_replace((data->my_env), data->cmds->args[i]);
		*nexp = tab_replace((data->export), data->cmds->args[i]);
	}
	else if (!ft_isexport(data->cmds->args[i], data->my_env) && \
			ft_isexport(data->cmds->args[i], data->export))
	{
		*nenv = tab_join((data->my_env), data->cmds->args[i]);
		*nexp = tab_replace((data->export), data->cmds->args[i]);
	}
	else
	{
		*nenv = tab_join((data->my_env), data->cmds->args[i]);
		*nexp = tab_join((data->export), data->cmds->args[i]);
	}
	if (!*nenv || !*nexp)
		ft_exit(data->token, data->cmds, data);
}

int	ft_print_export(char **args, t_data *data)
{
	int	i;

	i = 0;
	if (!args[1])
	{
		while (data->export[i] && data->export[i] != NULL)
		{
			printf("%s\n", data->export[i]);
			i++;
		}
		return (1);
	}
	return (0);
}

char	**tab_join(char **tab, char *str)
{
	int		i;
	char	**new_tab;

	i = 0;
	while (tab[i])
		i++;
	new_tab = malloc(sizeof(char *) * (i + 2));
	if (!new_tab)
		return (NULL);
	i = 0;
	while (tab[i])
	{
		new_tab[i] = ft_strdup(tab[i]);
		if (!new_tab[i])
			return (NULL);
		i++;
	}
	new_tab[i] = ft_strdup(str);
	if (!new_tab[i])
		return (NULL);
	new_tab[i + 1] = NULL;
	return (new_tab);
}

int	ft_envcmp(char *env, char *variable)
{
	char	*temp;
	int		res;

	res = 1;
	temp = ft_strjoin(variable, "=", 0);
	if (!temp)
		return (-1);
	if (ft_strncmp(env, temp, ft_strlen(temp)) == 0 || \
		ft_strncmp(env, variable, ft_strlen(variable) + 1) == 0)
		res = 0;
	free(temp);
	return (res);
}
