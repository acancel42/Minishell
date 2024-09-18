#include "minishell.h"

char	**tab_replace(char **env, char *args)
{
	char	*variable;
	int		j;
	int		k;
	int		i;

	j = -1;
	k = 0;
	i = 0;
	while (args[i] && args[i++] != '=')
		;
	variable = ft_calloc(i + 1, sizeof(char));
	while (++j < i - 1)
		variable[j] = args[j];
	while (env[k++] && env[k] != NULL)
	{
		if (ft_envcmp(env[k], variable) == 0)
		{
			env[k] = ft_strdup(args);
			if (!env[k])
				return (NULL);
		}
	}
	free(variable);
	return (env);
}

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
			(data->my_env) = new_env;
			(data->export) = new_export;
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
			(data->export) = new_export;
		}
		i++;
	}
	return (0);
}
