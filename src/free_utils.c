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

void	free__monitoring(char *host, char *username, char *pwd)
{
	if (pwd)
		free(pwd);
	if (host)
		free(host);
	if (username)
		free(username);
	return ;
}
