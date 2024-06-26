
#include "minishell.h"


void	cmd_not_found(t_token *token, t_commands *cmds, char **env)
{
	char	*cmd_n_found;

	cmd_n_found = ft_strjoin(cmds->name, " : command not found\n", 0);
	if (cmd_n_found == NULL)
		exit_minishell(&token, &cmds, NULL, &env);
	ft_printf("%s\n", cmd_n_found);
	free(cmd_n_found);
	exit_minishell(&token, &cmds, NULL, &env);
}

void	build_path(t_token *token, t_commands *cmds, char *s1, \
					char *s2)
{
	size_t		len_s1;
	size_t		len_s2;

	if (!s1 || !s2)
	{
		cmds->path = NULL;
		return ;
	}
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	cmds->path = ft_calloc(len_s1 + 1 + len_s2 + 1, sizeof(char));
	if (cmds->path == NULL)
	{
		ft_putstr_fd("malloc failed\n", 2);
		exit_minishell(&token, &cmds, NULL, NULL);
	}
	ft_memcpy(cmds->path, s1, len_s1);
	ft_memcpy(cmds->path + len_s1, "/", 1);
	ft_memcpy(cmds->path + len_s1 + 1, s2, len_s2);
	return ;
}

void	free_tab(char **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);
}

void	cmd_path(t_token *token, t_commands *cmds, char **env)
{
	char	**all_paths;
	int		i;
	int		flag;

	i = 0;
	flag = 0;
	while (ft_strncmp(env[i], "PATH=", 5) != 0)
		i++;
	cmds->path = env[i];
	all_paths = ft_split(cmds->path + 5, ':');
	if (all_paths == NULL)
	{
		ft_putstr_fd("malloc failed\n", 2);
		exit_minishell(&token, &cmds, NULL, &env);
	}
	i = 0;
	build_path(token, cmds, all_paths[i], cmds->name);
	while (cmds->path != NULL && access(cmds->path, F_OK))
	{
		free(cmds->path);
		build_path(token, cmds, all_paths[i++], cmds->name);
	}
	if (cmds->path == NULL && ft_strncmp(cmds->name, "cd", 2) && flag == 0)
	cmd_not_found(token, cmds, env);
	free_tab(all_paths);
	return ;
}


void	ft_pathfinder(t_token *token, t_commands *cmds, char **env)
{
	while (cmds)
	{
		cmds->valid_path = access(cmds->args[0], F_OK);
		if (cmds->valid_path == -1 && ft_strchr_b(cmds->name, '/'))
			cmd_path(token, cmds, env);
		else
			cmds->path = ft_strdup(cmds->args[0]);
		if (cmds->path)
			cmds = cmds->next;
	}
	return ;
}
