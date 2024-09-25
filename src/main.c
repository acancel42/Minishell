/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acancel <acancel@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 08:57:47 by acancel           #+#    #+#             */
/*   Updated: 2024/09/25 08:57:48 by acancel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_sigint = 0;

void	ft_handler(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		g_sigint = 1;
	}
	return ;
}

int	do_nothing(void)
{
	return (42);
}

int	main(int argc, char **argv, char **env)
{
	t_token				*token;
	t_commands			*cmds;
	t_data				*data;

	(void)argv;
	if (argc != 1)
		return (-1);
	token = NULL;
	cmds = NULL;
	g_sigint = 0;
	data = ft_init_shell(env);
	while (1)
	{
		ft_signalhandle();
		ft_routine(token, cmds, data);
	}
	return (0);
}
