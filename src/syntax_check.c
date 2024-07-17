#include "minishell.h"

static int	oredir_handle(char *line, int *i)
{
	int op_count;
	int is_word;
	int multiple_op;

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
		while (ft_iswspace(line[*i]))
			(*i)++;
		if (ft_isalnum(line[*i]) || line[*i] == '_')
		{
			is_word++;
			break;
		}
		if (line[*i] == '<')
		{
			multiple_op++;
			(*i)++;
		}
		else if (line[*i] == '>')
		{
			multiple_op++;
			(*i)++;
		}
		else if (line[*i] == '|')
		{
			multiple_op++;
			(*i)++;
		}
		else if (line[*i])
			(*i)++;
	}
	if (op_count > 2 || multiple_op > 0 || is_word == 0)
	{
		printf("syntax error\n");
		return (2);
	}
	return (0);
}

static int	iredir_handle(char *line, int *i)
{
	int op_count;
	int is_word;
	int multiple_op;

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
		while (ft_iswspace(line[*i]))
			(*i)++;
		if (ft_isalnum(line[*i]) || line[*i] == '_')
		{
			is_word++;
			break;
		}
		if (line[*i] == '<')
		{
			multiple_op++;
			(*i)++;
		}
		else if (line[*i] == '>')
		{
			multiple_op++;
			(*i)++;
		}
		else if (line[*i] == '|')
		{
			multiple_op++;
			(*i)++;
		}
		else if (line[*i])
			(*i)++;
	}
	if (op_count > 2 || multiple_op > 0 || is_word == 0)
	{
		printf("syntax error\n");
		return (2);
	}
	return (0);
}

static int	pipe_handle(char *line, int *i)
{
	int op_count;
	int is_word;
	int multiple_op;

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
		while (ft_iswspace(line[*i]))
			(*i)++;
		if (ft_isalnum(line[*i]) || line[*i] == '_')
		{
			is_word++;
			break;
		}
		else if (line[*i] == '|')
		{
			multiple_op++;
			(*i)++;
		}
		else if (line[*i])
			(*i)++;
	}
	if (line[0] == '|' || op_count > 1 || multiple_op > 0 || is_word == 0)
	{
		printf("syntax error\n");
		return (2);
	}
	return (0);
}

int prelexer_check(t_data *data)
{
	int i;
	int j;
	int wspace;

	wspace = 0;
	i = 0;
	j = 0;
	while (data->line[i])
	{
		if (ft_iswspace(data->line[i]) == 0)
			wspace = 1;
		if (data->line[i] == '>')
		{
			if (oredir_handle(data->line, &i) == 2)
				return (2);
		}
		else if (data->line[i] == '<')
		{
			if (iredir_handle(data->line, &i) == 2)
				return (2);
		}
		else if (data->line[i] == '|')
		{
			if (pipe_handle(data->line, &i) == 2)
				return (2);
		}
		else
			i++;
	}
	if (wspace == 0)
		return(2);
	return (0);
}
