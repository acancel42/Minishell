#include "minishell.h"

char	**tab_delete(char **tab, char *str)
{
	int		i;
	int		j;
	char	**new_tab;

	i = 0;
	j = 0;
	while (tab[i])
	{
		if (ft_envcmp(tab[i], str) != 0)
			j++;
		i++;
	}
	new_tab = ft_calloc(j + 1, sizeof(char *));
	if (!new_tab)
		return (NULL);
	i = 0;
	j = 0;
	while (tab[i])
	{
		if (ft_envcmp(tab[i], str) != 0)
		{
			new_tab[j++] = ft_strdup(tab[i]);
			if (!new_tab[j - 1])
				return (NULL);
		}
		i++;
	}
	return (new_tab);
}

int	ft_unset(char **args, t_data *data)
{
	int		i;
	char	**new_env;
	char	**new_export;

	i = 1;
	while (args[i])
	{
		new_env = tab_delete(data->my_env, args[i]);
		new_export = tab_delete(data->export, args[i]);
		if (!new_env || !new_export)
			return (-1);
		(data->my_env) = new_env;
		(data->export) = new_export;
		i++;
	}
	return (0);
}
