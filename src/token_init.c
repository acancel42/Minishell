/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acancel <acancel@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 08:59:20 by acancel           #+#    #+#             */
/*   Updated: 2024/09/25 08:59:21 by acancel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_unquoted(char *src, t_token **token, t_data *data, int *i)
{
	if (src[*i] == '>')
		*i += handle_output(src + *i, token, data);
	else if (src[*i] == '<')
		*i += handle_input(src + *i, token, data);
	else if (src[*i] == '|')
		*i += handle_pipe(token, data);
	else
		*i += handle_else(src + *i, token, data);
}

int	token_init(char *src, int i, t_token **token, t_data *data)
{
	int	j;

	while (ft_iswspace(src[i]))
		i++;
	if (!src[i])
		return (i);
	if (src[i] == '"')
	{
		j = handle_double_quote(src + i, token, data);
		if (j == -1)
			return (j);
		else
			i += j;
	}
	else if (src[i] == '\'')
	{
		j = handle_single_quote(src + i, token, data);
		if (j == -1)
			return (j);
		else
			i += j;
	}
	else
		handle_unquoted(src, token, data, &i);
	return (i);
}
