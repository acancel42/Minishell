/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_init_redir.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acancel <acancel@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 08:59:02 by acancel           #+#    #+#             */
/*   Updated: 2024/09/25 08:59:03 by acancel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_output_util(t_token **token, t_data *data, int j)
{
	t_token	*temp;

	if (j == 0)
	{
		temp = ft_toknew('>', T_REDIR_OUT);
		if (!temp)
			ft_exit(*token, NULL, data);
		ft_tokadd_back(token, temp);
	}
	else
	{
		temp = ft_toknew('+', T_APPEND_OUT);
		if (!temp)
			ft_exit(*token, NULL, data);
		ft_tokadd_back(token, temp);
	}
}

int	handle_output(char *src, t_token **token, t_data *data)
{
	int		j;
	int		i;

	i = 0;
	j = 0;
	if (src && src[i + 1] == '>')
	{
		j++;
		i++;
	}
	handle_output_util(token, data, j);
	data->rflag = 1;
	i++;
	return (i);
}

static void	handle_input_util(t_token **token, t_data *data, int j)
{
	t_token	*temp;

	if (j == 0)
	{
		temp = ft_toknew('<', T_REDIR_IN);
		if (!temp)
			ft_exit(*token, NULL, data);
		ft_tokadd_back(token, temp);
	}
	else
	{
		temp = ft_toknew('-', T_HEREDOC);
		if (!temp)
			ft_exit(*token, NULL, data);
		ft_tokadd_back(token, temp);
	}
}

int	handle_input(char *src, t_token **token, t_data *data)
{
	int		j;
	int		i;

	i = 0;
	j = 0;
	if (src && src[i + 1] == '<')
	{
		j++;
		i++;
	}
	handle_input_util(token, data, j);
	data->rflag = 1;
	i++;
	return (i);
}
