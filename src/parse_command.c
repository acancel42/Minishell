#include "../../inc/minishell.h"

int	is_wspace(char c)
{
	if (c == '\t' || c == '\n' || c == '\v' || \
		c == '\f' || c == '\r' || c == ' ')
		return (1);
	return (0);
}

static char	*worddup(char const *str, int i)
{
	int		wrdlen;
	char	*tab;

	wrdlen = 1;
	while (is_wspace(str[wrdlen]) == 0)
		wrdlen++;
	tab = ft_calloc((wrdlen + 1), sizeof(char));
	if (!tab)
		return (0);
	while (i < wrdlen)
	{
		tab[i] = str[i];
		i++;
	}
	return (tab);
}

void	parse_command(t_commands *commands, char *line)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (is_wspace(line[i]) == 1)
		i++;
	while (line[i])
	{
		if (line[i] == '<')
		{
			i++;
			while (is_wspace(line[i]) == 1)
				i++;
			if (line[i] != '\0')
			{
				commands->input.name = worddup(line, i);
				ft_printf("%s", commands->input.name);
				ft_printf("%d\n", 1);
				i++;
			}
			while (is_wspace(line[i]) == 1)
				i++;
		}
		if (line[i] == '>')
		{
			i++;
			while (is_wspace(line[i]) == 1)
				i++;
			if (line[i])
			{
				commands->output.name = worddup(line, i);
				ft_printf("%s", commands->output.name);
				ft_printf("%d\n", 2);
				i++;
			}
			while (is_wspace(line[i]) == 1)
				i++;
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_commands	commands;

	commands.input.name = NULL;
	commands.output.name = NULL;
	(void)(argc);
	parse_command(&commands, argv[1]);
	ft_printf("%s", commands.input.name);
	ft_printf("%s", commands.output.name);
}
