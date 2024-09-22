#include "minishell.h"

t_data	*ft_init_shell(char **env)
{
	t_data	*data;
	char	*buf;

	buf = NULL;
	if (!env[0])
	{
		printf("no env\n");
		printf("%s\n", getcwd(buf, 0));
	}
	rl_event_hook = &do_nothing;
	data = ft_calloc(1, sizeof(t_data));
	if (!data)
		exit(EXIT_FAILURE);
	data->last_error_status = 0;
	ft_get_env(data, env);
	if (!data->my_env)
		printf("no env\n");
	if (get_home(data) == -1)
		ft_exit(NULL, NULL, data);
	return (data);
}

int	ft_data_init(t_data *data, t_commands **cmds)
{
	g_sigint = 0;
	ft_signalhandle();
	data->user = get_user(data);
	data->user = get_color(data, BLUE);
	data->line = readline(data->user);
	if (!data->line)
		ft_exit(NULL, NULL, data);
	if (ft_strncmp(data->line, "", 1) == 0)
	{
		free_data(data, cmds);
		return (-1);
	}
	if (g_sigint != 0)
	{
		free_data(data, cmds);
		return (-1);
	}
	if (data->line)
		add_history(data->line);
	if (prelexer_check(data) == 2)
	{
		free_data(data, cmds);
		return (-1);
	}
	return (0);
}
