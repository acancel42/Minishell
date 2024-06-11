
#include "minishell.h"

#include <unistd.h>

int main(int argc, char **argv, char **env)
{
	t_token				*token;
	t_commands			*cmds;
	char				*user;
	char				*line;
	char				**my_env;

	(void)argc;
	(void)argv;
	user = get_user(env);
	if (user == NULL)
		return (-1);
	while (1)
	{
		token = NULL;
		cmds = NULL;
		user = get_user(env);
		if (user == NULL)
		return (-1);
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
			get_cd(ft_substr(line, 3, ft_strlen(line) - 3));
			continue;
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
	return (0);
}

/*VALGRIND :

valgrind --suppressions=debug/valgrind_ignore_leaks.txt --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --show-mismatched-frees=yes --read-var-info=yes

*/
