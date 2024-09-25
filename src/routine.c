/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acancel <acancel@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 08:58:22 by acancel           #+#    #+#             */
/*   Updated: 2024/09/25 08:58:23 by acancel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_exec(t_commands *cmds, t_token *token, t_data *data)
{
	if (!cmds->name && !cmds->redirections[0])
	{
		data->last_error_status = 2;
		printf("syntax error\n");
		free_data(data, &cmds, &token);
		return (-1);
	}
	if (cmds->name && ft_is_built_in(cmds) && data->index_max == 0 \
		&& cmds->redirections[0] == NULL)
	{
		if (ft_exec_built_in(token, cmds, data) == 1)
			data->last_error_status = 0;
		free_data(data, &cmds, &token);
		return (-1);
	}
	data->pflag = 0;
	if (ft_pathfinder(data) == 0)
	{
		free_data(data, &cmds, &token);
		return (-1);
	}
	if (cmds->next != NULL)
		data->pflag = 1;
	exec_cmds(data, cmds);
	return (0);
}

void	ft_routine(t_token *token, t_commands *cmds, t_data *data)
{
	ft_is_env_op(data);
	token = NULL;
	cmds = NULL;
	if (ft_data_init(data, &cmds) == -1)
	{
		free_data(data, &cmds, &token);
		return ;
	}
	if (lexer_init(&token, data) == -1)
	{
		free_data(data, &cmds, &token);
		return ;
	}
	init_cmd(&cmds, token, data);
	if (fill_cmd(&cmds, token, data) == 2)
	{
		data->last_error_status = 2;
		free_data(data, &cmds, &token);
		return ;
	}
	data->cmds = cmds;
	data->token = token;
	if (ft_exec(cmds, token, data) == -1)
		return ;
	free_data(data, &cmds, &token);
}
