#include "minishell.h"

void	exit_minishell(t_token **token, t_commands **cmds, t_data *data)
{
	ft_cmdsclear(cmds);
	ft_tokenclear(token);
	if (data)
	{
		if (data->line)
			free(data->line);
		if (data->my_env)
			ft_free_tab(data->my_env);
		if (data->user)
			free(data->user);
		if (data->home)
			free(data->home);
		if (data->export)
			ft_free_tab(data->export);
		free(data);
	}
	printf(RED"%s\n"RESET, "exit");
	return ;
}
	// exit(EXIT_SUCCESS);

void	ft_exec_error(t_token *token, t_commands *cmds, t_data *data, int flag)
{
	if (flag == 0)
		perror("pipe");
	else if (flag == 1)
		perror("fork");
	else if (flag == 2)
		perror("dup2");
	ft_exit(token, cmds, data);
}

void	ft_exit(t_token *token, t_commands *cmds, t_data *data)
{
	int	exit_stat;

	data->last_error_status = 1;
	if (cmds && cmds->args[1])
		exit_stat = ft_atoi(cmds->args[1]);
	else
		exit_stat = data->last_error_status;
	exit_minishell(&token, &cmds, data);
	exit(exit_stat);
}
