#include "minishell.h"

char	*get_color(char *user, char *color)
{
	char	*prompt;

	prompt = ft_strdup(color);
	prompt = ft_strjoin(prompt, user, 1);
	prompt = ft_strjoin(prompt, RESET, 1);
	free(user);
	return (prompt);
}

void	free_data(t_data *data)
{
	if (data->cmds)
		ft_cmdsclear(&data->cmds);
	if (data->token)
		ft_tokenclear(&data->token);
	if (data->line)
		free(data->line);
	if (data->user)
		free(data->user);
	data->index_max = 0;
	data->pflag = 0;
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
	data = ft_calloc(1, sizeof(t_data));
	data->home = get_home(env);
	data->my_env = ft_get_env(env);
	if (!data->my_env)
		printf("no env\n");
	(void)argc;
	(void)argv;
	while (1)
	{
		token = NULL;
		cmds = NULL;
		data->user = get_user(data);
		if (data->user == NULL)
			return (-1);
		data->user = get_color(data->user, BLUE);
		data->line = readline(data->user);
		if (!data->line)
			exit_minishell(&token, &cmds, data);
		if (ft_strncmp(data->line, "", 1) == 0)
		{
			free_data(data);
			continue ;
		}
		if (data->line)
			add_history(data->line);
		if (prelexer_check(data) == 2)
		{
			free_data(data);
			continue ;
		}
		lexer_init(&token, data);
		print_lst(token);
		init_cmd(&cmds, token, data);
		fill_cmd(&cmds, token, data);
		data->cmds = cmds;
		data->token = token;
		// if (ft_is_built_in(data, cmds))
		// 	continue ;
		j = -1;
		data->pflag = false;
		if (ft_pathfinder(data) == 0)
			continue ;
		while (data->line[++j])
		{
			if (data->line[j] == '|')
				data->pflag = 1;
		}
		exec_cmd(data, cmds);
		free_data(data);
	}
	free(data->home);
	return (0);
}
