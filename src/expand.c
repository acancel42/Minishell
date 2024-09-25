/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acancel <acancel@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 09:14:35 by acancel           #+#    #+#             */
/*   Updated: 2024/09/25 09:35:11 by acancel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_replace_value(char **dest, char **value, \
								char **name, t_data *data)
{
	char	*tmp;

	tmp = malloc(ft_strlen((*dest)) - ft_strlen(*name) + \
				ft_strlen(*value) + 1);
	if (!tmp)
	{
		free(*name);
		return (-1);
	}
	ft_strncpy(tmp, (*dest), data->exp.s);
	ft_strcpy(tmp + data->exp.s, *value);
	data->exp.i = data->exp.s + ft_strlen(*value);
	ft_strcpy(tmp + data->exp.s + ft_strlen(*value), (*dest) + data->exp.e);
	free((*dest));
	(*dest) = ft_strdup(tmp);
	free(tmp);
	free(*name);
	if (!(*dest))
		return (-1);
	return (0);
}

static int	ft_replace_null_value(char **dest, char **value, \
									char **name, t_data *data)
{
	char	*tmp;

	data->exp.i = data->exp.s;
	tmp = malloc(ft_strlen((*dest)) - ft_strlen(*name) + \
			ft_strlen(*value) + 1);
	if (!tmp)
	{
		free(*name);
		return (-1);
	}
	ft_strncpy(tmp, (*dest), data->exp.s);
	ft_strcpy(tmp + data->exp.s, (*dest) + data->exp.e);
	free((*dest));
	(*dest) = ft_strdup(tmp);
	free(tmp);
	free(*name);
	if (!(*dest))
		return (-1);
	if (!(*dest)[0])
		return (2);
	return (0);
}

int	ft_wich_value(char **dest, char **value, char **name, t_data *data)
{
	if (*value)
		return (ft_replace_value(dest, value, name, data));
	else
		return (ft_replace_null_value(dest, value, name, data));
}

int	ft_expand_loop(char **dest, char **name, char **value, t_data *data)
{
	int	ret;

	if ((*dest)[data->exp.i] == '$')
	{
		data->exp.s = data->exp.i;
		data->exp.e = data->exp.i + 1;
		data->exp.i++;
		if (ft_assign_value(name, value, dest, data) == -1)
			return (-1);
		ret = ft_wich_value(dest, value, name, data);
		if (ret == 2)
			return (2);
		if (ret == -1)
			return (-1);
		if (data->exp.is_itoa == true)
		{
			data->exp.is_itoa = false;
			free(*value);
		}
	}
	else
		data->exp.i++;
	return (0);
}

int	expand_variables(char **dest, char *src, t_data *data)
{
	char		*name;
	char		*value;
	int			ret;

	(*dest) = ft_strdup(src);
	if (!(*dest))
		return (-1);
	value = NULL;
	name = NULL;
	data->exp.i = 0;
	data->exp.e = 0;
	data->exp.is_itoa = false;
	if (ft_strncmp((*dest), "$", 1) == 0 && ft_strlen((*dest)) == 1)
		return (data->exp.i);
	while ((*dest) && (*dest)[data->exp.i])
	{
		ret = ft_expand_loop(dest, &name, &value, data);
		if (ret == -1)
			return (-1);
		else if (ret == 2)
			break ;
	}
	return (data->exp.i);
}
