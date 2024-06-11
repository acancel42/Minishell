
#include "minishell.h"


void	cmd_not_found(t_commands *cmds)	//, char **all_paths)
{
	char	*cmd_n_found;

	cmd_n_found = ft_strjoin(cmds->name, " : command not found\n", 0);
	// if (cmd_n_found == NULL)
		// clean_all(cmds, all_paths);
	ft_putstr_fd(cmd_n_found, 1);
	//printf("%s : command not found\n", cmds->name);
	free(cmd_n_found);
	// clean_all(cmds, all_paths);
}

void	build_path(t_commands *cmds, char *s1, char *s2)
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
		//free_all(NULL, cmds->path);
		exit(EXIT_FAILURE);
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
	while(tab[++i])
		free(tab[i]);
	free(tab);
}

void	cmd_path(t_commands *cmds, char **env)
{
	char	**all_paths;
	int		i;

	i = 0;
	while (ft_strncmp(env[i], "PATH=", 5) != 0)
		i++;
	cmds->path = env[i];
	all_paths = ft_split(cmds->path + 5, ':');
	if (all_paths == NULL)
	{
		ft_putstr_fd("malloc failed\n", 2);
		exit(EXIT_FAILURE);
	}
	i = 0;
	build_path(cmds, all_paths[i], cmds->name);
	printf("%s\n", cmds->path);
	while (cmds->path != NULL && access(cmds->path, F_OK))
	{
		free(cmds->path);
		build_path(cmds, all_paths[i++], cmds->name);
	}
	if (cmds->path == NULL)
		cmd_not_found(cmds); //, all_paths
	free_tab(all_paths);
	return ;
}

void	free_file(t_file *file)
{
	while (file)
	{
		free(file->name);
		file = file->next;
	}
}

void	ft_pathfinder(t_commands *cmds, char **env)
{
	while(cmds)
	{
		cmds->valid_path = access(cmds->name, F_OK);
		if (cmds->valid_path == -1 && ft_strchr_b(cmds->args[0], '/'))
			cmd_path(cmds, env);
		if (cmds->path)
			printf("path : %s\n", cmds->path);
		cmds = cmds->next;
	}
}
