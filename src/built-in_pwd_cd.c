#include "minishell.h"

int	get_pwd(char **pwd)
{
	*pwd = getcwd(NULL, 0);
	if (!*pwd)
		return (-2);
	return (0);
}

int	ft_pwd(void)
{
	char	*pwd;

	if (get_pwd(&pwd) == 0)
	{
		if (pwd == NULL)
			return (-2);
		printf("%s\n", pwd);
		return (0);
	}
	return (-2);
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
	if (!data->my_env[i])
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


