#include "minishell.h"

int	get_pwd(char **pwd)
{
	*pwd = getcwd(NULL, 0);
	if (!*pwd)
		return (-2);
	return (0);
}

int	ft_cd(char *path, t_data *data)
{
	int		i;
	char	*oldpwd;
	char	*pwd;

	i = 0;
	while (ft_strncmp(data->my_env[i], "OLDPWD=", 7))
		i++;
	get_pwd(&oldpwd);
	data->my_env[i] = ft_strjoin("OLDPWD=", oldpwd, 0);
	if (!data->my_env)
		return (-1);
	if (chdir(path) == -1)
		return (-2);
	i = 0;
	while (ft_strncmp(data->my_env[i], "PWD=", 4))
		i++;
	get_pwd(&pwd);
	data->my_env[i] = ft_strjoin("PWD=", pwd, 0);
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

int	is_flagn(char *str)
{
	int	i;

	i = 0;
	if (str[i] != '-')
		return (0);
	i++;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	ft_echo(t_commands *cmds)
{
	int	i;
	int	flag;

	flag = 0;
	i = 1;
	if (cmds->args[i] == NULL)
		return (0);
	while (cmds->args[i][0] == 0)
		i++;
	while (cmds->args[i] && is_flagn(cmds->args[i]))
	{
		i++;
		flag++;
	}
	while (cmds->args[i])
	{
		printf("%s", cmds->args[i]);
		if (cmds->args[i + 1] && cmds->args[i + 1][0] != 0)
			printf(" ");
		i++;
	}
	if (!flag)
		printf("\n");
	return (0);
}
