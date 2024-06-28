
#include "minishell.h"

#include <unistd.h>

char	*get_color(char *user, char *color)
{
	char *prompt;

	prompt = ft_strdup(color);
	prompt = ft_strjoin(prompt, user, 1);
	prompt = ft_strjoin(prompt, RESET, 1);
	free(user);
	return (prompt);
}

int main(int argc, char **argv, char **env)
{
	t_token				*token;
	t_commands			*cmds;
	t_data				*data;
	int					j;

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
		data->user = get_user(data->my_env);
		if (data->user == NULL)
			return (-1);
		data->user = get_color(data->user, BLUE);
		data->line = readline(data->user);
		if (!data->line)
			exit_minishell(&token, &cmds, &data->user, &data->my_env);
		if (data->line)
			add_history(data->line);
		if (ft_strncmp(data->line, "", 1) == 0)
		{
			free(data->line);
			continue ;
		}
		lexer_init(&token, data->line);
		init_cmd(&cmds, token, data);
		fill_cmd(&cmds, token, data->my_env);
		data->cmds = cmds;
		data->token = token;
		//print_cmds(cmds);
		if (ft_strncmp(cmds->name, "cd", 3) == 0)
		{
			if (cmds->args[1] == NULL || ft_strncmp(cmds->args[1], "~", 1) == 0)
			{
				ft_cd(data->home, data->my_env);
				ft_echo(cmds->args);
				ft_cmdsclear(&cmds);
				ft_tokenclear(&token);
				free(data->line);
				continue ;
			}
			else
			{
				ft_cd(ft_substr(data->line, 3, ft_strlen(data->line) - 3), data->my_env);
				ft_echo(cmds->args);
				ft_cmdsclear(&cmds);
				ft_tokenclear(&token);
				free(data->line);
				continue ;
			}
		}
		if (ft_strncmp(cmds->name, "echo", 5) == 0)
		{
			ft_echo(cmds->args);
			ft_cmdsclear(&cmds);
			ft_tokenclear(&token);
			free(data->line);
			continue;
		}
		if (ft_strncmp(cmds->name, "export", 7) == 0)
		{
			ft_export(cmds->args, &data->my_env);
			ft_cmdsclear(&cmds);
			ft_tokenclear(&token);
			free(data->line);
			continue;
		}
		j = -1;
		data->pflag = false;
		if (ft_pathfinder(token, cmds, data->my_env) == 0)
		{
			ft_cmdsclear(&cmds);
			ft_tokenclear(&token);
			free(data->line);
			continue;
		}
		while (data->line[++j])
		{
			if (data->line[j] == '|')
				data->pflag = 1;
		}
		if (data->pflag != 0)
			ft_pipe(cmds, data, token);
		else
			data->last_error_status = ft_exec_v1(cmds, data->my_env);
		ft_cmdsclear(&data->cmds);
		ft_tokenclear(&data->token);
		free(data->line);
	}
	free(data->home);
	return (0);
}
