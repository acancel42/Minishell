/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acancel <acancel@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 08:57:42 by acancel           #+#    #+#             */
/*   Updated: 2024/09/25 09:30:53 by acancel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*handle_w_util(t_token **token, t_data *data, char *temp2, int j)
{
	char	*temp;
	char	*temp3;

	temp = ft_strdup(temp2);
	free(temp2);
	while ((*token)->next && (*token)->is_separated == 1)
	{
		if (ft_strncmp((*token)->value, "$", 2) == 0 && \
			ft_strncmp((*token)->next->value, "", 1) == 0)
			(*token) = (*token)->next;
		(*token) = (*token)->next;
		if ((*token)->type != T_S_QUOTED_WORD)
			j = expand_variables(&temp3, (*token)->value, data);
		else
		{
			temp3 = ft_strdup((*token)->value);
			if (!temp3)
				ft_exit(*token, data->cmds, data);
		}
		temp = ft_strjoin(temp, temp3, 1);
		if (!temp)
			ft_exit(*token, data->cmds, data);
		free(temp3);
	}
	return (temp);
}

static char	*handle_word_util(t_commands **cmds, t_token **token, t_data *data)
{
	char	*temp2;
	int		j;

	temp2 = NULL;
	j = 0;
	if (ft_strncmp((*token)->value, "", 1 == 0) && (*token)->is_separated == 0)
		temp2 = ft_strdup((*token)->value);
	else
	{
		if ((*token)->next && ft_strncmp((*token)->value, "$", 2) == 0 && \
				ft_strncmp((*token)->next->value, "", 1) == 0)
			(*token) = (*token)->next;
		if ((*token)->type != T_S_QUOTED_WORD)
			j = expand_variables(&temp2, (*token)->value, data);
		else
		{
			temp2 = ft_strdup((*token)->value);
			if (!temp2)
				ft_exit(*token, *cmds, data);
		}
		temp2 = handle_w_util(token, data, temp2, j);
	}
	return (temp2);
}

void	handle_word(t_commands **cmds, t_token **token, t_data *data, int *i)
{
	char	*temp2;

	temp2 = handle_word_util(cmds, token, data);
	if (*i == 0)
	{
		(*cmds)->name = ft_strdup(temp2);
		if (!(*cmds)->name)
			ft_exit(*token, *cmds, data);
	}
	(*cmds)->args[(*i)++] = ft_strdup(temp2);
	if (!(*cmds)->args[(*i) - 1])
		ft_exit(*token, *cmds, data);
	free(temp2);
}

void	handle_rword_loop(t_token **token, t_data *data, char **temp)
{
	int		j;
	char	*temp3;

	j = 0;
	if (ft_strncmp((*token)->value, "$", 2) == 0 && \
		ft_strncmp((*token)->next->value, "", 1) == 0)
		(*token) = (*token)->next;
	(*token) = (*token)->next;
	if ((*token)->type != T_RS_QUOTED_WORD)
		j = expand_variables(&temp3, (*token)->value, data);
	else
	{
		temp3 = ft_strdup((*token)->value);
		if (!temp3)
		{
			free(*temp);
			ft_exit(*token, data->cmds, data);
		}
	}
	*temp = ft_strjoin(*temp, temp3, 1);
	free(temp3);
	if (!(*temp))
		ft_exit(*token, data->cmds, data);
}

int	ft_is_variable(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == '$')
			return (1);
	return (0);
}
