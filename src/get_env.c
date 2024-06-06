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
	return (my_env);
}

// int	main(int ac, char **av, char **env)
// {
// 	int		i;
// 	char	**my_env;

// 	(void) ac, (void)av;
// 	i = -1;
// 	my_env = ft_get_env(env);
// 	if (!my_env)
// 		return (-1);
// 	while (my_env[++i])
// 		printf("%s\n", my_env[i]);
// 	ft_free_tab(my_env, i);
// 	return (0);
// }
