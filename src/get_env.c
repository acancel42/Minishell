#include "minishell.h"

void	ft_get_env(t_data *data, char **env)
{
	size_t	i;

	i = 0;
	while (env[i])
		i++;
	data->my_env = ft_calloc(i + 1, sizeof(char *));
	data->export = ft_calloc(i + 1, sizeof(char *));
	if (!data->my_env || !data->export)
		return ;
	i = 0;
	while (env[i])
	{
		data->my_env[i] = ft_strdup(env[i]);
		data->export[i] = ft_strdup(env[i]);
		if (!data->my_env[i] || !data->export[i])
		{
			ft_free_tab(data->my_env);
			ft_free_tab(data->export);
			return ;
		}
		i++;
	}
}
