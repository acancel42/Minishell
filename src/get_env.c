#include "minishell.h"

char	**ft_shlvl(char **my_env)
{
	int		i;
	int 	lvl;
	char	*shlvl;

	i = 0;
	while (ft_strncmp(my_env[i], "SHLVL=", 6))
		i++;
	lvl = ft_atoi(my_env[i] + 6);
	lvl++;
	shlvl = ft_itoa(lvl);
	if (!shlvl)
		return (NULL);
	i = 0;
	while (ft_strncmp(my_env[i], "SHLVL=", 6))
		i++;
	my_env[i] = ft_strjoin("SHLVL=", shlvl, 0);
	free(shlvl);
	return (my_env);
}

char	**ft_get_env(char **env)
{
	char	**my_env;
	size_t	i;

	i = 0;
	while (env[i])
		i++;
	my_env = ft_calloc(i + 1, sizeof(char *));
	if (!my_env)
		return (NULL);
	i = 0;
	while (env[i])
	{
		my_env[i] = ft_strdup(env[i]);
		if (!my_env[i])
		{
			ft_free_tab(my_env);
			return (NULL);
		}
		i++;
	}
	my_env = ft_shlvl(my_env);
	if (!my_env)
		return (NULL);
	i = 0;
	return (my_env);
}
