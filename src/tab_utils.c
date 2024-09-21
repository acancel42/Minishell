#include "minishell.h"

char	**tab_dup(char **env)
{
	char	**new_env;
	int		i;

	i = 0;
	while (env[i++])
		;
	new_env = ft_calloc(i + 1, sizeof(char *));
	if (!new_env)
		return (NULL);
	i = -1;
	while (env[++i])
	{
		new_env[i] = ft_strdup(env[i]);
		if (!new_env[i])
		{
			ft_free_tab(new_env);
			return (NULL);
		}
	}
	return (new_env);
}

static char	**ft_line_replace(char *variable, char *args, char **env)
{
	int		k;
	char	**new_env;

	k = 0;
	new_env = tab_dup(env);
	if (!new_env)
		return (NULL);
	while (new_env[k] && new_env[k] != NULL)
	{
		if (ft_envcmp(new_env[k], variable) == 0)
		{
			free(new_env[k]);
			new_env[k] = ft_strdup(args);
			if (!new_env[k])
				return (NULL);
		}
		k++;
	}
	return (new_env);
}

char	**tab_replace(char **env, char *args)
{
	char	**new_env;
	char	*variable;
	int		j;
	int		i;

	j = 0;
	i = 0;
	while (args[i] && args[i++] != '=')
		;
	variable = ft_calloc(i + 1, sizeof(char));
	while (j < i - 1)
	{
		variable[j] = args[j];
		j++;
	}
	new_env = ft_line_replace(variable, args, env);
	free(variable);
	if (!new_env)
		return (NULL);
	return (new_env);
}
