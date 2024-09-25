/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acancel <acancel@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 08:56:23 by acancel           #+#    #+#             */
/*   Updated: 2024/09/25 11:28:10 by acancel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	*ft_init_shell(char **env)
{
	t_data	*data;
	char	*buf;

	buf = NULL;
	rl_event_hook = &do_nothing;
	data = ft_calloc(1, sizeof(t_data));
	if (!data)
		exit(EXIT_FAILURE);
	data->last_error_status = 0;
	ft_get_env(data, env);
	if (!data->my_env)
		printf("no env\n");
	if (get_home(data) == -1)
		ft_exit(NULL, NULL, data);
	return (data);
}

int	ft_data_init(t_data *data)
{
	data->user = get_user(data);
	get_color(data, BLUE);
	data->line = readline(data->user);
	if (g_sigint != 0)
	{
		g_sigint = 0;
		data->last_error_status = 130;
		return (-1);
	}
	if (!data->line)
		ft_exit(NULL, NULL, data);
	if (ft_strncmp(data->line, "", 1) == 0)
		return (-1);
	if (data->line)
		add_history(data->line);
	if (prelexer_check(data) == 2)
	{
		data->last_error_status = 2;
		return (-1);
	}
	return (0);
}
