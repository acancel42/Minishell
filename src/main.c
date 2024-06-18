
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
	char				*user;
	char				*line;
	char				**my_env;
	char				*home;

	home = get_home(env);
	(void)argc;
	(void)argv;
	while (1)
	{
		token = NULL;
		cmds = NULL;
		user = get_user(env);
		if (user == NULL)
		return (-1);
		user = get_color(user, BLUE);
		line = readline(user);
		if (!line)
			exit_minishell(&token, &cmds, &user);
		if (*line)
			add_history(line);
		lexer_init(&token, line);
		init_cmd(&cmds, token, user);
		fill_cmd(&cmds, token);
		if (ft_strncmp(cmds->name, "cd", 2) == 0)
		{
			if (ft_strncmp(cmds->args[1], "~", 1) == 0)
			{
				ft_printf("HOME =%s\n", home);
				get_cd(home);
				continue ;
			}
			else
			{
				ft_printf("test\n");
				get_cd(ft_substr(line, 3, ft_strlen(line) - 3));
				continue ;
			}
		}
		print_cmds(cmds);
		my_env = ft_get_env(env);
		if (!my_env)
			printf("no env\n");
		ft_pathfinder(token, cmds, env);
		if (ft_exec_v1(cmds, my_env) == -1)
			printf("execve failed\n");
		ft_free_tab(my_env);
		ft_cmdsclear(&cmds);
		ft_tokenclear(&token);
		free(line);
	}
	free(home);
	return (0);
}
