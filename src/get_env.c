#include "minishell.h"

static void	ft_empty_env(t_data *data)
{
	size_t	i;
	char	*buf;
	char	*temp;

	buf = NULL;
	i = 0;
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

void	ft_get_env(t_data *data, char **env)
{
	if (!env[0])
	{
		ft_empty_env(data);
		data->export = tab_dup(data->my_env);
		if (!data->export)
			ft_free_tab(data->export);
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

void	ft_is_env_op(t_data *data)
{
	char	*buf;
	char	*temp;

	buf = NULL;
	if (!find_env_var("PWD", data->my_env))
	{
		temp = ft_strjoin("PWD=", getcwd(buf, 0), 0);
		data->my_env = tab_join(data->my_env, temp);
		free(buf);
		free(temp);
	}
	if (!find_env_var("LOGNAME", data->my_env))
		data->my_env = tab_join(data->my_env, "LOGNAME=?");
	if (!find_env_var("SESSION_MANAGER", data->my_env))
		data->my_env = tab_join(data->my_env, "SESSION_MANAGER=?");
	if (!find_env_var("PATH", data->my_env))
		data->my_env = tab_join(data->my_env, "PATH=/usr/bin/");
}
