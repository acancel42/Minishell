/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acancel <acancel@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 09:18:24 by acancel           #+#    #+#             */
/*   Updated: 2024/09/25 09:35:06 by acancel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_assign_value_util(char **name, char **dst, t_data *dt)
{
	if (ft_isdigit((*dst)[dt->exp.i]))
	{
		*name = ft_strndup((*dst) + dt->exp.s + 1, 1);
		if (!(*name))
			return (-1);
		dt->exp.i++;
		dt->exp.e++;
	}
	else if ((*dst)[dt->exp.i] == '$')
	{
		*name = ft_strndup((*dst) + dt->exp.s + 1, 1);
		if (!(*name))
			return (-1);
		dt->exp.i++;
		dt->exp.e++;
	}
	else
	{
		while (ft_isalnum((*dst)[dt->exp.i++]) && (*dst)[dt->exp.i - 1] != '$')
			dt->exp.e++;
		*name = ft_strndup((*dst) + (dt->exp.s + 1), dt->exp.e - dt->exp.s - 1);
		if (!(*name))
			return (-1);
	}
	return (0);
}

int	ft_assign_value(char **name, char **value, char **dest, t_data *data)
{
	if ((*dest)[data->exp.i] == '?')
	{
		*name = NULL;
		*value = ft_itoa(data->last_error_status);
		if (!(*value))
			return (-1);
		data->exp.e++;
		data->exp.is_itoa = true;
	}
	else
	{
		if (ft_assign_value_util(name, dest, data) == -1)
			return (-1);
		*value = find_env_var(*name, data->my_env);
	}
	return (0);
}
