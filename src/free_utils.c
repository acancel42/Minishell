#include "minishell.h"

void	ft_free_tab(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
}

void	free_data(t_data *data, t_commands **cmds)
{
	if (*cmds)
		ft_cmdsclear(cmds);
	if (data->token)
		ft_tokenclear(&data->token);
	if (data->line)
		free(data->line);
	if (data->user)
		free(data->user);
	data->index_max = 0;
	data->pflag = 0;
}

void	free_monitoring(char *host, char *username, char *pwd)
{
	if (pwd)
		free(pwd);
	if (host)
		free(host);
	if (username)
		free(username);
	return ;
}

void	free_child(t_data *data, t_commands *cmds)
{
	free_data(data, &cmds);
	if (data->home)
		free(data->home);
	if (data->export)
		ft_free_tab(data->export);
	if (data->my_env)
		ft_free_tab(data->my_env);
	exit(data->last_error_status);
}
