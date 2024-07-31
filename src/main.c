#include "minishell.h"

int	g_sigint = 0;

char	*get_color(char *user, char *color)
{
	char	*prompt;

	prompt = ft_strdup(color);
	prompt = ft_strjoin(prompt, user, 1);
	prompt = ft_strjoin(prompt, RESET, 1);
	free(user);
	return (prompt);
}

void	ft_handler(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		g_sigint = 1;
	}
	return ;
}

int	do_nothing(void)
{
	return (42);
}

int	main(int argc, char **argv, char **env)
{
	t_token				*token;
	t_commands			*cmds;
	t_data				*data;
	int					j;

	if (!env[0])
	{
		printf("no env\n");
		return (-1);
	}
	rl_event_hook = &do_nothing;
	data = ft_calloc(1, sizeof(t_data));
	data->last_error_status = 0;
	ft_get_env(data, env);
	if (!data->my_env)
		printf("no env\n");
	if (get_home(data) == -1)
		ft_exit(NULL, NULL, data);
	(void)argc;
	(void)argv;
	while (1)
	{
		g_sigint = 0;
		ft_signalhandle();
		token = NULL;
		cmds = NULL;
		data->user = get_user(data);
		if (data->user == NULL)
			return (-1);
		data->user = get_color(data->user, BLUE);
		data->line = readline(data->user);
		if (!data->line)
			ft_exit(token, cmds, data);
		if (ft_strncmp(data->line, "", 1) == 0)
		{
			free_data(data, &cmds);
			continue ;
		}
		if (g_sigint != 0)
		{
			free_data(data, &cmds);
			continue ;
		}
		if (data->line)
			add_history(data->line);
		if (prelexer_check(data) == 2)
		{
			free_data(data, &cmds);
			continue ;
		}
		lexer_init(&token, data);
		init_cmd(&cmds, token, data);
		if (fill_cmd(&cmds, token, data) == 2)
		{
			free_data(data, &cmds);
			continue ;
		}
		data->cmds = cmds;
		data->token = token;
		if (cmds->name && ft_is_built_in(cmds) && data->index_max == 0 \
			&& cmds->redirections[0] == NULL)
		{
			if (ft_exec_built_in(token, cmds, data) == 1)
				data->last_error_status = 0;
			free_data(data, &cmds);
			continue ;
		}
		j = -1;
		data->pflag = false;
		if (cmds->name && ft_pathfinder(data) == 0)
		{
			data->last_error_status = 127;
			continue ;
		}
		while (data->line[++j])
		{
			if (data->line[j] == '|')
				data->pflag = 1;
		}
		exec_cmd(data, cmds);
		free_data(data, &cmds);
	}
	return (0);
}
