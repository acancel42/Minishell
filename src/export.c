#include "minishell.h"

static int	check_arg(char *args)
{
	int	i;

	i = -1;
	if (args[0] != '_' && !ft_isalpha(args[0]))
		return (1);
	while (args[++i])
		if (ft_isoperator(args[i]))
			return (1);
	return (0);
}

int	ft_isexport(char *args, char **env)
{
	char	*variable;
	int		is_export;
	int		j;
	int		k;
	int		i;

	is_export = 0;
	j = 0;
	k = 0;
	i = 0;
	while (args[i] && args[i] != '=')
		i++;
	variable = ft_calloc(i + 1, sizeof(char));
	while (j < i)
	{
		variable[j] = args[j];
		j++;
	}
	while (env[k++] && env[k] != NULL)
	{
		if (ft_envcmp(env[k], variable) == 0)
			is_export = 1;
	}
	free(variable);
	return (is_export);
}

int	ft_export(char **args, t_data *data)
{
	int		i;
	char	**new_env;
	char	**new_export;

	new_env = NULL;
	new_export = NULL;
	i = 1;
	if (ft_print_export(args, data) == 1)
		return (0);
	while (args[i])
	{
		if (check_arg(args[i]))
		{
			write(1, "not a valid identifier\n", 24);
			i++;
			continue ;
		}
		if (ft_strchr(args[i], '='))
		{
			ft_replace_export(&new_env, &new_export, i, data);
			ft_free_tab(data->my_env);
			data->my_env = tab_dup(new_env);
			ft_free_tab(data->export);
			data->export = tab_dup(new_export);
		}
		else
		{
			if (ft_isexport(args[i], data->export))
			{
				i++;
				continue ;
			}
			new_export = tab_join((data->export), args[i]);
			if (!new_export)
				return (-1);
			ft_free_tab(data->export);
			data->export = tab_dup(new_export);
		}
		if (new_env)
			ft_free_tab(new_env);
		if (new_export)
			ft_free_tab(new_export);
		i++;
	}
	return (0);
}
