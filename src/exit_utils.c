/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acancel <acancel@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 08:56:38 by acancel           #+#    #+#             */
/*   Updated: 2024/09/25 22:54:24 by acancel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_minishell(t_token **token, t_commands **cmds, t_data *data)
{
	if (cmds)
		if (*cmds)
			ft_cmdsclear(cmds);
	if (token)
		if (*token)
			ft_tokenclear(token);
	if (data)
	{
		if (data->line)
			free(data->line);
		if (data->my_env)
			ft_free_tab(data->my_env);
		if (data->user)
			free(data->user);
		if (data->home)
			free(data->home);
		if (data->export)
			ft_free_tab(data->export);
		free(data);
	}
	clear_history();
	printf(RED"%s\n"RESET, "exit");
	return ;
}

void	ft_exec_error(t_token *token, t_commands *cmds, t_data *data, int flag)
{
	if (flag == 0)
		perror("pipe");
	else if (flag == 1)
		perror("fork");
	else if (flag == 2)
		perror("dup2");
	data->last_error_status = 1;
	ft_exit(token, cmds, data);
}

void	ft_exit(t_token *token, t_commands *cmds, t_data *data)
{
	int	exit_stat;

	exit_stat = 0;
	if (cmds && cmds->name && ft_strncmp(cmds->name, "exit", 5) == 0 \
			&& cmds->args[1])
		exit_stat = ft_atoi(cmds->args[1]);
	else
		exit_stat = data->last_error_status;
	if (cmds && token)
		exit_minishell(&token, &cmds, data);
	else if (token)
		exit_minishell(&token, NULL, data);
	else if (cmds)
		exit_minishell(NULL, &cmds, data);
	else
		exit_minishell(NULL, NULL, data);
	exit(exit_stat);
}
