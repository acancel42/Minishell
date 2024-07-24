#include "minishell.h"

int ft_envcmp(char *env, char *variable)
{
	char	*temp;
	int		res;

	res = 1;
	temp = ft_strjoin(variable, "=", 0);
	if (ft_strncmp(env, temp, ft_strlen(temp)) == 0 || ft_strncmp(env, variable, ft_strlen(variable) + 1) == 0)
		res = 0;
	free(temp);
	return (res);
}

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
	// printf("new tab : %s\n", new_tab[i]);
	new_tab[i + 1] = NULL;
	return (new_tab);
}

char **tab_replace(char **env, char *args)
{
	char	*variable;
	int		j;
	int		k;
	int		i;

	j = 0;
	k = 0;
	i = 0;
	while (args[i] && args[i++] != '=')
		;
	variable = ft_calloc(i + 1, sizeof(char));
	while (j < i - 1)
	{
		variable[j] = args[j];
		j++;
	}
	while (env[k++] && env[k] != NULL)
	{
		if (ft_envcmp(env[k], variable) == 0)
			env[k] = ft_strdup(args);
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
			return(1);
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

	i = 0;
	if (!args[1])
	{
		while(data->export[i++] && data->export[i] != NULL)
			printf("%s\n", data->export[i]);
		return(0);
	}
	i++;
	while (args[i])
	{
		if (check_arg(args[i]))
		{
			write(1, "not a valid identifier\n", 24);
			i++;
			continue;
		}
		if (ft_strchr(args[i], '='))
		{
			if (ft_isexport(args[i], data->my_env) && ft_isexport(args[i], data->export))
			{
				new_env = tab_replace((data->my_env), args[i]);
				new_export = tab_replace((data->export), args[i]);
			}
			else if (!ft_isexport(args[i], data->my_env) && ft_isexport(args[i], data->export))
			{
				new_env = tab_join((data->my_env), args[i]);
				new_export = tab_replace((data->export), args[i]);
			}
			else
			{
				new_env = tab_join((data->my_env), args[i]);
				new_export = tab_join((data->export), args[i]);
			}
			if (!new_env || !new_export)
				return (-1);
			(data->my_env) = new_env;
			(data->export) = new_export;
		}
		else
		{
			if (ft_isexport(args[i], data->export))
			{
				i++;
				continue;
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
