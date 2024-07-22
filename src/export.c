#include "minishell.h"

char	**tab_join(char **tab, char *str)
{
	int		i;
	char	**new_tab;

	i = 0;
	while (tab[i])
		i++;
	new_tab = malloc(sizeof(char *) * (i + 2));
	if (!new_tab)
		return (NULL);
	i = 0;
	while (tab[i])
	{
		new_tab[i] = ft_strdup(tab[i]);
		i++;
	}
	new_tab[i] = ft_strdup(str);
	new_tab[i + 1] = NULL;
	free(tab);
	return (new_tab);
}

int	ft_export(char **args, t_data *data)
{
	int		i;
	char	**new_env;

	i = 1;
	while (args[i])
	{
		if (ft_strchr(args[i], '='))
		{
			new_env = tab_join((data->my_env), args[i]);
			if (!new_env)
				return (-1);
			(data->my_env) = new_env;
		}
		i++;
	}
	return (0);
}
