#include "minishell.h"

void	ft_get_env(t_data *data, char **env)
{
	size_t	i;
	char	*buf;
	char	*temp;

	buf = NULL;
	i = 0;
	if (!env[0])
	{
		data->my_env = ft_calloc(5, sizeof(char *));
		data->export = ft_calloc(5, sizeof(char *));
		if (!data->my_env || !data->export)
		{
			if (data->my_env)
				ft_free_tab(data->my_env);
			exit(EXIT_FAILURE);
		}
		temp = ft_strjoin("PWD=", getcwd(buf, 0), 0);
		data->my_env[0] = ft_strdup(temp);
		data->my_env[1] = ft_strdup("LOGNAME=?");
		data->my_env[2] = ft_strdup("SESSION_MANAGER=?");
		data->my_env[3] = ft_strdup("PATH=/usr/bin/");
		free(buf);
		free(temp);
	}
	else
	{
		data->my_env = tab_dup(env);
		if (!data->my_env)
			ft_free_tab(data->my_env);
		data->export = tab_dup(env);
		if (!data->export)
			ft_free_tab(data->export);
	}
}
