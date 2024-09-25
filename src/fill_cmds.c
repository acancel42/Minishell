/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acancel <acancel@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 09:28:15 by acancel           #+#    #+#             */
/*   Updated: 2024/09/25 09:46:38 by acancel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*handle_rword_utils(t_token **token, t_data *data, \
								char *temp2)
{
	char	*temp;

	temp = ft_strdup(temp2);
	free (temp2);
	if (!temp)
		ft_exit(*token, data->cmds, data);
	while ((*token)->next && (*token)->is_separated == 1)
		handle_rword_loop(token, data, &temp);
	return (temp);
}

static int	handle_rw_utils(t_token **token, t_commands **cmds, \
							t_data *data, char **redir_type)
{
	if ((*token)->type == T_HEREDOC && \
		ft_is_variable((*token)->next->value) == 1)
	{
		printf("syntax error\n");
		return (2);
	}
	*redir_type = ft_strdup((*token)->value);
	if (!(*redir_type))
		ft_exit(*token, *cmds, data);
	(*token) = (*token)->next;
	if (ft_strncmp((*token)->value, "$", 2) == 0 && \
		ft_strncmp((*token)->next->value, "", 1) == 0)
		(*token) = (*token)->next;
	return (0);
}

int	handle_rword(t_commands **cmds, t_token **token, t_data *data, int *k)
{
	char	*redir_type;
	char	*temp2;
	int		j;

	temp2 = NULL;
	if (handle_rw_utils(token, cmds, data, &redir_type) == 2)
		return (2);
	j = 0;
	if ((*token)->type != T_RS_QUOTED_WORD)
		j = expand_variables(&temp2, (*token)->value, data);
	else
	{
		temp2 = ft_strdup((*token)->value);
		if (!temp2)
			ft_exit(*token, *cmds, data);
	}
	temp2 = handle_rword_utils(token, data, temp2);
	(*cmds)->redirections[(*k)++] = ft_strjoin(redir_type, temp2, 0);
	if (!(*cmds)->redirections[(*k - 1)])
		ft_exit(*token, *cmds, data);
	free(redir_type);
	free(temp2);
	return (0);
}

static void	fill_cmd_util(t_commands **cmds, t_token *token, t_data *data)
{
	if (!(*cmds)->args)
		(*cmds)->args = ft_calloc(count_type_until_pipe(token, T_WORD, 0) \
		+ count_type_until_pipe(token, T_D_QUOTED_WORD, 0) \
		+ count_type_until_pipe(token, T_S_QUOTED_WORD, 0) \
		+ 1, sizeof(char *));
	if (!(*cmds)->args)
		ft_exit(token, *cmds, data);
	if (!(*cmds)->redirections)
		(*cmds)->redirections = \
			ft_calloc(count_type_until_pipe(token, T_RWORD, 0) \
			+ count_type_until_pipe(token, T_RD_QUOTED_WORD, 0) \
			+ count_type_until_pipe(token, T_RS_QUOTED_WORD, 0) \
			+ 1, sizeof(char *));
	if (!(*cmds)->redirections)
		ft_exit(token, *cmds, data);
}

int	fill_cmd(t_commands **cmds, t_token *token, t_data *data)
{
	int	i;
	int	k;

	k = 0;
	i = 0;
	while (token && *cmds)
	{
		fill_cmd_util(cmds, token, data);
		if (ft_isword(token))
			handle_word(cmds, &token, data, &i);
		else if (token->type == T_REDIR_OUT || token->type == T_REDIR_IN \
				|| token->type == T_APPEND_OUT || token->type == T_HEREDOC)
		{
			if (handle_rword(cmds, &token, data, &k) == 2)
				return (2);
		}
		else if (token->type == T_PIPE)
		{
			k = 0;
			i = 0;
			cmds = &(*cmds)->next;
		}
		token = token->next;
	}
	return (0);
}
