
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
	int					i;
	char				*home;

	home = get_home(env);
	my_env = ft_get_env(env);

	if (!my_env)
		printf("no env\n");
	(void)argc;
	(void)argv;
	my_env = ft_get_env(env);
	if (!my_env)
			printf("no env\n");
	my_env = tab_join(my_env, "IFS= \t\n");
	while (1)
	{
		i = 0;
		token = NULL;
		cmds = NULL;
		// print_my_env(my_env);
		user = get_user(my_env);
		if (user == NULL)
		return (-1);
		user = get_color(user, BLUE);
		line = readline(user);
		if (!line)
			exit_minishell(&token, &cmds, &user, &my_env);
		if (*line)
			add_history(line);
		if (ft_strncmp(line, "", 1) == 0)
		{
			free(line);
			continue ;
		}
		lexer_init(&token, line);
		init_cmd(&cmds, token, user);
		fill_cmd(&cmds, token, my_env);
		//print_cmds(cmds);
		if (ft_strncmp(cmds->name, "cd", 2) == 0)
		{
			if (cmds->args[1] == NULL || ft_strncmp(cmds->args[1], "~", 1) == 0)
			{
				ft_cd(home, my_env);
				continue ;
			}
			else
			{
				ft_cd(ft_substr(line, 3, ft_strlen(line) - 3), my_env);
				continue ;
			}
		}
		if (ft_strncmp(cmds->name, "export", 6) == 0)
		{
			ft_export(cmds->args, &my_env);
			i++;
		}
		if (i == 0)
		{
			ft_pathfinder(token, cmds, my_env);
			if (ft_exec_v1(cmds, my_env) == -1)
				printf("execve failed\n");
		}
		ft_cmdsclear(&cmds);
		ft_tokenclear(&token);
		free(line);
	}
	free(home);
	return (0);
}
