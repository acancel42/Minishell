
#include "minishell.h"

int	get_pwd(char **pwd)
{
	*pwd = getcwd(NULL, 0);
	if (!*pwd)
		return (-2);
	return (0);
}

int	ft_cd(char *path, char **my_env)
{
	int	i;
	char	*oldpwd;
	char	*pwd;

	i = 0;
	while (ft_strncmp(my_env[i], "OLDPWD=", 7))
		i++;
	get_pwd(&oldpwd);
	my_env[i] = ft_strjoin("OLDPWD=", oldpwd, 0);
	if (!my_env)
		return (-1);
	if (chdir(path) == -1)
		return (-2);
	i = 0;
	while (ft_strncmp(my_env[i], "PWD=", 4))
		i++;
	get_pwd(&pwd);
	my_env[i] = ft_strjoin("PWD=", pwd, 0);
	return (0);
}

char	*get_home(char **env)
{
	char	*home;
	int		i;

	i = 0;
	while (ft_strncmp(env[i], "HOME=", 5))
		i++;
	home = ft_substr(env[i], 5, 6 + 8);
	if (home == NULL)
		return (NULL);
	return (home);
}

int	ft_echo(char **args)
{
	int	i;
	int	flag;

	flag = 0;
	i = 1;
	if (!ft_strncmp(args[1], "-n", 2))
		flag++;
	i += flag;
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i +1])
			printf(" ");
		i++;
	}
	if (!flag)
		printf("\n");
	return (0);
}
