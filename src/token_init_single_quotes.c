/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_init_single_quotes.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acancel <acancel@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 08:59:09 by acancel           #+#    #+#             */
/*   Updated: 2024/09/25 08:59:10 by acancel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_single_quote_util(char *src, t_token **token, \
										t_data *data, t_token **temp)
{
	int	i;

	i = 0;
	if (src[i] == '\'' && src[i + 1] == '\0')
	{
		printf("syntax error\n");
		return (-1);
	}
	i++;
	if (data->rflag == 0)
	{
		*temp = ft_toknew(src[i], T_S_QUOTED_WORD);
		if (!(*temp))
			ft_exit(*token, NULL, data);
	}
	else
	{
		data->rflag = 0;
		*temp = ft_toknew(src[i], T_RS_QUOTED_WORD);
		if (!(*temp))
			ft_exit(*token, NULL, data);
	}
	ft_tokadd_back(token, *temp);
	i++;
	return (i);
}

static int	handle_empty_single_quote(t_data *data, t_token **token, char *src)
{
	t_token	*temp;
	int		i;

	i = 0;
	temp = NULL;
	if (data->rflag == 0)
	{
		temp = ft_toknew(0, T_S_QUOTED_WORD);
		if (!temp)
			ft_exit(*token, NULL, data);
	}
	else
	{
		data->rflag = 0;
		temp = ft_toknew(0, T_RS_QUOTED_WORD);
		if (!temp)
			ft_exit(*token, NULL, data);
	}
	ft_tokadd_back(token, temp);
	if (!ft_iswspace(src[i + 2]) && !ft_isoperator(src[i + 2]))
		temp->is_separated = 1;
	return (i + 2);
}

int	handle_single_quote(char *src, t_token **token, t_data *data)
{
	char	c;
	int		i;
	t_token	*temp;

	if (src[0] == '\'' && src[1] == '\'')
		return (handle_empty_single_quote(data, token, src));
	i = handle_single_quote_util(src, token, data, &temp);
	if (i == -1)
		return (-1);
	while (src[i] && src[i] != '\'')
	{
		c = src[i];
		temp->value = ft_charjoin(temp->value, c);
		if (!temp->value)
			ft_exit(*token, NULL, data);
		i++;
	}
	if (src[i] != '\'')
	{
		printf("syntax error\n");
		return (-1);
	}
	else if (!ft_iswspace(src[++i]) && !ft_isoperator(src[i]))
		temp->is_separated = 1;
	return (i);
}
