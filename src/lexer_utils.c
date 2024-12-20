/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acancel <acancel@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 08:57:38 by acancel           #+#    #+#             */
/*   Updated: 2024/09/26 00:11:34 by acancel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isword(t_token *token)
{
	if (token->type == T_D_QUOTED_WORD || token->type == T_S_QUOTED_WORD \
		|| token->type == T_WORD)
		return (1);
	return (0);
}

int	lexer_init(t_token **token, t_data *data)
{
	int	i;

	i = 0;
	while (data->line[i])
	{
		i = token_init(data->line, i, token, data);
		if (i == -1)
		{
			data->last_error_status = 2;
			return (-1);
		}
	}
	return (1);
}

void	init_cmd(t_commands **cmds, t_token *token, t_data *data)
{
	t_commands	*temp;
	int			flag;

	flag = 0;
	while (token)
	{
		if (token->type == T_PIPE)
			token = token->next;
		temp = ft_cmdnew(flag++);
		ft_cmdadd_back(cmds, temp);
		data->index_max = temp->index;
		while (token && token->type != T_PIPE)
			token = token->next;
	}
}

int	count_type_until_pipe(t_token *token, t_token_types type, int flag)
{
	int	count;

	count = 0;
	while (token && token->type != T_PIPE)
	{
		if (token->type == type)
		{
			if (flag == 0)
				count++;
			else if (flag == 1)
				if (token->value[0] != '-')
					count++;
		}
		token = token->next;
	}
	return (count);
}

char	*find_env_var(char *name, char **env)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(name);
	while (env[i])
	{
		if (ft_strncmp(env[i], name, len) == 0 && env[i][len] == '=')
			return (&env[i][len + 1]);
		i++;
	}
	return (NULL);
}
