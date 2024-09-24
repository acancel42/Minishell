#include "minishell.h"

int	get_pwd(char **pwd)
{
	*pwd = getcwd(NULL, 0);
	if (!*pwd)
		return (-2);
	return (0);
}

int	ft_pwd(t_data *data)
{
	dprintf(1,"'%s'\n", find_env_var("PWD", data->my_env));
	dprintf(2, "																		debug5\n");
	return (0);
}

// int	ft_pwd(void)
// {
// 	char	*pwd;

// 	pwd = NULL;
// 	if (get_pwd(&pwd) == 0)
// 	{
// 		if (pwd == NULL)
// 			return (-2);
// 		printf("%s\n", pwd);
// 		return (0);
// 	}
// 	free(pwd);
// 	return (-2);
// }

static int	ft_get_oldpwd(t_data *data)
{
	int		i;
	char	*oldpwd;

	i = 0;
	while (ft_strncmp(data->my_env[i], "OLDPWD=", 7))
		i++;
	get_pwd(&oldpwd);
	free(data->my_env[i]);
	data->my_env[i] = ft_strjoin("OLDPWD=", oldpwd, 0);
	if (!data->my_env[i])
		return (-1);
	free(oldpwd);
	return (0);
}

int	ft_cd(char *path, t_data *data, t_commands *cmds)
{
	int		i;
	char	*pwd;

	if (ft_get_oldpwd(data) == -1)
		return (-1);
	if (chdir(path) == -1)
	{
		printf("cd: %s: No such file or directory\n", path);
		return (-2);
	}
	i = 0;
	while (ft_strncmp(data->my_env[i], "PWD=", 4))
		i++;
	if (get_pwd(&pwd) == -2)
		printf("getcwd: cannot access parent directories\n");
	free(data->my_env[i]);
	data->my_env[i] = ft_strjoin("PWD=", pwd, 0);
	free(pwd);
	if (!data->my_env[i])
		ft_exit(data->token, cmds, data);
	return (0);
}
