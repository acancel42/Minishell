#include "minishell.h"

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
	i = 0;
	return (my_env);
}
