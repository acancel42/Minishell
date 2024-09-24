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
	buf = getcwd(NULL, 0);
	if (!buf)
		ft_exit(NULL, NULL, data);
	temp = ft_strjoin("PWD=", buf, 0);
	free(buf);
	if (!temp)
		ft_exit(NULL, NULL, data);
	data->my_env[0] = ft_strdup(temp);
	free(temp);
	if (!data->my_env[0])
		ft_exit(NULL, NULL, data);
	data->my_env[1] = ft_strdup("LOGNAME=?");
	if (!data->my_env[1])
		ft_exit(NULL, NULL, data);
	data->my_env[2] = ft_strdup("SESSION_MANAGER=?");
	if (!data->my_env[2])
		ft_exit(NULL, NULL, data);
	data->my_env[3] = ft_strdup("PATH=/usr/bin/");
	if (!data->my_env[3])
		ft_exit(NULL, NULL, data);
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
		if (data->my_env)
			ft_free_tab(data->my_env);
		data->my_env = tab_dup(env);
		if (!data->my_env)
			ft_free_tab(data->my_env);
		if (data->export)
			ft_free_tab(data->export);
		data->export = tab_dup(env);
		if (!data->export)
			ft_free_tab(data->export);
	}
}

void	ft_variable_missing(t_data *data, char *variable)
{
	char	**new_env;

	new_env = tab_join(data->my_env, variable);
	if (!new_env)
		ft_exit(NULL, NULL, data);
	ft_free_tab(data->my_env);
	data->my_env = tab_dup(new_env);
	ft_free_tab(new_env);
	if (!data->my_env)
		ft_exit(NULL, NULL, data);
}

void	ft_pwd_missing(t_data *data)
{
	char	*buf;
	char	*temp;

	buf = NULL;
	buf = getcwd(NULL, 0);
	if (!buf)
		ft_exit(NULL, NULL, data);
	temp = ft_strjoin("PWD=", buf, 0);
	free(buf);
	if (!temp)
		ft_exit(NULL, NULL, data);
	ft_variable_missing(data, temp);
	free(temp);
}

void	ft_is_env_op(t_data *data)
{
	if (!find_env_var("PWD", data->my_env))
		ft_pwd_missing(data);
	if (!find_env_var("LOGNAME", data->my_env))
		ft_variable_missing(data, "LOGNAME=?");
	if (!find_env_var("SESSION_MANAGER", data->my_env))
		ft_variable_missing(data, "SESSION_MANAGER=?");
	if (!find_env_var("PATH", data->my_env))
		ft_variable_missing(data, "PATH=?");
	ft_free_tab(data->export);
	data->export = tab_dup(data->my_env);
	if (!data->export)
		ft_free_tab(data->export);
}
