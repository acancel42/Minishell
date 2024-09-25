/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acancel <acancel@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 08:58:36 by acancel           #+#    #+#             */
/*   Updated: 2024/09/25 21:27:33 by acancel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	oredir_handle(char *line, int *i)
{
	int	op_count;
	int	is_word;
	int	multiple_op;

	is_word = 0;
	multiple_op = 0;
	op_count = 0;
	while (line[*i])
	{
		while (line[*i] == '>')
		{
			op_count++;
			(*i)++;
		}
		if (is_mult_op(line, i, &multiple_op, &is_word) == 1)
			break ;
	}
	if (op_count > 2 || multiple_op > 0 || is_word == 0)
	{
		printf("syntax error\n");
		return (2);
	}
	return (0);
}

int	iredir_handle(char *line, int *i)
{
	int	op_count;
	int	is_word;
	int	multiple_op;

	is_word = 0;
	multiple_op = 0;
	op_count = 0;
	while (line[*i])
	{
		while (line[*i] == '<')
		{
			op_count++;
			(*i)++;
		}
		if (is_mult_op(line, i, &multiple_op, &is_word) == 1)
			break ;
	}
	if (op_count > 2 || multiple_op > 0 || is_word == 0)
	{
		printf("syntax error\n");
		return (2);
	}
	return (0);
}

int	op_counter(char *line, int *i, int *is_word, int *multi_op)
{
	while (ft_iswspace(line[*i]))
		(*i)++;
	if (line[*i] && (ft_isalnum(line[*i]) || \
		(line[*i +1] && (line[*i] == '"' && line[*i + 1] == '"')) \
		|| line[*i] == '_'))
	{
		(*is_word)++;
		return (1);
	}
	else if (line[*i] == '|')
	{
		(*multi_op)++;
		(*i)++;
	}
	else if (line[*i])
		(*i)++;
	return (0);
}

int	pipe_handle(char *line, int *i)
{
	int	op_count;
	int	is_word;
	int	multiple_op;

	is_word = 0;
	multiple_op = 0;
	op_count = 0;
	while (line[*i])
	{
		while (line[*i] == '|')
		{
			op_count++;
			(*i)++;
		}
		if (op_counter(line, i, &is_word, &multiple_op) == 1)
			break ;
	}
	if (line[0] == '|' || op_count > 1 || multiple_op > 0 || is_word == 0)
	{
		printf("syntax error\n");
		return (2);
	}
	return (0);
}

int	prelexer_check(t_data *data)
{
	int	i;
	int	wspace;

	wspace = 0;
	i = 0;
	while (data->line[i])
	{
		if (ft_iswspace(data->line[i]) == 0)
			wspace = 1;
		if (data->line[i] == '"')
			i = skip_quoted('"', data->line, i);
		else if (data->line[i] == '\'')
			i = skip_quoted('\'', data->line, i);
		else if (is_redir_or_pipe(data, i) == 2)
			return (2);
		else
			i++;
	}
	if (wspace == 0)
		return (2);
	return (0);
}
