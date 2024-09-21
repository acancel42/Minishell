#include "minishell.h"

static char	**tab_delete_util(char **tab, char *str, int j)
{
	int		i;
	char	**new_tab;

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
	new_tab = tab_delete_util(tab, str, j);
	if (!new_tab)
		return (NULL);
	return (new_tab);
}

int	ft_unset_util(t_data *data, char **new_env, char **new_export)
{
	ft_free_tab(data->my_env);
	data->my_env = tab_dup(new_env);
	if (!data->my_env)
	{
		ft_free_tab(new_env);
		ft_free_tab(new_export);
		return (-1);
	}
	ft_free_tab(data->export);
	data->export = tab_dup(new_export);
	if (!data->export)
	{
		ft_free_tab(new_env);
		ft_free_tab(new_export);
		return (-1);
	}
	ft_free_tab(new_env);
	ft_free_tab(new_export);
	return (0);
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
		if (!new_env)
			return (-1);
		new_export = tab_delete(data->export, args[i]);
		if (!new_export)
		{
			ft_free_tab(new_env);
			return (-1);
		}
		if (ft_unset_util(data, new_env, new_export) == -1)
			return (-1);
		i++;
	}
	return (0);
}
