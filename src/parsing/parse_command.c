#include "../../inc/minishell.h"

int	is_wspace(char c)
{
	if (c == '\t' || c == '\n' || c == '\v' || \
		c == '\f' || c == '\r' || c == ' ')
		return (1);
	return (0);
}

static char	*worddup(char const *str, char c)
{
	int		wrdlen;
	int		i;
	char	*tab;

	wrdlen = 1;
	i = 0;
	while (str[wrdlen] && str[wrdlen] != c)
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
			if (line[i])
			{
				commands->input.name = worddup(line, i);
				i++;
			}
			while (is_wspace(line[i]) == 1)
				i++;
		}
	}
}
