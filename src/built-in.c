
#include "minishell.h"

int	get_pwd(char **pwd)
{
	*pwd = getcwd(NULL, 0);
	if (!*pwd)
		return (-2);
	return (0);
}

int	get_cd(char *path)
{
	if (chdir(path) == -1)
		return (-2);
	return (0);
}

char	*get_home(char **env)
{
	char	*home;
	char	*name;
	int		i = 0;


	home = ft_strdup("/home/");
	i = 0;
	while (ft_strncmp(env[i], "LOGNAME=", 8) != 0)
		i++;
	name = ft_substr(env[i], 8, 8);
	if (name == NULL)
		return (NULL);
	home = ft_strjoin(home, name, 1);
	printf("Home bin = %s\n", home);
	return (home);
}