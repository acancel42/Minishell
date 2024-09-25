/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acancel <acancel@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 08:58:31 by acancel           #+#    #+#             */
/*   Updated: 2024/09/25 08:58:32 by acancel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_mult_op(char *line, int *i, int *multiple_op, int *is_word)
{
	while (ft_iswspace(line[*i]))
		(*i)++;
	if (ft_isalnum(line[*i]) || line[*i] == '_')
	{
		(*is_word)++;
		return (1);
	}
	if (line[*i] == '<')
	{
		(*multiple_op)++;
		(*i)++;
	}
	else if (line[*i] == '>')
	{
		(*multiple_op)++;
		(*i)++;
	}
	else if (line[*i] == '|')
	{
		(*multiple_op)++;
		(*i)++;
	}
	else if (line[*i])
		(*i)++;
	return (0);
}

int	is_redir_or_pipe(t_data *data, int i)
{
	if (data->line[i] == '>')
	{
		if (oredir_handle(data->line, &i) == 2)
			return (2);
	}
	else if (data->line[i] == '<')
	{
		if (iredir_handle(data->line, &i) == 2)
			return (2);
	}
	else if (data->line[i] == '|')
	{
		if (pipe_handle(data->line, &i) == 2)
			return (2);
	}
	return (0);
}
