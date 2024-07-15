#include "minishell.h"

static int	oredir_handle(char *line, int *i)
{
	int count;
	int j;
	int l;

	j = 0;
	l = 0;
	count = 0;
	while (line[*i])
	{
		while (line[*i] == '>')
		{
			count++;
			(*i)++;
		}
		while (ft_iswspace(line[*i]))
			(*i)++;
		if (ft_isalnum(line[*i]) || line[*i] == '_')
		{
			j++;
			break;
		}
		if (line[*i] == '<')
		{
			l++;
			(*i)++;
		}
		if (line[*i] == '>')
		{
			l++;
			(*i)++;
		}
		if (line[*i] == '|')
		{
			l++;
			(*i)++;
		}
		(*i)++;
	}
	if (count > 2 || l > 0 || j == 0)
	{
		printf("syntax error\n");
		return (2);
	}
	return (0);
}

static int	iredir_handle(char *line, int *i)
{
	int count;
	int j;
	int l;

	j = 0;
	l = 0;
	count = 0;
	while (line[*i])
	{
		while (line[*i] == '<')
		{
			count++;
			(*i)++;
		}
		while (ft_iswspace(line[*i]))
			(*i)++;
		if (ft_isalnum(line[*i]) || line[*i] == '_')
		{
			j++;
			break;
		}
		if (line[*i] == '<')
		{
			l++;
			(*i)++;
		}
		if (line[*i] == '>')
		{
			l++;
			(*i)++;
		}
		if (line[*i] == '|')
		{
			l++;
			(*i)++;
		}
		(*i)++;
	}
	if (count > 2 || l > 0 || j == 0)
	{
		printf("syntax error\n");
		return (2);
	}
	return (0);
}

static int	pipe_handle(char *line, int *i)
{
	int count;
	int j;
	int l;

	j = 0;
	l = 0;
	count = 0;
	while (line[*i])
	{
		while (line[*i] == '|')
		{
			count++;
			(*i)++;
		}
		while (ft_iswspace(line[*i]))
			(*i)++;
		if (ft_isalnum(line[*i]) || line[*i] == '_')
		{
			j++;
			break;
		}
		if (line[*i] == '<')
		{
			l++;
			(*i)++;
		}
		if (line[*i] == '>')
		{
			l++;
			(*i)++;
		}
		if (line[*i] == '|')
		{
			l++;
			(*i)++;
		}
		(*i)++;
	}
	if (count > 1 || l > 0 || j == 0)
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

	i = -1;
	j = 0;
	while (data->line[++i])
	{
		if (data->line[i] == '>')
			if (oredir_handle(data->line, &i) == 2)
				return (2);
		if (data->line[i] == '<')
			if (iredir_handle(data->line, &i) == 2)
				return (2);
		if (data->line[i] == '|')
			if (pipe_handle(data->line, &i) == 2)
				return (2);
	}
	return (0);
}
